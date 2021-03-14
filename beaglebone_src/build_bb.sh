rm -f rootfs.cpio.gz
rm -rf _install/

make -j 4
make install

mkdir -p _install/{boot,dev,etc\/init.d,lib,proc,root,sys\/kernel\/debug,tmp}


echo '#!/bin/sh'                                   > _install/etc/init.d/rcS
echo 'mount -t sysfs none /sys'                   >> _install/etc/init.d/rcS
echo 'mount -t proc none /proc'                   >> _install/etc/init.d/rcS
echo 'mount -t debugfs none /sys/kernel/debug'    >> _install/etc/init.d/rcS
echo 'echo /sbin/mdev > /proc/sys/kernel/hotplug' >> _install/etc/init.d/rcS
echo 'mdev -s'                                    >> _install/etc/init.d/rcS

chmod +x _install/etc/init.d/rcS

ln -s bin/busybox _install/init

#/boot
cd _install/boot
cp ../../../linux-stable/arch/arm/boot/zImage .
cp ../../../linux-stable/arch/arm/boot/dts/am335x-boneblack.dtb .
cp ../../../linux-stable/System.map .
cp ../../../linux-stable/.config ./config
cd ..

#/lib
cd ../../linux-stable
export INSTALL_MOD_PATH=../busybox/_install
export ARCH=arm
make modules_install
cd ../busybox/

cd _install/lib
libc_dir=$(${CROSS_COMPILE}gcc -print-sysroot)/lib
cp -a $libc_dir/*.so* .
cd ../../

#/etc
echo '$MODALIAS=.* root:root 660 @modprobe "$MODALIAS"' > _install/etc/mdev.conf
echo 'root:x:0:' > _install/etc/group
echo 'root:x:0:0:root:/root:/bin/sh' > _install/etc/passwd
echo 'root::10933:0:99999:7:::' > _install/etc/shadow

echo "nameserver 8.8.8.8" > _install/etc/resolv.conf

# QEMU
cd _install
find . | cpio -o -H newc | gzip > ../rootfs.cpio.gz
cd ..

