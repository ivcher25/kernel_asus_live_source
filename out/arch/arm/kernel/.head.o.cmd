cmd_arch/arm/kernel/head.o := /root/kernel_asus_live_source/scripts/gcc-wrapper.py /root/Android/utulity/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,arch/arm/kernel/.head.o.d  -nostdinc -isystem /root/Android/utulity/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/root/kernel_asus_live_source/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/root/kernel_asus_live_source/include -include /root/kernel_asus_live_source/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian   -I/root/kernel_asus_live_source/arch/arm/mach-msm/include -DASUS_SW_VER=\"_ENG\" -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a15 -include asm/unified.h -msoft-float -gdwarf-2 -DTEXT_OFFSET=0x00008000   -c -o arch/arm/kernel/head.o /root/kernel_asus_live_source/arch/arm/kernel/head.S

source_arch/arm/kernel/head.o := /root/kernel_asus_live_source/arch/arm/kernel/head.S

deps_arch/arm/kernel/head.o := \
    $(wildcard include/config/debug/ll.h) \
    $(wildcard include/config/arm/lpae.h) \
    $(wildcard include/config/xip/kernel.h) \
    $(wildcard include/config/xip/phys/addr.h) \
    $(wildcard include/config/smp/on/up.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/debug/icedcc.h) \
    $(wildcard include/config/debug/semihosting.h) \
    $(wildcard include/config/arch/netwinder.h) \
    $(wildcard include/config/arch/cats.h) \
    $(wildcard include/config/arch/rpc.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/alignment/trap.h) \
    $(wildcard include/config/cpu/dcache/disable.h) \
    $(wildcard include/config/cpu/bpredict/disable.h) \
    $(wildcard include/config/cpu/icache/disable.h) \
    $(wildcard include/config/arch/msm/krait.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  /root/kernel_asus_live_source/include/linux/linkage.h \
  /root/kernel_asus_live_source/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/linkage.h \
  /root/kernel_asus_live_source/include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
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
  /root/kernel_asus_live_source/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/hwcap.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/domain.h \
    $(wildcard include/config/verify/permission/fault.h) \
    $(wildcard include/config/io/36.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/cp15.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
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
    $(wildcard include/config/arch/msm7x27.h) \
  /root/kernel_asus_live_source/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable.h \
    $(wildcard include/config/highpte.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/proc-fns.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/glue-proc.h \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm7tdmi.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/arm720t.h) \
    $(wildcard include/config/cpu/arm740t.h) \
    $(wildcard include/config/cpu/arm9tdmi.h) \
    $(wildcard include/config/cpu/arm920t.h) \
    $(wildcard include/config/cpu/arm922t.h) \
    $(wildcard include/config/cpu/arm925t.h) \
    $(wildcard include/config/cpu/arm926t.h) \
    $(wildcard include/config/cpu/arm940t.h) \
    $(wildcard include/config/cpu/arm946e.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/arm1020.h) \
    $(wildcard include/config/cpu/arm1020e.h) \
    $(wildcard include/config/cpu/arm1022.h) \
    $(wildcard include/config/cpu/arm1026.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/mohawk.h) \
    $(wildcard include/config/cpu/v6.h) \
    $(wildcard include/config/cpu/v6k.h) \
    $(wildcard include/config/cpu/v7.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/glue.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/kuser/helpers.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/memory/hotplug/sparse.h) \
  /root/kernel_asus_live_source/include/asm-generic/getorder.h \
  /root/kernel_asus_live_source/include/asm-generic/pgtable-nopud.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable-hwdef.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable-2level-hwdef.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable-2level.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/debug-macro.S \
    $(wildcard include/config/msm/has/debug/uart/hs.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/hardware.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap.h \
    $(wildcard include/config/debug/msm/uart1.h) \
    $(wildcard include/config/debug/msm/uart2.h) \
    $(wildcard include/config/debug/msm/uart3.h) \
    $(wildcard include/config/msm/debug/uart/phys.h) \
    $(wildcard include/config/arch/qsd8x50.h) \
    $(wildcard include/config/arch/fsm9xxx.h) \
    $(wildcard include/config/arch/msm9625.h) \
    $(wildcard include/config/arch/msm9615.h) \
    $(wildcard include/config/arch/msm8610.h) \
    $(wildcard include/config/arch/msm8226.h) \
    $(wildcard include/config/arch/msmkrypton.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-7xxx.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-7x30.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8625.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8960.h \
    $(wildcard include/config/debug/msm8960/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8930.h \
    $(wildcard include/config/debug/msm8930/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8064.h \
    $(wildcard include/config/debug/apq8064/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-9615.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8974.h \
    $(wildcard include/config/debug/msm8974/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8084.h \
    $(wildcard include/config/debug/apq8084/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-9625.h \
    $(wildcard include/config/debug/msm9625/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8092.h \
    $(wildcard include/config/debug/mpq8092/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8226.h \
    $(wildcard include/config/debug/msm8226/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-8610.h \
    $(wildcard include/config/debug/msm8610/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-krypton.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-fsm9900.h \
    $(wildcard include/config/debug/fsm9900/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_iomap-samarium.h \
    $(wildcard include/config/debug/msmsamarium/uart.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_serial_hsl_regs.h \
    $(wildcard include/config/msm/has/debug/uart/hs/v14.h) \
  /root/kernel_asus_live_source/arch/arm/kernel/head-common.S \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/of/flattree.h) \

arch/arm/kernel/head.o: $(deps_arch/arm/kernel/head.o)

$(deps_arch/arm/kernel/head.o):
