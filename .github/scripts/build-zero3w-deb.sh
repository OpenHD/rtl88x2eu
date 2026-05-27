#!/usr/bin/env bash
set -euo pipefail

: "${KERNEL_VERSION:=6.1.84-16-rk2410-nocsf}"
: "${KERNEL_PACKAGE_VERSION:=6.1.84-16}"
: "${PACKAGE_NAME:=rtl88x2eu-ohd-zero3w}"
: "${PACKAGE_VERSION:=2.6.openhd.0.local}"
: "${MODULE_NAME:=rtl88x2eu_ohd}"

export DEBIAN_FRONTEND=noninteractive

apt-get update
apt-get install -y --no-install-recommends \
  bc \
  bison \
  build-essential \
  ca-certificates \
  curl \
  dpkg-dev \
  file \
  flex \
  gnupg \
  kmod \
  make

curl -1sLf 'https://dl.cloudsmith.io/public/openhd/dev-release/setup.deb.sh' \
  | distro=debian codename=bookworm bash

apt-get update
headers_download_dir="$(mktemp -d)"
(
  cd "${headers_download_dir}"
  apt-get download "linux-headers-${KERNEL_VERSION}=${KERNEL_PACKAGE_VERSION}"
)
headers_deb="$(find "${headers_download_dir}" -maxdepth 1 -name "linux-headers-${KERNEL_VERSION}_*.deb" -print -quit)"
if [[ -z "${headers_deb}" || ! -f "${headers_deb}" ]]; then
  echo "Failed to download linux-headers-${KERNEL_VERSION}=${KERNEL_PACKAGE_VERSION}" >&2
  exit 1
fi

# Extract only the header payload into an isolated tree. Installing the package
# would run maintainer scripts under the GitHub host kernel uname, and extracting
# into / can break merged-/usr containers that keep /lib as a symlink.
headers_extract_dir="$(mktemp -d)"
dpkg-deb -x "${headers_deb}" "${headers_extract_dir}"

headers_dir="${headers_extract_dir}/usr/src/linux-headers-${KERNEL_VERSION}"
if [[ ! -e "${headers_dir}/Makefile" ]]; then
  headers_dir="$(find "${headers_extract_dir}" -type d -name "*${KERNEL_VERSION}*" | head -n1)"
fi
if [[ -z "${headers_dir}" || ! -e "${headers_dir}/Makefile" ]]; then
  echo "Unable to locate kernel headers for ${KERNEL_VERSION}" >&2
  exit 1
fi

mkdir -p "/lib/modules/${KERNEL_VERSION}"
ln -sfn "${headers_dir}" "/lib/modules/${KERNEL_VERSION}/build"
ls -ld "/lib/modules/${KERNEL_VERSION}/build"

make clean || true
make -j"$(nproc)" \
  ARCH=arm64 \
  KVER="${KERNEL_VERSION}" \
  KSRC="/lib/modules/${KERNEL_VERSION}/build" \
  M="${PWD}" \
  USER_MODULE_NAME="${MODULE_NAME}" \
  modules

module_path="${PWD}/${MODULE_NAME}.ko"
if [[ ! -f "${module_path}" ]]; then
  module_path="$(find "${PWD}" -maxdepth 1 -name '*.ko' | head -n1)"
fi
if [[ -z "${module_path}" || ! -f "${module_path}" ]]; then
  echo "Failed to find built ${MODULE_NAME}.ko" >&2
  exit 1
fi

file "${module_path}" | tee /tmp/module-file.txt
grep -Eq 'ARM aarch64|ARM64|aarch64' /tmp/module-file.txt
modinfo -F vermagic "${module_path}" | tee /tmp/module-vermagic.txt
grep -F "${KERNEL_VERSION}" /tmp/module-vermagic.txt

dpkg --validate-version "${PACKAGE_VERSION}"

pkg_root="$(mktemp -d)"
trap 'rm -rf "${pkg_root}"' EXIT
mkdir -p \
  "${pkg_root}/DEBIAN" \
  "${pkg_root}/etc/modprobe.d" \
  "${pkg_root}/lib/modules/${KERNEL_VERSION}/kernel/drivers/net/wireless"

install -m 0644 "${module_path}" \
  "${pkg_root}/lib/modules/${KERNEL_VERSION}/kernel/drivers/net/wireless/${MODULE_NAME}.ko"

if [[ -f realtek_88x2eu.conf ]]; then
  install -m 0644 realtek_88x2eu.conf "${pkg_root}/etc/modprobe.d/realtek_88x2eu.conf"
else
  printf 'options %s rtw_regd_src=1 rtw_tx_pwr_by_rate=0 rtw_tx_pwr_lmt_enable=0\n' "${MODULE_NAME}" \
    > "${pkg_root}/etc/modprobe.d/realtek_88x2eu.conf"
fi

cat > "${pkg_root}/DEBIAN/control" <<EOF
Package: ${PACKAGE_NAME}
Version: ${PACKAGE_VERSION}
Section: kernel
Priority: optional
Architecture: arm64
Maintainer: OpenHD <maintainers@openhd.org>
Depends: kmod, linux-image-${KERNEL_VERSION} (= ${KERNEL_PACKAGE_VERSION})
Description: OpenHD RTL88x2EU kernel module for Radxa Zero 3W
 Prebuilt rtl88x2eu_ohd module for the Radxa Zero 3W OpenHD Lite kernel.
EOF

cat > "${pkg_root}/DEBIAN/postinst" <<EOF
#!/bin/sh
set -e
depmod -a ${KERNEL_VERSION} || true
exit 0
EOF
chmod 0755 "${pkg_root}/DEBIAN/postinst"

cat > "${pkg_root}/DEBIAN/postrm" <<EOF
#!/bin/sh
set -e
depmod -a ${KERNEL_VERSION} || true
exit 0
EOF
chmod 0755 "${pkg_root}/DEBIAN/postrm"

mkdir -p dist
deb_path="dist/${PACKAGE_NAME}_${PACKAGE_VERSION}_arm64.deb"
dpkg-deb --build --root-owner-group "${pkg_root}" "${deb_path}"
dpkg-deb -I "${deb_path}"
dpkg-deb -c "${deb_path}"
