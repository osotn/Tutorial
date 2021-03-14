# Baremetal Linaro toolchain
wget https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/arm-eabi/gcc-linaro-7.3.1-2018.05-x86_64_arm-eabi.tar.xz
sudo tar xJvf gcc-linaro-7.3.1-2018.05-x86_64_arm-eabi.tar.xz -C /opt/
# Linux Linaro toolchain
# TODO

# Preparing
sudo apt install vim git tee ccache make libncurses5-dev libssl-dev bc bison flex

ccache -M 5G

mkdir ~/repos
cd ~/repos

# Build U-Boot
git clone git://git.denx.de/u-boot.git
git checkout v2019.01
git revert --no-edit d30ba2315ae3

export PATH=/opt/gcc-linaro-7.3.1-2018.05-x86_64_arm-eabi/bin:$PATH
export CROSS_COMPILE='ccache arm-eabi-'
export ARCH=arm

make am335x_boneblack_defconfig
make -j4


# Build U-Boot and run it on QEMU
git clone git://git.denx.de/u-boot.git ./u-boot-qemu
cd u-boot-qemu/
git checkout v2019.01
git revert --no-edit d30ba2315ae3
make qemu_arm_defconfig
make -j 4
qemu-system-arm -M virt -nographic -kernel u-boot
### To interrupt QEMU need to put "Ctrl-A + X" => QEMU: Terminated
### To test U-Boot on native host, we can build SANDBOX config



# Linux kernel
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
cd linux-stable
git checkout linux-4.19.y
#
export PATH=/opt/gcc-linaro-7.3.1-2018.05-x86_64_arm-eabi/bin:$PATH
export CROSS_COMPILE='ccache arm-eabi-'
export ARCH=arm

mkdir fragments

---------------------
# Use multi_v7_defconfig as a base for merge_config.sh
# --- USB ---
# Enable USB on BBB (AM335x)
CONFIG_USB_ANNOUNCE_NEW_DEVICES=y
CONFIG_USB_EHCI_ROOT_HUB_TT=y
CONFIG_AM335X_PHY_USB=y
CONFIG_USB_MUSB_TUSB6010=y
CONFIG_USB_MUSB_OMAP2PLUS=y
CONFIG_USB_MUSB_HDRC=y
CONFIG_USB_MUSB_DSPS=y
CONFIG_USB_MUSB_AM35X=y
CONFIG_USB_CONFIGFS=y
CONFIG_NOP_USB_XCEIV=y
# For USB keyboard and mouse
CONFIG_USB_HID=y
CONFIG_USB_HIDDEV=y
# For PL2303, FTDI, etc
CONFIG_USB_SERIAL=y
CONFIG_USB_SERIAL_PL2303=y
CONFIG_USB_SERIAL_GENERIC=y
CONFIG_USB_SERIAL_SIMPLE=y
CONFIG_USB_SERIAL_FTDI_SIO=y
# For USB mass storage devices (like flash USB stick)
CONFIG_USB_ULPI=y
CONFIG_USB_ULPI_BUS=y
# --- Networking ---
CONFIG_BRIDGE=y
# --- Device Tree Overlays (.dtbo support) ---
CONFIG_OF_OVERLAY=y
----------------------------------

vim fragments/bbb.cfg

./scripts/kconfig/merge_config.sh \
arch/arm/configs/multi_v7_defconfig fragments/bbb.cfg

make -j4 zImage modules am335x-boneblack.dtb





# BUSY-BOX

git clone git://git.busybox.net/busybox
cd busybox
git checkout 1_29_stable

export ARCH=arm
export PATH=/opt/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabihf/bin:$PATH
export CROSS_COMPILE="ccache arm-linux-gnueabihf-"

make defconfig

make -j4

make install

# see build_bb.sh

qemu-system-arm -kernel _install/boot/zImage -initrd rootfs.cpio.gz \
-machine virt -nographic -m 512 \
-append "root=/dev/ram0 rw console=ttyAMA0,115200 mem=512M"


# SD image
sudo fdisk -l
### for sdb
sudo umount /dev/sdb1
sudo umount /dev/sdb2
sudo dd if=/dev/zero of=/dev/sdb bs=1M count=1
sudo sfdisk /dev/sdb << EOF
2048,100M,0x0c,*
,,L,-
EOF

sudo mkfs.vfat -F 32 -n "boot" /dev/sdb1
sudo mkfs.ext4 -F -L "rootfs" /dev/sdb2

sudo fdisk -l

sudo umount /dev/sdb1
sudo umount /dev/sdb2

sudo mkdir /mnt/{boot,rootfs}
sudo mount /dev/sdb1 /mnt/boot
sudo mount /dev/sdb2 /mnt/rootfs

cd /busybox/_install
sudo cp -R . /mnt/rootfs
cd ../../u-boot
sudo cp MLO u-boot.img /mnt/boot


sudo umount /mnt/boot
sudo umount /mnt/rootfs




