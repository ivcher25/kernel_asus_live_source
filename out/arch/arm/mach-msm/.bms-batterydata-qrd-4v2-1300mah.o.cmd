cmd_arch/arm/mach-msm/bms-batterydata-qrd-4v2-1300mah.o := /root/kernel_asus_live_source/scripts/gcc-wrapper.py /root/Android/utulity/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,arch/arm/mach-msm/.bms-batterydata-qrd-4v2-1300mah.o.d  -nostdinc -isystem /root/Android/utulity/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/root/kernel_asus_live_source/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/root/kernel_asus_live_source/include -include /root/kernel_asus_live_source/include/linux/kconfig.h  -I/root/kernel_asus_live_source/arch/arm/mach-msm -Iarch/arm/mach-msm -D__KERNEL__ -mlittle-endian   -I/root/kernel_asus_live_source/arch/arm/mach-msm/include -DASUS_SW_VER=\"_ENG\" -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -Wno-maybe-uninitialized -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a15 -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(bms_batterydata_qrd_4v2_1300mah)"  -D"KBUILD_MODNAME=KBUILD_STR(bms_batterydata_qrd_4v2_1300mah)" -c -o arch/arm/mach-msm/.tmp_bms-batterydata-qrd-4v2-1300mah.o /root/kernel_asus_live_source/arch/arm/mach-msm/bms-batterydata-qrd-4v2-1300mah.c

source_arch/arm/mach-msm/bms-batterydata-qrd-4v2-1300mah.o := /root/kernel_asus_live_source/arch/arm/mach-msm/bms-batterydata-qrd-4v2-1300mah.c

deps_arch/arm/mach-msm/bms-batterydata-qrd-4v2-1300mah.o := \
  /root/kernel_asus_live_source/include/linux/batterydata-lib.h \
    $(wildcard include/config/pm8921/bms.h) \
    $(wildcard include/config/qpnp/bms.h) \
  /root/kernel_asus_live_source/include/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  /root/kernel_asus_live_source/include/asm-generic/errno.h \
  /root/kernel_asus_live_source/include/asm-generic/errno-base.h \

arch/arm/mach-msm/bms-batterydata-qrd-4v2-1300mah.o: $(deps_arch/arm/mach-msm/bms-batterydata-qrd-4v2-1300mah.o)

$(deps_arch/arm/mach-msm/bms-batterydata-qrd-4v2-1300mah.o):
