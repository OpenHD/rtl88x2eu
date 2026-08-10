#!/bin/sh
set -eu

binary=
map=
mask=
version=1.0.2
architecture=
output_dir=dist

while [ "$#" -gt 0 ]; do
	case "$1" in
		--binary) binary=$2; shift 2 ;;
		--map) map=$2; shift 2 ;;
		--mask) mask=$2; shift 2 ;;
		--version) version=$2; shift 2 ;;
		--architecture) architecture=$2; shift 2 ;;
		--output-dir) output_dir=$2; shift 2 ;;
		*) echo "unknown argument: $1" >&2; exit 2 ;;
	esac
done

command -v dpkg-deb >/dev/null 2>&1 || {
	echo "dpkg-deb is required" >&2
	exit 1
}

for required_file in "$binary" "$map" "$mask"; do
	[ -f "$required_file" ] || {
		echo "required file not found: $required_file" >&2
		exit 1
	}
done

[ -n "$architecture" ] || architecture=$(dpkg --print-architecture)
case "$version" in
	*[!0-9A-Za-z.+:~-]*|'') echo "invalid Debian version: $version" >&2; exit 2 ;;
esac
case "$architecture" in
	*[!0-9a-z]*|'') echo "invalid Debian architecture: $architecture" >&2; exit 2 ;;
esac

staging=$(mktemp -d "${TMPDIR:-/tmp}/openhd-efuse-deb.XXXXXX")
trap 'rm -rf -- "$staging"' EXIT HUP INT TERM
chmod 0755 "$staging"

install -d -m 0755 "$staging/DEBIAN" "$staging/usr/sbin" \
	"$staging/usr/share/doc/openhd-efuse-flasher" "$staging/etc/wifi"
install -m 0755 "$binary" "$staging/usr/sbin/openhd-efuse-flash"
install -m 0600 "$map" "$staging/etc/wifi/wifi_efuse_88x2eu_ohd.map"
install -m 0600 "$mask" "$staging/etc/wifi/wifi_efuse_88x2eu_ohd.mask"
install -m 0644 tools/README.efuse.md \
	"$staging/usr/share/doc/openhd-efuse-flasher/README"

cat >"$staging/DEBIAN/control" <<EOF
Package: openhd-efuse-flasher
Version: $version
Section: utils
Priority: optional
Architecture: $architecture
Maintainer: OpenHD <contact@openhd.tech>
Depends: libc6, libstdc++6, kmod
Recommends: whiptail
Description: OpenHD RTL8812EU/RTL8822EU eFuse provisioning utility
 Installs the native provisioning tool and the root-only OpenHD eFuse map and
 mask. The utility allocates a random persistent MAC, rejects addresses already
 recorded on the host, verifies readback, and restores normal driver mode.
EOF

cat >"$staging/DEBIAN/conffiles" <<EOF
/etc/wifi/wifi_efuse_88x2eu_ohd.map
/etc/wifi/wifi_efuse_88x2eu_ohd.mask
EOF

install -d -m 0755 "$output_dir"
package="$output_dir/openhd-efuse-flasher_${version}_${architecture}.deb"
dpkg-deb --root-owner-group --build "$staging" "$package"
echo "$package"
