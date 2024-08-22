#!/bin/bash
# This file is the install instruction for the CHROOT build
# We're using cloudsmith-cli to upload the file in CHROOT

mkdir -p /out
sudo apt update
sudo apt install -y python3-pip ruby ruby-dev rubygems build-essential
pip3 install --upgrade pip
gem install fpm
sudo pip3 install --upgrade cloudsmith-cli --break-system-packages
ls -a
API_KEY=$(cat cloudsmith_api_key.txt)
DISTRO=$(cat distro.txt)
FLAVOR=$(cat flavor.txt)
REPO=$(cat repo.txt)
CUSTOM=$(cat custom.txt)
ARCH=$(cat arch.txt)

echo ${DISTRO}
echo ${FLAVOR}
echo ${CUSTOM}
echo ${ARCH}

if [[ -e /etc/os-release && $(grep -c "Raspbian" /etc/os-release) -gt 0 ]]; then
    echo "building for the raspberry pi"
    sudo apt update 
    sudo apt install -y build-essential flex bc bison dkms raspberrypi-kernel-headers
    echo "---------------"
    echo "_____________________________________________"
    make KSRC=/usr/src/linux-headers-6.1.21-v7l+ O="" modules
    ls -a /usr/src/
elif [[ "$(lsb_release -cs)" == "noble" ]]; then 
    echo "building for ubuntu noble minimal"
    sudo apt update 
    sudo apt install -y build-essential flex bc bison dkms
    make KSRC=/usr/src/linux-headers-6.1.21-v7l+ O="" modules
    mkdir -p package/lib/modules/6.8.0-31-generic/kernel/drivers/net/wireless/
    cp *.ko package/lib/modules/6.8.0-31-generic/kernel/drivers/net/wireless/
    ls -a
    fpm -a amd64 -s dir -t deb -n rtl88x2eu-x86 -v 2.6-evo-$(date '+%m%d%H%M') -C package -p rtl88x2eu-x86.deb --before-install before-install.sh --after-install after-install.sh
    echo "copied deb file"
    echo "push to cloudsmith"
    git describe --exact-match HEAD >/dev/null 2>&1
    echo "Pushing the package to OpenHD 2.5 repository"
    # cloudsmith push deb --api-key "$API_KEY" openhd/release/ubuntu/noble rtl88x2eu-x86.deb || exit 1
    cp *.deb /out/
    echo "copied deb file"
    echo "---------------"
    echo "_____________________________________________"
else
ls -a /usr/src/

sudo apt install -y build-essential flex bc bison dkms
make KSRC=/usr/src/linux-headers-6.3.13-060313-generic O="" modules
mkdir -p package/lib/modules/6.3.13-060313-generic/kernel/drivers/net/wireless/
cp *.ko package/lib/modules/6.3.13-060313-generic/kernel/drivers/net/wireless/
ls -a
fpm -a amd64 -s dir -t deb -n rtl88x2eu-x86 -v 2.6-evo-$(date '+%m%d%H%M') -C package -p rtl88x2eu-x86.deb --before-install before-install.sh --after-install after-install.sh
cp *.deb /out/
echo "copied deb file"

# echo "push to cloudsmith"
# git describe --exact-match HEAD >/dev/null 2>&1
# echo "Pushing the package to OpenHD 2.5 repository"
# ls -a
# cloudsmith push deb --api-key "$API_KEY" openhd/release/ubuntu/lunar rtl88x2eu-x86.deb || exit 1
fi