cmd_init/main.o := /root/kernel_asus_live_source/scripts/gcc-wrapper.py /root/Android/utulity/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,init/.main.o.d  -nostdinc -isystem /root/Android/utulity/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/root/kernel_asus_live_source/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/root/kernel_asus_live_source/include -include /root/kernel_asus_live_source/include/linux/kconfig.h  -I/root/kernel_asus_live_source/init -Iinit -D__KERNEL__ -mlittle-endian   -I/root/kernel_asus_live_source/arch/arm/mach-msm/include -DASUS_SW_VER=\"_ENG\" -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -Wno-maybe-uninitialized -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a15 -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(main)"  -D"KBUILD_MODNAME=KBUILD_STR(main)" -c -o init/.tmp_main.o /root/kernel_asus_live_source/init/main.c

source_init/main.o := /root/kernel_asus_live_source/init/main.c

deps_init/main.o := \
    $(wildcard include/config/x86/local/apic.h) \
    $(wildcard include/config/debug/rodata.h) \
    $(wildcard include/config/tc.h) \
    $(wildcard include/config/init/env/arg/limit.h) \
    $(wildcard include/config/asus/bsp/hw/id.h) \
    $(wildcard include/config/bsp/hw/sku/zb551kl.h) \
    $(wildcard include/config/bsp/hw/sku/zb501kl.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/blk/dev/initrd.h) \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/constructors.h) \
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
  /root/kernel_asus_live_source/include/linux/module.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  /root/kernel_asus_live_source/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /root/kernel_asus_live_source/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /root/kernel_asus_live_source/include/linux/const.h \
  /root/kernel_asus_live_source/include/linux/stat.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/stat.h \
  /root/kernel_asus_live_source/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /root/kernel_asus_live_source/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /root/kernel_asus_live_source/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
  /root/kernel_asus_live_source/include/linux/sysinfo.h \
  /root/Android/utulity/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include/stdarg.h \
  /root/kernel_asus_live_source/include/linux/linkage.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/linkage.h \
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
  /root/kernel_asus_live_source/arch/arm/include/asm/byteorder.h \
  /root/kernel_asus_live_source/include/linux/byteorder/little_endian.h \
  /root/kernel_asus_live_source/include/linux/swab.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/swab.h \
  /root/kernel_asus_live_source/include/linux/byteorder/generic.h \
  /root/kernel_asus_live_source/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /root/kernel_asus_live_source/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /root/kernel_asus_live_source/include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /root/kernel_asus_live_source/include/linux/init.h \
    $(wildcard include/config/hotplug.h) \
  /root/kernel_asus_live_source/include/linux/dynamic_debug.h \
  /root/kernel_asus_live_source/include/linux/asusdebug.h \
  /root/kernel_asus_live_source/include/linux/asusevtlog.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/div64.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/compiler.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  /root/kernel_asus_live_source/include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /root/kernel_asus_live_source/include/linux/seqlock.h \
  /root/kernel_asus_live_source/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /root/kernel_asus_live_source/include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  /root/kernel_asus_live_source/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/domain.h \
    $(wildcard include/config/verify/permission/fault.h) \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /root/kernel_asus_live_source/include/linux/stringify.h \
  /root/kernel_asus_live_source/include/linux/bottom_half.h \
  /root/kernel_asus_live_source/include/linux/spinlock_types.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/spinlock_types.h \
  /root/kernel_asus_live_source/include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  /root/kernel_asus_live_source/include/linux/rwlock_types.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/spinlock.h \
    $(wildcard include/config/msm/krait/wfe/fixup.h) \
    $(wildcard include/config/arm/ticket/locks.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/hw_breakpoint.h \
  /root/kernel_asus_live_source/include/linux/rwlock.h \
  /root/kernel_asus_live_source/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  /root/kernel_asus_live_source/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /root/kernel_asus_live_source/include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/atomic.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  /root/kernel_asus_live_source/include/asm-generic/cmpxchg-local.h \
  /root/kernel_asus_live_source/include/asm-generic/atomic-long.h \
  /root/kernel_asus_live_source/include/linux/math64.h \
  /root/kernel_asus_live_source/include/linux/kmod.h \
  /root/kernel_asus_live_source/include/linux/gfp.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/cma.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/pm/sleep.h) \
  /root/kernel_asus_live_source/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/have/memblock/node.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /root/kernel_asus_live_source/include/linux/wait.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/current.h \
  /root/kernel_asus_live_source/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /root/kernel_asus_live_source/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  /root/kernel_asus_live_source/include/linux/nodemask.h \
  /root/kernel_asus_live_source/include/linux/bitmap.h \
  /root/kernel_asus_live_source/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/string.h \
  /root/kernel_asus_live_source/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/kuser/helpers.h) \
    $(wildcard include/config/memory/hotplug/sparse.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/glue.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable-2level-types.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
  arch/arm/include/generated/asm/sizes.h \
  /root/kernel_asus_live_source/include/asm-generic/sizes.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/memory.h \
    $(wildcard include/config/arch/msm7x30.h) \
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
    $(wildcard include/config/sparsemem/vmemmap.h) \
  /root/kernel_asus_live_source/include/asm-generic/getorder.h \
  /root/kernel_asus_live_source/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  /root/kernel_asus_live_source/include/linux/notifier.h \
  /root/kernel_asus_live_source/include/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  /root/kernel_asus_live_source/include/asm-generic/errno.h \
  /root/kernel_asus_live_source/include/asm-generic/errno-base.h \
  /root/kernel_asus_live_source/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  /root/kernel_asus_live_source/include/linux/mutex-debug.h \
  /root/kernel_asus_live_source/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /root/kernel_asus_live_source/include/linux/rwsem-spinlock.h \
  /root/kernel_asus_live_source/include/linux/srcu.h \
  /root/kernel_asus_live_source/include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/preempt/rt.h) \
  /root/kernel_asus_live_source/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /root/kernel_asus_live_source/include/linux/bug.h \
    $(wildcard include/config/panic/on/data/corruption.h) \
  /root/kernel_asus_live_source/include/linux/completion.h \
  /root/kernel_asus_live_source/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /root/kernel_asus_live_source/include/linux/rcutree.h \
  /root/kernel_asus_live_source/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  /root/kernel_asus_live_source/include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/smp.h \
  /root/kernel_asus_live_source/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /root/kernel_asus_live_source/include/linux/pfn.h \
  arch/arm/include/generated/asm/percpu.h \
  /root/kernel_asus_live_source/include/asm-generic/percpu.h \
  /root/kernel_asus_live_source/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
  /root/kernel_asus_live_source/include/asm-generic/topology.h \
  /root/kernel_asus_live_source/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /root/kernel_asus_live_source/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  /root/kernel_asus_live_source/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /root/kernel_asus_live_source/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /root/kernel_asus_live_source/include/linux/jiffies.h \
  /root/kernel_asus_live_source/include/linux/timex.h \
  /root/kernel_asus_live_source/include/linux/param.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/timex.h \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/timex.h \
    $(wildcard include/config/have/arch/has/current/timer.h) \
  /root/kernel_asus_live_source/include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  /root/kernel_asus_live_source/include/linux/rbtree.h \
  /root/kernel_asus_live_source/include/linux/elf.h \
  /root/kernel_asus_live_source/include/linux/elf-em.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/elf.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/user.h \
  /root/kernel_asus_live_source/include/linux/kobject.h \
  /root/kernel_asus_live_source/include/linux/sysfs.h \
  /root/kernel_asus_live_source/include/linux/kobject_ns.h \
  /root/kernel_asus_live_source/include/linux/kref.h \
  /root/kernel_asus_live_source/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  /root/kernel_asus_live_source/include/linux/tracepoint.h \
  /root/kernel_asus_live_source/include/linux/static_key.h \
  /root/kernel_asus_live_source/include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /root/kernel_asus_live_source/include/linux/export.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \
  /root/kernel_asus_live_source/include/linux/proc_fs.h \
    $(wildcard include/config/proc/devicetree.h) \
    $(wildcard include/config/proc/kcore.h) \
  /root/kernel_asus_live_source/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/slab.h) \
  /root/kernel_asus_live_source/include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/slub/debug.h) \
  /root/kernel_asus_live_source/include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  /root/kernel_asus_live_source/include/linux/fs.h \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  /root/kernel_asus_live_source/include/linux/limits.h \
  /root/kernel_asus_live_source/include/linux/ioctl.h \
  arch/arm/include/generated/asm/ioctl.h \
  /root/kernel_asus_live_source/include/asm-generic/ioctl.h \
  /root/kernel_asus_live_source/include/linux/blk_types.h \
    $(wildcard include/config/blk/dev/integrity.h) \
  /root/kernel_asus_live_source/include/linux/kdev_t.h \
  /root/kernel_asus_live_source/include/linux/dcache.h \
  /root/kernel_asus_live_source/include/linux/rculist.h \
  /root/kernel_asus_live_source/include/linux/rculist_bl.h \
  /root/kernel_asus_live_source/include/linux/list_bl.h \
  /root/kernel_asus_live_source/include/linux/bit_spinlock.h \
  /root/kernel_asus_live_source/include/linux/path.h \
  /root/kernel_asus_live_source/include/linux/radix-tree.h \
  /root/kernel_asus_live_source/include/linux/prio_tree.h \
  /root/kernel_asus_live_source/include/linux/pid.h \
  /root/kernel_asus_live_source/include/linux/capability.h \
  /root/kernel_asus_live_source/include/linux/semaphore.h \
  /root/kernel_asus_live_source/include/linux/fiemap.h \
  /root/kernel_asus_live_source/include/linux/shrinker.h \
  /root/kernel_asus_live_source/include/linux/migrate_mode.h \
  /root/kernel_asus_live_source/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /root/kernel_asus_live_source/include/linux/percpu_counter.h \
  /root/kernel_asus_live_source/include/linux/dqblk_xfs.h \
  /root/kernel_asus_live_source/include/linux/dqblk_v1.h \
  /root/kernel_asus_live_source/include/linux/dqblk_v2.h \
  /root/kernel_asus_live_source/include/linux/dqblk_qtree.h \
  /root/kernel_asus_live_source/include/linux/nfs_fs_i.h \
  /root/kernel_asus_live_source/include/linux/fcntl.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/fcntl.h \
  /root/kernel_asus_live_source/include/asm-generic/fcntl.h \
  /root/kernel_asus_live_source/include/linux/err.h \
  /root/kernel_asus_live_source/include/linux/magic.h \
  /root/kernel_asus_live_source/include/linux/syscalls.h \
    $(wildcard include/config/ftrace/syscalls.h) \
    $(wildcard include/config/mips.h) \
    $(wildcard include/config/have/syscall/wrappers.h) \
  /root/kernel_asus_live_source/include/linux/aio_abi.h \
  /root/kernel_asus_live_source/include/linux/sem.h \
    $(wildcard include/config/sysvipc.h) \
  /root/kernel_asus_live_source/include/linux/ipc.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/ipcbuf.h \
  /root/kernel_asus_live_source/include/asm-generic/ipcbuf.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/sembuf.h \
  arch/arm/include/generated/asm/siginfo.h \
  /root/kernel_asus_live_source/include/asm-generic/siginfo.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/signal.h \
  /root/kernel_asus_live_source/include/asm-generic/signal-defs.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/sigcontext.h \
  /root/kernel_asus_live_source/include/linux/unistd.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/oabi/compat.h) \
  /root/kernel_asus_live_source/include/linux/key.h \
    $(wildcard include/config/keys.h) \
  /root/kernel_asus_live_source/include/trace/syscall.h \
    $(wildcard include/config/perf/events.h) \
  /root/kernel_asus_live_source/include/linux/ftrace_event.h \
  /root/kernel_asus_live_source/include/linux/ring_buffer.h \
    $(wildcard include/config/ring/buffer/allow/swap.h) \
  /root/kernel_asus_live_source/include/linux/kmemcheck.h \
  /root/kernel_asus_live_source/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mm/owner.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/transparent/hugepage.h) \
  /root/kernel_asus_live_source/include/linux/auxvec.h \
  arch/arm/include/generated/asm/auxvec.h \
  /root/kernel_asus_live_source/include/asm-generic/auxvec.h \
  /root/kernel_asus_live_source/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
  /root/kernel_asus_live_source/include/linux/mm.h \
    $(wildcard include/config/fix/movable/zone.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/use/user/accessible/timers.h) \
    $(wildcard include/config/hugetlbfs.h) \
  /root/kernel_asus_live_source/include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /root/kernel_asus_live_source/include/linux/range.h \
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
    $(wildcard include/config/cpu/arm1020.h) \
    $(wildcard include/config/cpu/arm1020e.h) \
    $(wildcard include/config/cpu/arm1022.h) \
    $(wildcard include/config/cpu/arm1026.h) \
    $(wildcard include/config/cpu/mohawk.h) \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/cpu/v6k.h) \
    $(wildcard include/config/cpu/v7.h) \
  /root/kernel_asus_live_source/include/asm-generic/pgtable-nopud.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable-hwdef.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable-2level-hwdef.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/pgtable-2level.h \
  /root/kernel_asus_live_source/include/asm-generic/pgtable.h \
  /root/kernel_asus_live_source/include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/s390.h) \
  /root/kernel_asus_live_source/include/linux/huge_mm.h \
  /root/kernel_asus_live_source/include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  /root/kernel_asus_live_source/include/linux/vm_event_item.h \
  /root/kernel_asus_live_source/include/linux/seq_file.h \
  /root/kernel_asus_live_source/include/linux/trace_seq.h \
  /root/kernel_asus_live_source/include/linux/hardirq.h \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/irq/time/accounting.h) \
  /root/kernel_asus_live_source/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/hardirq.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/irq.h \
    $(wildcard include/config/sparse/irq.h) \
  /root/kernel_asus_live_source/include/linux/irq_cpustat.h \
  /root/kernel_asus_live_source/include/linux/perf_event.h \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/function/tracer.h) \
  /root/kernel_asus_live_source/include/linux/cgroup.h \
    $(wildcard include/config/cgroups.h) \
  /root/kernel_asus_live_source/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/cfs/bandwidth.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/cgroup/sched.h) \
  arch/arm/include/generated/asm/cputime.h \
  /root/kernel_asus_live_source/include/asm-generic/cputime.h \
  /root/kernel_asus_live_source/include/linux/signal.h \
  /root/kernel_asus_live_source/include/linux/proportions.h \
  /root/kernel_asus_live_source/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  /root/kernel_asus_live_source/include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /root/kernel_asus_live_source/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /root/kernel_asus_live_source/include/linux/resource.h \
  arch/arm/include/generated/asm/resource.h \
  /root/kernel_asus_live_source/include/asm-generic/resource.h \
  /root/kernel_asus_live_source/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  /root/kernel_asus_live_source/include/linux/timerqueue.h \
  /root/kernel_asus_live_source/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /root/kernel_asus_live_source/include/linux/latencytop.h \
  /root/kernel_asus_live_source/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/user/ns.h) \
  /root/kernel_asus_live_source/include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  /root/kernel_asus_live_source/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /root/kernel_asus_live_source/include/linux/aio.h \
  /root/kernel_asus_live_source/include/linux/uio.h \
  /root/kernel_asus_live_source/include/linux/cgroupstats.h \
  /root/kernel_asus_live_source/include/linux/taskstats.h \
  /root/kernel_asus_live_source/include/linux/prio_heap.h \
  /root/kernel_asus_live_source/include/linux/idr.h \
  /root/kernel_asus_live_source/include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/debug.h) \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/net/cls/cgroup.h) \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/netprio/cgroup.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/perf_event.h \
  arch/arm/include/generated/asm/local64.h \
  /root/kernel_asus_live_source/include/asm-generic/local64.h \
  /root/kernel_asus_live_source/include/linux/pid_namespace.h \
    $(wildcard include/config/pid/ns.h) \
  /root/kernel_asus_live_source/include/linux/nsproxy.h \
  /root/kernel_asus_live_source/include/linux/ftrace.h \
    $(wildcard include/config/dynamic/ftrace.h) \
    $(wildcard include/config/stack/tracer.h) \
    $(wildcard include/config/frame/pointer.h) \
  /root/kernel_asus_live_source/include/linux/trace_clock.h \
  /root/kernel_asus_live_source/include/linux/kallsyms.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/ftrace.h \
    $(wildcard include/config/old/mcount.h) \
  /root/kernel_asus_live_source/include/linux/cpu.h \
    $(wildcard include/config/arch/has/cpu/autoprobe.h) \
    $(wildcard include/config/arch/cpu/probe/release.h) \
    $(wildcard include/config/pm/sleep/smp.h) \
  /root/kernel_asus_live_source/include/linux/node.h \
  /root/kernel_asus_live_source/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /root/kernel_asus_live_source/include/linux/ioport.h \
  /root/kernel_asus_live_source/include/linux/klist.h \
  /root/kernel_asus_live_source/include/linux/pinctrl/devinfo.h \
  /root/kernel_asus_live_source/include/linux/pm.h \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
    $(wildcard include/config/iommu/api.h) \
    $(wildcard include/config/arm/dma/use/iommu.h) \
    $(wildcard include/config/arch/omap.h) \
  /root/kernel_asus_live_source/include/linux/pm_wakeup.h \
  /root/kernel_asus_live_source/include/linux/irq_work.h \
  arch/arm/include/generated/asm/local.h \
  /root/kernel_asus_live_source/include/asm-generic/local.h \
  /root/kernel_asus_live_source/include/linux/stackprotector.h \
  /root/kernel_asus_live_source/include/linux/random.h \
    $(wildcard include/config/arch/random.h) \
  /root/kernel_asus_live_source/include/linux/irqnr.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/stackprotector.h \
  include/linux/version.h \
  /root/kernel_asus_live_source/include/linux/ctype.h \
  /root/kernel_asus_live_source/include/linux/delay.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/delay.h \
  /root/kernel_asus_live_source/include/linux/initrd.h \
  /root/kernel_asus_live_source/include/linux/bootmem.h \
    $(wildcard include/config/have/arch/bootmem/node.h) \
    $(wildcard include/config/have/arch/alloc/remap.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/dma.h \
    $(wildcard include/config/isa/dma/api.h) \
    $(wildcard include/config/pci.h) \
  /root/kernel_asus_live_source/include/linux/acpi.h \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/acpi/hotplug/cpu.h) \
    $(wildcard include/config/x86/io/apic.h) \
    $(wildcard include/config/acpi/wmi.h) \
    $(wildcard include/config/acpi/video.h) \
    $(wildcard include/config/acpi/numa.h) \
    $(wildcard include/config/support.h) \
  /root/kernel_asus_live_source/include/linux/tty.h \
  /root/kernel_asus_live_source/include/linux/major.h \
  /root/kernel_asus_live_source/include/linux/termios.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/termios.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/termbits.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/ioctls.h \
  /root/kernel_asus_live_source/include/asm-generic/ioctls.h \
  /root/kernel_asus_live_source/include/linux/tty_driver.h \
    $(wildcard include/config/console/poll.h) \
  /root/kernel_asus_live_source/include/linux/cdev.h \
  /root/kernel_asus_live_source/include/linux/tty_ldisc.h \
  /root/kernel_asus_live_source/include/linux/pps_kernel.h \
    $(wildcard include/config/ntp/pps.h) \
  /root/kernel_asus_live_source/include/linux/pps.h \
  /root/kernel_asus_live_source/include/linux/vmalloc.h \
    $(wildcard include/config/enable/vmalloc/saving.h) \
  /root/kernel_asus_live_source/include/linux/kernel_stat.h \
  /root/kernel_asus_live_source/include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  /root/kernel_asus_live_source/include/linux/irqreturn.h \
  /root/kernel_asus_live_source/include/linux/irq.h \
    $(wildcard include/config/irq/release/method.h) \
    $(wildcard include/config/generic/pending/irq.h) \
  arch/arm/include/generated/asm/irq_regs.h \
  /root/kernel_asus_live_source/include/asm-generic/irq_regs.h \
  /root/kernel_asus_live_source/include/linux/irqdesc.h \
    $(wildcard include/config/irq/preflow/fasteoi.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/hw_irq.h \
  /root/kernel_asus_live_source/include/linux/start_kernel.h \
  /root/kernel_asus_live_source/include/linux/security.h \
    $(wildcard include/config/security/path.h) \
    $(wildcard include/config/security/network.h) \
    $(wildcard include/config/security/network/xfrm.h) \
    $(wildcard include/config/securityfs.h) \
  /root/kernel_asus_live_source/include/linux/bio.h \
  /root/kernel_asus_live_source/include/linux/highmem.h \
    $(wildcard include/config/arch/want/kmap/atomic/flush.h) \
    $(wildcard include/config/x86/32.h) \
    $(wildcard include/config/debug/highmem.h) \
  /root/kernel_asus_live_source/include/linux/uaccess.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/uaccess.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/cacheflush.h \
    $(wildcard include/config/smp/on/up.h) \
    $(wildcard include/config/arm/errata/411920.h) \
    $(wildcard include/config/cpu/cache/vipt.h) \
    $(wildcard include/config/free/pages/rdonly.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/glue-cache.h \
    $(wildcard include/config/cpu/cache/v3.h) \
    $(wildcard include/config/cpu/cache/v4.h) \
    $(wildcard include/config/cpu/cache/v4wb.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/shmparam.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/cachetype.h \
    $(wildcard include/config/cpu/cache/vivt.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/kmap_types.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/highmem.h \
    $(wildcard include/config/cpu/tlb/v6.h) \
  /root/kernel_asus_live_source/include/linux/mempool.h \
  /root/kernel_asus_live_source/include/linux/ioprio.h \
  /root/kernel_asus_live_source/include/linux/iocontext.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/io.h \
    $(wildcard include/config/need/mach/io/h.h) \
    $(wildcard include/config/pcmcia/soc/common.h) \
    $(wildcard include/config/isa.h) \
    $(wildcard include/config/pccard.h) \
  /root/kernel_asus_live_source/include/asm-generic/pci_iomap.h \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/msm_rtb.h \
    $(wildcard include/config/msm/rtb.h) \
  /root/kernel_asus_live_source/arch/arm/mach-msm/include/mach/io.h \
  /root/kernel_asus_live_source/include/linux/profile.h \
    $(wildcard include/config/profiling.h) \
  /root/kernel_asus_live_source/include/linux/writeback.h \
  /root/kernel_asus_live_source/include/linux/cpuset.h \
  /root/kernel_asus_live_source/include/linux/efi.h \
    $(wildcard include/config/efi/pcdp.h) \
    $(wildcard include/config/efi.h) \
    $(wildcard include/config/efi/vars.h) \
  /root/kernel_asus_live_source/include/linux/rtc.h \
    $(wildcard include/config/rtc/intf/dev/uie/emul.h) \
    $(wildcard include/config/rtc/hctosys.h) \
  /root/kernel_asus_live_source/include/linux/poll.h \
  arch/arm/include/generated/asm/poll.h \
  /root/kernel_asus_live_source/include/asm-generic/poll.h \
  /root/kernel_asus_live_source/include/linux/pstore.h \
    $(wildcard include/config/pstore.h) \
  /root/kernel_asus_live_source/include/linux/kmsg_dump.h \
  /root/kernel_asus_live_source/include/linux/tick.h \
    $(wildcard include/config/generic/clockevents.h) \
    $(wildcard include/config/generic/clockevents/broadcast.h) \
    $(wildcard include/config/tick/oneshot.h) \
  /root/kernel_asus_live_source/include/linux/clockchips.h \
    $(wildcard include/config/generic/clockevents/build.h) \
  /root/kernel_asus_live_source/include/linux/clocksource.h \
    $(wildcard include/config/arch/clocksource/data.h) \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/generic/time/vsyscall.h) \
  /root/kernel_asus_live_source/include/linux/taskstats_kern.h \
  /root/kernel_asus_live_source/include/linux/delayacct.h \
  /root/kernel_asus_live_source/include/linux/rmap.h \
  /root/kernel_asus_live_source/include/linux/memcontrol.h \
    $(wildcard include/config/cgroup/mem/res/ctlr/swap.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr/kmem.h) \
  /root/kernel_asus_live_source/include/linux/mempolicy.h \
    $(wildcard include/config/tmpfs.h) \
  /root/kernel_asus_live_source/include/linux/pagemap.h \
  /root/kernel_asus_live_source/include/linux/hugetlb_inline.h \
  /root/kernel_asus_live_source/include/linux/buffer_head.h \
  /root/kernel_asus_live_source/include/linux/page_cgroup.h \
  /root/kernel_asus_live_source/include/linux/swap.h \
  /root/kernel_asus_live_source/include/linux/kthread.h \
  /root/kernel_asus_live_source/include/linux/kgdb.h \
    $(wildcard include/config/have/arch/kgdb.h) \
    $(wildcard include/config/kgdb.h) \
  /root/kernel_asus_live_source/include/linux/serial_8250.h \
  /root/kernel_asus_live_source/include/linux/serial_core.h \
    $(wildcard include/config/type.h) \
    $(wildcard include/config/irq.h) \
    $(wildcard include/config/serial/core/console.h) \
  /root/kernel_asus_live_source/include/linux/serial.h \
  /root/kernel_asus_live_source/include/linux/circ_buf.h \
  /root/kernel_asus_live_source/include/linux/sysrq.h \
    $(wildcard include/config/magic/sysrq.h) \
  /root/kernel_asus_live_source/include/linux/platform_device.h \
    $(wildcard include/config/suspend.h) \
    $(wildcard include/config/hibernate/callbacks.h) \
  /root/kernel_asus_live_source/include/linux/mod_devicetable.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/kgdb.h \
  /root/kernel_asus_live_source/include/linux/ptrace.h \
  /root/kernel_asus_live_source/include/linux/async.h \
  /root/kernel_asus_live_source/include/linux/sfi.h \
    $(wildcard include/config/sfi.h) \
  /root/kernel_asus_live_source/include/linux/shmem_fs.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/bugs.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/setup.h \
    $(wildcard include/config/arm/nr/banks.h) \
  arch/arm/include/generated/asm/sections.h \
  /root/kernel_asus_live_source/include/asm-generic/sections.h \

init/main.o: $(deps_init/main.o)

$(deps_init/main.o):
