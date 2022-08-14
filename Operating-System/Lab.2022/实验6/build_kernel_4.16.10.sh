##########################################################################
# File Name: build_kernel_4.16.10.sh
# Author: Zhang Hao
# mail: HolgerZhang@outlook.com
# Created Time:  5/ 6 21:39:20 2022
# !!RUN THIS SCRIPT AS ROOT!!
#########################################################################
#!/bin/bash

# Check kernel version
ver1=`uname -r | cut -d '.' -f1`
ver2=`uname -r | cut -d '.' -f2`
ver3=`uname -r | cut -d '.' -f3`
if [ $ver1 != 4 ]; then 
	echo "Kernel version not matches!"
	exit
fi
if [ $ver2 = 16 ]; then
	if [ $ver3 -ge 10 ]; then
		echo "Kernel version not matches!"
		exit
	fi
elif [ $ver2 -gt 16 ]; then 
	echo "Kernel version not matches!"
	exit
fi

# Install packages
apt update || exit
apt install wget build-essential libncurses-dev bison flex openssl libssl-dev libelf-dev -y || exit

# Download linux-4.16.10
if [ -e /usr/src/linux-4.16.10/ ]; then
	rm -rf /usr/src/linux-4.16.10
fi
cd /tmp || exit
wget http://ftp.sjtu.edu.cn/sites/ftp.kernel.org/pub/linux/kernel/v4.x/linux-4.16.10.tar.gz || exit
tar -xzf linux-4.16.10.tar.gz -C /usr/src || exit

# Config and build
cd /usr/src/linux-4.16.10 || exit
make menuconfig || exit
make -j || exit
make modules -j || exit
make modules_install || exit
make install || exit

echo "Kernel built finished! Please reboot."


