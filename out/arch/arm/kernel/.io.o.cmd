cmd_arch/arm/kernel/io.o := /root/kernel_asus_live_source/scripts/gcc-wrapper.py /root/Android/utulity/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,arch/arm/kernel/.io.o.d  -nostdinc -isystem /root/Android/utulity/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/root/kernel_asus_live_source/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/root/kernel_asus_live_source/include -include /root/kernel_asus_live_source/include/linux/kconfig.h  -I/root/kernel_asus_live_source/arch/arm/kernel -Iarch/arm/kernel -D__KERNEL__ -mlittle-endian   -I/root/kernel_asus_live_source/arch/arm/mach-msm/include -DASUS_SW_VER=\"_ENG\" -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -Wno-maybe-uninitialized -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a15 -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(io)"  -D"KBUILD_MODNAME=KBUILD_STR(io)" -c -o arch/arm/kernel/.tmp_io.o /root/kernel_asus_live_source/arch/arm/kernel/io.c

source_arch/arm/kernel/io.o := /root/kernel_asus_live_source/arch/arm/kernel/io.c

deps_arch/arm/kernel/io.o := \
  /root/kernel_asus_live_source/include/linux/export.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /root/kernel_asus_live_source/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/types.h \
  /root/kernel_asus_live_source/include/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  /root/kernel_asus_live_source/include/asm-generic/bitsperlong.h \
  /root/kernel_asus_live_source/include/linux/posix_types.h \
  /root/kernel_asus_live_source/include/linux/stddef.h \
  /root/kernel_asus_live_source/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /root/kernel_asus_live_source/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /root/kernel_asus_live_source/include/linux/compiler-gcc4.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/posix_types.h \
  /root/kernel_asus_live_source/include/asm-generic/posix_types.h \
  /root/kernel_asus_live_source/include/linux/io.h \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/has/ioport.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/io.h \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/need/mach/io/h.h) \
    $(wildcard include/config/pcmcia/soc/common.h) \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/isa.h) \
    $(wildcard include/config/pccard.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/byteorder.h \
  /root/kernel_asus_live_source/include/linux/byteorder/little_endian.h \
  /root/kernel_asus_live_source/include/linux/swab.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/swab.h \
  /root/kernel_asus_live_source/include/linux/byteorder/generic.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
  /root/kernel_asus_live_source/include/linux/const.h \
  arch/arm/include/generated/asm/sizes.h \
  /root/kernel_asus_live_source/include/asm-generic/sizes.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/memory.h \
    $(wildcard include/config/arch/msm7x30.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/vmsplit/3g.h) \
    $(wildcard include/config/arch/msm/arm11.h) \
    $(wildcard include/config/arch/msm/cortex/a5.h) \
    $(wildcard include/config/cache/l2x0.h) \
    $(wildcard include/config/arch/msm8x60.h) \
    $(wildcard include/config/arch/msm8960.h) \
    $(wildcard include/config/dont/map/hole/after/membank0.h) \
    $(wildcard include/config/arch/msm/scorpion.h) \
    $(wildcard include/config/arch/msm/krait.h) \
    $(wildcard include/config/arch/msm7x27.h) \
  /root/kernel_asus_live_source/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  /root/kernel_asus_live_source/include/asm-generic/pci_iomap.h \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_rtb.h \
    $(wildcard include/config/msm/rtb.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/smp.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/io.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/kuser/helpers.h) \
    $(wildcard include/config/arm/lpae.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/memory/hotplug/sparse.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/glue.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable-2level-types.h \
  /root/kernel_asus_live_source/include/asm-generic/getorder.h \
  /root/kernel_asus_live_source/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /root/kernel_asus_live_source/include/linux/bitops.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/bitops.h \
  /root/kernel_asus_live_source/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /root/kernel_asus_live_source/include/linux/typecheck.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/irqflags.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/hwcap.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/non-atomic.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/fls64.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/sched.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/hweight.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/arch_hweight.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/const_hweight.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/lock.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/le.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/ext2-atomic-setbit.h \

arch/arm/kernel/io.o: $(deps_arch/arm/kernel/io.o)

$(deps_arch/arm/kernel/io.o):
