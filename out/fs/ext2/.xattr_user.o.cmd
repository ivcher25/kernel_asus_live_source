cmd_fs/ext2/xattr_user.o := /root/kernel_asus_live_source/scripts/gcc-wrapper.py /root/Android/utulity/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,fs/ext2/.xattr_user.o.d  -nostdinc -isystem /root/Android/utulity/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/root/kernel_asus_live_source/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/root/kernel_asus_live_source/include -include /root/kernel_asus_live_source/include/linux/kconfig.h  -I/root/kernel_asus_live_source/fs/ext2 -Ifs/ext2 -D__KERNEL__ -mlittle-endian   -I/root/kernel_asus_live_source/arch/arm/mach-msm/include -DASUS_SW_VER=\"_ENG\" -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -Wno-maybe-uninitialized -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a15 -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(xattr_user)"  -D"KBUILD_MODNAME=KBUILD_STR(ext2)" -c -o fs/ext2/.tmp_xattr_user.o /root/kernel_asus_live_source/fs/ext2/xattr_user.c

source_fs/ext2/xattr_user.o := /root/kernel_asus_live_source/fs/ext2/xattr_user.c

deps_fs/ext2/xattr_user.o := \
  /root/kernel_asus_live_source/include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
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
  /root/kernel_asus_live_source/arch/arm/include/asm/posix_types.h \
  /root/kernel_asus_live_source/include/asm-generic/posix_types.h \
  /root/kernel_asus_live_source/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /root/Android/utulity/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include/stdarg.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/string.h \
  /root/kernel_asus_live_source/fs/ext2/ext2.h \
    $(wildcard include/config/ext2/fs/xattr.h) \
  /root/kernel_asus_live_source/include/linux/fs.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  /root/kernel_asus_live_source/include/linux/limits.h \
  /root/kernel_asus_live_source/include/linux/ioctl.h \
  arch/arm/include/generated/asm/ioctl.h \
  /root/kernel_asus_live_source/include/asm-generic/ioctl.h \
  /root/kernel_asus_live_source/include/linux/blk_types.h \
    $(wildcard include/config/blk/dev/integrity.h) \
  /root/kernel_asus_live_source/include/linux/linkage.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/linkage.h \
  /root/kernel_asus_live_source/include/linux/wait.h \
    $(wildcard include/config/lockdep.h) \
  /root/kernel_asus_live_source/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /root/kernel_asus_live_source/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /root/kernel_asus_live_source/include/linux/const.h \
  /root/kernel_asus_live_source/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /root/kernel_asus_live_source/include/linux/typecheck.h \
  /root/kernel_asus_live_source/include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  /root/kernel_asus_live_source/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /root/kernel_asus_live_source/include/linux/bitops.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/bitops.h \
  /root/kernel_asus_live_source/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
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
  /root/kernel_asus_live_source/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/bsp/hw/sku/zb551kl.h) \
    $(wildcard include/config/bsp/hw/sku/zb501kl.h) \
  /root/kernel_asus_live_source/include/linux/sysinfo.h \
  /root/kernel_asus_live_source/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /root/kernel_asus_live_source/include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
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
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /root/kernel_asus_live_source/include/linux/stringify.h \
  /root/kernel_asus_live_source/include/linux/bottom_half.h \
  /root/kernel_asus_live_source/include/linux/spinlock_types.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/spinlock_types.h \
  /root/kernel_asus_live_source/include/linux/lockdep.h \
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
  /root/kernel_asus_live_source/arch/arm/include/asm/current.h \
  /root/kernel_asus_live_source/include/linux/kdev_t.h \
  /root/kernel_asus_live_source/include/linux/dcache.h \
  /root/kernel_asus_live_source/include/linux/rculist.h \
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
  /root/kernel_asus_live_source/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /root/kernel_asus_live_source/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /root/kernel_asus_live_source/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /root/kernel_asus_live_source/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /root/kernel_asus_live_source/include/linux/bitmap.h \
  /root/kernel_asus_live_source/include/linux/bug.h \
    $(wildcard include/config/panic/on/data/corruption.h) \
  /root/kernel_asus_live_source/include/linux/seqlock.h \
  /root/kernel_asus_live_source/include/linux/completion.h \
  /root/kernel_asus_live_source/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /root/kernel_asus_live_source/include/linux/rcutree.h \
  /root/kernel_asus_live_source/include/linux/rculist_bl.h \
  /root/kernel_asus_live_source/include/linux/list_bl.h \
  /root/kernel_asus_live_source/include/linux/bit_spinlock.h \
  /root/kernel_asus_live_source/include/linux/path.h \
  /root/kernel_asus_live_source/include/linux/stat.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/stat.h \
  /root/kernel_asus_live_source/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /root/kernel_asus_live_source/include/linux/math64.h \
  /root/kernel_asus_live_source/include/linux/radix-tree.h \
  /root/kernel_asus_live_source/include/linux/prio_tree.h \
  /root/kernel_asus_live_source/include/linux/pid.h \
  /root/kernel_asus_live_source/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  /root/kernel_asus_live_source/include/linux/mutex-debug.h \
  /root/kernel_asus_live_source/include/linux/capability.h \
  /root/kernel_asus_live_source/include/linux/semaphore.h \
  /root/kernel_asus_live_source/include/linux/fiemap.h \
  /root/kernel_asus_live_source/include/linux/shrinker.h \
  /root/kernel_asus_live_source/include/linux/migrate_mode.h \
  /root/kernel_asus_live_source/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /root/kernel_asus_live_source/include/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  /root/kernel_asus_live_source/include/asm-generic/errno.h \
  /root/kernel_asus_live_source/include/asm-generic/errno-base.h \
  /root/kernel_asus_live_source/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /root/kernel_asus_live_source/include/linux/rwsem-spinlock.h \
  /root/kernel_asus_live_source/include/linux/percpu_counter.h \
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
  /root/kernel_asus_live_source/include/linux/dqblk_xfs.h \
  /root/kernel_asus_live_source/include/linux/dqblk_v1.h \
  /root/kernel_asus_live_source/include/linux/dqblk_v2.h \
  /root/kernel_asus_live_source/include/linux/dqblk_qtree.h \
  /root/kernel_asus_live_source/include/linux/nfs_fs_i.h \
  /root/kernel_asus_live_source/include/linux/fcntl.h \
  /root/kernel_asus_live_source/arch/arm/include/asm/fcntl.h \
  /root/kernel_asus_live_source/include/asm-generic/fcntl.h \
  /root/kernel_asus_live_source/include/linux/err.h \
  /root/kernel_asus_live_source/include/linux/ext2_fs.h \
  /root/kernel_asus_live_source/include/linux/magic.h \
  /root/kernel_asus_live_source/include/linux/blockgroup_lock.h \
  /root/kernel_asus_live_source/include/linux/rbtree.h \
  /root/kernel_asus_live_source/fs/ext2/xattr.h \
    $(wildcard include/config/ext2/fs/security.h) \
  /root/kernel_asus_live_source/include/linux/xattr.h \

fs/ext2/xattr_user.o: $(deps_fs/ext2/xattr_user.o)

$(deps_fs/ext2/xattr_user.o):
