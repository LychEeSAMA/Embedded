#!/bin/sh

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf- 

make distclean
make mx6ull_14x14_ddr512_emmc_defconfig
make -j16
