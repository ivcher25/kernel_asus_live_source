/* //20100930 jack_wong for asus debug mechanisms +++++
 *  asusdebug.c
 * //20100930 jack_wong for asus debug mechanisms -----
 *
 */

#include <linux/delay.h>
#include <linux/earlysuspend.h>
#include <linux/export.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/rtc.h>
#include <linux/syscalls.h>
#include <linux/time.h>
#include <linux/types.h>
#include <linux/workqueue.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include "rtmutex_common.h"

#define ASDF_ROOT_DIR "/asdf/"
#define SPLIT_NS(x) nsec_high(x), nsec_low(x)

unsigned int PRINTK_BUFFER = 0x1FF00000;
unsigned int RTB_BUFFER = 0x1FF00000 + SZ_1M;
ulong logcat_buffer_index = 0; /* ASUS_BSP Paul +++ */
int entering_suspend = 0;
int first = 0;
static char* g_phonehang_log;
static int g_iPtr = 0;
static int g_read_pos;
unsigned int asusdebug_enable = 0;
unsigned int readflag = 0;

extern struct timezone sys_tz;
extern int nSuspendInProgress;
extern struct timezone sys_tz;
// ASUS_BSP +++
extern u8 download_mode_value;
char evtlog_bootup_reason[100];
char evtlog_poweroff_reason[100];
char evtlog_warm_reset_reason[100];
extern u16 warm_reset_value;
// ASUS_BSP ---

struct mutex fake_mutex;
struct completion fake_completion;
struct rt_mutex fake_rtmutex;
struct workqueue_struct *ASUSDebugMsg_workQueue;
struct thread_info_save;
struct stackframe;
struct stack_trace;
struct thread_info_save *ptis_head = NULL;

int unwind_frame(struct stackframe *frame);
void notrace walk_stackframe(struct stackframe *frame,
			 int (*fn)(struct stackframe *, void *), void *data);
void save_stack_trace_asus(struct task_struct *tsk, struct stack_trace *trace);
void printk_buffer_rebase(void);

/*ASUS-BBSP SubSys Health Record+++*/
static struct workqueue_struct *ASUSSubsys_workQueue;
static char g_SubSys_W_Buf[SUBSYS_W_MAXLEN];
static char g_SubSys_C_Buf[SUBSYS_C_MAXLEN]="0000-0000-0000-0000-0000";
static void do_write_subsys_worker(struct work_struct *work);
static void do_count_subsys_worker(struct work_struct *work);
static void do_delete_subsys_worker(struct work_struct *work);
static DECLARE_WORK(subsys_w_Work, do_write_subsys_worker);
static DECLARE_WORK(subsys_c_Work, do_count_subsys_worker);
static DECLARE_WORK(subsys_d_Work, do_delete_subsys_worker);
static struct completion SubSys_C_Complete;
/*ASUS-BBSP SubSys Health Record---*/
/* ASUS_BSP Paul +++ */
static struct kset *dropbox_uevent_kset;
static struct kobject *ssr_reason_kobj;
static struct work_struct send_ssr_reason_dropbox_uevent_work;
static void send_ssr_reason_dropbox_uevent_work_handler(struct work_struct *work);
/* ASUS_BSP Paul --- */

int asus_rtc_read_time(struct rtc_time *tm)
{
	struct timespec ts;

	getnstimeofday(&ts);
	ts.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(ts.tv_sec, tm);
	printk("now %04d%02d%02d-%02d%02d%02d, tz=%d\r\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, sys_tz.tz_minuteswest);
	return 0;
}
EXPORT_SYMBOL(asus_rtc_read_time);
EXPORT_SYMBOL(ASUSDebugMsg_workQueue);

////////////////////////////////////////////////////////////////////////
//                    all thread information
////////////////////////////////////////////////////////////////////////

/*
 * memset for non cached memory
 */
void *memset_nc(void *s, int c, size_t count)
{
	u8 *p = s;
	while (count--)
		*p++ = c;
	return s;
}
EXPORT_SYMBOL(memset_nc);

/*
 *memcpy for non cached memory
 */
void *memcpy_nc(void *dest, const void *src, size_t n)
{
    int i = 0;
    u8 *d = (u8 *)dest, *s = (u8 *)src;
    for (i = 0; i < n; i++)
        d[i] = s[i];

    return dest;
}
EXPORT_SYMBOL(memcpy_nc);
int save_log(const char *f, ...)
{
	va_list args;
	int len;

	if (g_iPtr < PHONE_HANG_LOG_SIZE) {
		va_start(args, f);
		len = vsnprintf(g_phonehang_log + g_iPtr, PHONE_HANG_LOG_SIZE - g_iPtr, f, args);
		va_end(args);
		if (g_iPtr < PHONE_HANG_LOG_SIZE) {
			g_iPtr += len;
			return 0;
		}
	}
	g_iPtr = PHONE_HANG_LOG_SIZE;
	return -1;
}

static char *task_state_array[] = {
	"RUNNING",			/*  0 */
	"INTERRUPTIBLE",	/*  1 */
	"UNINTERRUPTIB",	/*  2 */
	"STOPPED",			/*  4 */
	"TRACED",			/*  8 */
	"EXIT ZOMBIE",		/* 16 */
	"EXIT DEAD",		/* 32 */
	"DEAD",				/* 64 */
	"WAKEKILL",			/* 128 */
	"WAKING"			/* 256 */
};

struct thread_info_save
{
	struct task_struct *pts;
	pid_t pid;
	u64 sum_exec_runtime;
	u64 vruntime;
	struct thread_info_save* pnext;
};
static char* print_state(long state)
{   
	int i;
	if (state == 0)
		return task_state_array[0];

	for(i = 1; i <= 16; i++) {
		if (1<<(i-1) & state)
			return task_state_array[i];
	}
	return "NOTFOUND";

}

/*
 * Ease the printing of nsec fields:
 */
static long long nsec_high(unsigned long long nsec)
{
	if ((long long)nsec < 0) {
		nsec = -nsec;
		do_div(nsec, 1000000);
		return -nsec;
	}
	do_div(nsec, 1000000);

	return nsec;
}

static unsigned long nsec_low(unsigned long long nsec)
{
	unsigned long long nsec1;
	if ((long long)nsec < 0)
		nsec = -nsec;

	nsec1 =  do_div(nsec, 1000000);
	return do_div(nsec1, 1000000);
}
#define MAX_STACK_TRACE_DEPTH   64
struct stack_trace {
	unsigned int nr_entries, max_entries;
	unsigned long *entries;
	int skip;   /* input argument: How many entries to skip */
};

struct stack_trace_data {
	struct stack_trace *trace;
	unsigned int no_sched_functions;
	unsigned int skip;
};

struct stackframe {
	unsigned long fp;
	unsigned long sp;
	unsigned long lr;
	unsigned long pc;
};

void show_stack1(struct task_struct *p1, void *p2)
{
	struct stack_trace trace;
	unsigned long *entries;
	int i;

	entries = kmalloc(MAX_STACK_TRACE_DEPTH * sizeof(*entries), GFP_KERNEL);
	if (!entries) {
		printk("entries malloc failure\n");
		return;
	}
	trace.nr_entries	= 0;
	trace.max_entries   = MAX_STACK_TRACE_DEPTH;
	trace.entries	   = entries;
	trace.skip	  = 0;
	save_stack_trace_asus(p1, &trace);

	for (i = 0; i < trace.nr_entries; i++) {
		save_log("[<%p>] %pS\n", (void *)entries[i], (void *)entries[i]);
	}
	kfree(entries);
}

void print_all_thread_info(void)
{
	struct task_struct *pts;
	struct thread_info *pti;
	struct rtc_time tm;
	asus_rtc_read_time(&tm);

	#if 1
	g_phonehang_log = (char*)PHONE_HANG_LOG_BUFFER;//phys_to_virt(PHONE_HANG_LOG_BUFFER);
	g_iPtr = 0;
	memset(g_phonehang_log, 0, PHONE_HANG_LOG_SIZE);
	#endif

	save_log("PhoneHang-%04d%02d%02d-%02d%02d%02d.txt  ---  ASUS_SW_VER : %s----------------------------------------------\r\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ASUS_SW_VER);
	save_log(" pID----ppID----NAME----------------SumTime---vruntime--SPri-NPri-State----------PmpCnt-Binder----Waiting\r\n");

	for_each_process(pts) {
		pti = (struct thread_info *)((int)(pts->stack)  & ~(THREAD_SIZE - 1));
		save_log("-----------------------------------------------------\r\n");
		save_log(" %-7d", pts->pid);

		if (pts->parent)
			save_log("%-8d", pts->parent->pid);
		else
			save_log("%-8d", 0);

		save_log("%-20s", pts->comm);
		save_log("%lld.%06ld", SPLIT_NS(pts->se.sum_exec_runtime));
		save_log("     %lld.%06ld     ", SPLIT_NS(pts->se.vruntime));
		save_log("%-5d", pts->static_prio);
		save_log("%-5d", pts->normal_prio);
		save_log("%-15s", print_state((pts->state & TASK_REPORT) | pts->exit_state));
		save_log("%-6d", pti->preempt_count);

		if (pti->pWaitingMutex != &fake_mutex && pti->pWaitingMutex != NULL) {
			if (pti->pWaitingMutex->name) {
				save_log("    Mutex:%s,", pti->pWaitingMutex->name + 1);
				printk("    Mutex:%s,", pti->pWaitingMutex->name + 1);
			} else {
				printk("pti->pWaitingMutex->name == NULL\r\n");
			}

			if (pti->pWaitingMutex->mutex_owner_asusdebug) {
				save_log(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
				printk(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
			} else {
				printk("pti->pWaitingMutex->mutex_owner_asusdebug == NULL\r\n");
			}

			if (pti->pWaitingMutex->mutex_owner_asusdebug->comm) {
				save_log(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
				printk(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
			} else {
				printk("pti->pWaitingMutex->mutex_owner_asusdebug->comm == NULL\r\n");
			}
		}

		if (pti->pWaitingCompletion != &fake_completion && pti->pWaitingCompletion!=NULL) {
			if (pti->pWaitingCompletion->name)
				save_log("    Completion:wait_for_completion %s", pti->pWaitingCompletion->name );
			else
				printk("pti->pWaitingCompletion->name == NULL\r\n");
		}

		if (pti->pWaitingRTMutex != &fake_rtmutex && pti->pWaitingRTMutex != NULL) {
			struct task_struct *temp = rt_mutex_owner(pti->pWaitingRTMutex);
			if (temp)
				save_log("	RTMutex: Owned by pID(%d)", temp->pid);
			else
				printk("pti->pWaitingRTMutex->temp == NULL\r\n");

			if (temp->comm)
				save_log(" %s", temp->pid, temp->comm);
			else
				printk("pti->pWaitingRTMutex->temp->comm == NULL\r\n");
		}

		save_log("\r\n");
		show_stack1(pts, NULL);

		save_log("\r\n");

		if (!thread_group_empty(pts)) {
			struct task_struct *p1 = next_thread(pts);
			do {
				pti = (struct thread_info *)((int)(p1->stack)  & ~(THREAD_SIZE - 1));
				save_log(" %-7d", p1->pid);

				if (pts->parent)
					save_log("%-8d", p1->parent->pid);
				else
					save_log("%-8d", 0);

				save_log("%-20s", p1->comm);
				save_log("%lld.%06ld", SPLIT_NS(p1->se.sum_exec_runtime));
				save_log("     %lld.%06ld     ", SPLIT_NS(p1->se.vruntime));
				save_log("%-5d", p1->static_prio);
				save_log("%-5d", p1->normal_prio);
				save_log("%-15s", print_state((p1->state & TASK_REPORT) | p1->exit_state));
				save_log("%-6d", pti->preempt_count);

				if (pti->pWaitingMutex != &fake_mutex && pti->pWaitingMutex != NULL) {
					if (pti->pWaitingMutex->name) {
						save_log("    Mutex:%s,", pti->pWaitingMutex->name + 1);
						printk("    Mutex:%s,", pti->pWaitingMutex->name + 1);
					} else {
						printk("pti->pWaitingMutex->name == NULL\r\n");
					}

					if (pti->pWaitingMutex->mutex_owner_asusdebug) {
						save_log(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
						printk(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
					} else {
						printk("pti->pWaitingMutex->mutex_owner_asusdebug == NULL\r\n");
					}

					if (pti->pWaitingMutex->mutex_owner_asusdebug->comm) {
						save_log(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
						printk(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
					} else {
						printk("pti->pWaitingMutex->mutex_owner_asusdebug->comm == NULL\r\n");
					}
				}

				if (pti->pWaitingCompletion != &fake_completion && pti->pWaitingCompletion!=NULL) {
					if (pti->pWaitingCompletion->name)
						save_log("    Completion:wait_for_completion %s", pti->pWaitingCompletion->name );
					else
						printk("pti->pWaitingCompletion->name == NULL\r\n");
				}

				if (pti->pWaitingRTMutex != &fake_rtmutex && pti->pWaitingRTMutex != NULL) {
					struct task_struct *temp = rt_mutex_owner(pti->pWaitingRTMutex);
					if (temp)
						save_log("	RTMutex: Owned by pID(%d)", temp->pid);
					else
						printk("pti->pWaitingRTMutex->temp == NULL\r\n");
					if (temp->comm)
						save_log(" %s", temp->pid, temp->comm);
					else
						printk("pti->pWaitingRTMutex->temp->comm == NULL\r\n");
				}
				save_log("\r\n");
				show_stack1(p1, NULL);
				save_log("\r\n");
				p1 = next_thread(p1);
			} while(p1 != pts);
		}
		save_log("-----------------------------------------------------\r\n\r\n\r\n");
	}
	save_log("\r\n\r\n\r\n\r\n");
}

int find_thread_info(struct task_struct *pts, int force)
{
	struct thread_info *pti;
	struct thread_info_save *ptis, *ptis_ptr;
	u64 vruntime = 0, sum_exec_runtime;

	if (ptis_head != NULL) {
		ptis = ptis_head->pnext;
		ptis_ptr = NULL;
		while(ptis) {
			if (ptis->pid == pts->pid && ptis->pts == pts) {
				ptis_ptr = ptis;
				break;
			}
			ptis = ptis->pnext;
		}
		if (ptis_ptr) {
			sum_exec_runtime = pts->se.sum_exec_runtime - ptis->sum_exec_runtime;
		} else {
			sum_exec_runtime = pts->se.sum_exec_runtime;
		}

		if (sum_exec_runtime > 0 || force) {
			pti = (struct thread_info *)((int)(pts->stack)  & ~(THREAD_SIZE - 1));
			save_log(" %-7d", pts->pid);

			if (pts->parent)
				save_log("%-8d", pts->parent->pid);
			else
				save_log("%-8d", 0);

			save_log("%-20s", pts->comm);
			save_log("%lld.%06ld", SPLIT_NS(sum_exec_runtime));
			if (nsec_high(sum_exec_runtime) > 1000)
				save_log(" ******");
			save_log("     %lld.%06ld     ", SPLIT_NS(vruntime));
			save_log("%-5d", pts->static_prio);
			save_log("%-5d", pts->normal_prio);
			save_log("%-15s", print_state(pts->state));
			save_log("%-6d", pti->preempt_count);

			if (pti->pWaitingMutex != &fake_mutex && pti->pWaitingMutex != NULL) {
				if (pti->pWaitingMutex->name) {
					save_log("    Mutex:%s,", pti->pWaitingMutex->name + 1);
					printk("    Mutex:%s,", pti->pWaitingMutex->name + 1);
				} else {
					printk("pti->pWaitingMutex->name == NULL\r\n");
				}

				if (pti->pWaitingMutex->mutex_owner_asusdebug) {
					save_log(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
					printk(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
				} else {
					printk("pti->pWaitingMutex->mutex_owner_asusdebug == NULL\r\n");
				}

				if (pti->pWaitingMutex->mutex_owner_asusdebug->comm) {
					save_log(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
					printk(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
				} else {
					printk("pti->pWaitingMutex->mutex_owner_asusdebug->comm == NULL\r\n");
				}
			}

			if (pti->pWaitingCompletion != &fake_completion && pti->pWaitingCompletion!=NULL) {
				if (pti->pWaitingCompletion->name)
					save_log("    Completion:wait_for_completion %s", pti->pWaitingCompletion->name );
				else
					printk("pti->pWaitingCompletion->name == NULL\r\n");
			}

			if (pti->pWaitingRTMutex != &fake_rtmutex && pti->pWaitingRTMutex != NULL) {
				struct task_struct *temp = rt_mutex_owner(pti->pWaitingRTMutex);
				if (temp)
					save_log("    RTMutex: Owned by pID(%d)", temp->pid);
				else
					printk("pti->pWaitingRTMutex->temp == NULL\r\n");
				if (temp->comm)
					save_log(" %s", temp->pid, temp->comm);
				else
					printk("pti->pWaitingRTMutex->temp->comm == NULL\r\n");
			}

			save_log("\r\n");
			show_stack1(pts, NULL);
			save_log("\r\n");
		} else 
			return 0;
	}
	return 1;
}

struct worker {
	/* on idle list while idle, on busy hash table while busy */
	union {
		struct list_head	entry;	/* L: while idle */
		struct hlist_node	hentry;	/* L: while busy */
	};

	struct work_struct	*current_work;	/* L: work being processed */
	int *current_cwq; /* L: current_work's cwq */
	struct list_head	scheduled;	/* L: scheduled works */
	struct task_struct	*task;		/* I: worker task */
};

void save_all_thread_info(void)
{
	struct task_struct *pts;
	struct thread_info *pti;
	struct thread_info_save *ptis = NULL, *ptis_ptr = NULL;

	struct rtc_time tm;
	asus_rtc_read_time(&tm);

	g_phonehang_log = (char*)PHONE_HANG_LOG_BUFFER;//phys_to_virt(PHONE_HANG_LOG_BUFFER);
	g_iPtr = 0;
	memset(g_phonehang_log, 0, PHONE_HANG_LOG_SIZE);

	save_log("ASUSSlowg-%04d%02d%02d-%02d%02d%02d.txt  ---  ASUS_SW_VER : %s----------------------------------------------\r\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ASUS_SW_VER);
	save_log(" pID----ppID----NAME----------------SumTime---vruntime--SPri-NPri-State----------PmpCnt-binder----Waiting\r\n");

	if (ptis_head != NULL) {
		struct thread_info_save *ptis_next = ptis_head->pnext;
		struct thread_info_save *ptis_next_next;
		while(ptis_next) {
			ptis_next_next = ptis_next->pnext;
			kfree(ptis_next);
			ptis_next = ptis_next_next;
		}
		kfree(ptis_head);
		ptis_head = NULL;
	}

	if (ptis_head == NULL) {
		ptis_ptr = ptis_head = kmalloc(sizeof( struct thread_info_save), GFP_KERNEL);
		if (!ptis_head) {
			printk("kmalloc ptis_head failure\n");
			return;
		}
		memset(ptis_head, 0, sizeof( struct thread_info_save));
	}

	for_each_process(pts) {
		pti = (struct thread_info *)((int)(pts->stack)  & ~(THREAD_SIZE - 1));
		//printk("for pts %x, ptis_ptr=%x\n\r", pts, ptis_ptr);
		ptis = kmalloc(sizeof( struct thread_info_save), GFP_KERNEL);
		if (!ptis) {
			printk("kmalloc ptis failure\n");
			return;
		}
		memset(ptis, 0, sizeof( struct thread_info_save));

		save_log("-----------------------------------------------------\r\n");
		save_log(" %-7d", pts->pid);
		if (pts->parent)
			save_log("%-8d", pts->parent->pid);
		else
			save_log("%-8d", 0);

		save_log("%-20s", pts->comm);
		save_log("%lld.%06ld", SPLIT_NS(pts->se.sum_exec_runtime));
		save_log("	 %lld.%06ld	 ", SPLIT_NS(pts->se.vruntime));
		save_log("%-5d", pts->static_prio);
		save_log("%-5d", pts->normal_prio);
		save_log("%-15s", print_state((pts->state & TASK_REPORT) | pts->exit_state));
		save_log("%-6d", pti->preempt_count);

		if (pti->pWaitingMutex != &fake_mutex && pti->pWaitingMutex != NULL) {
			if (pti->pWaitingMutex->name) {
				save_log("	Mutex:%s,", pti->pWaitingMutex->name + 1);
				printk("	Mutex:%s,", pti->pWaitingMutex->name + 1);
			} else {
				printk("pti->pWaitingMutex->name == NULL\r\n");
			}

			if (pti->pWaitingMutex->mutex_owner_asusdebug) {
				save_log(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
				printk(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
			} else {
				printk("pti->pWaitingMutex->mutex_owner_asusdebug == NULL\r\n");
			}

			if (pti->pWaitingMutex->mutex_owner_asusdebug->comm) {
				save_log(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
				printk(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
			} else {
				printk("pti->pWaitingMutex->mutex_owner_asusdebug->comm == NULL\r\n");
			}
		}

		if (pti->pWaitingCompletion != &fake_completion && pti->pWaitingCompletion!=NULL) {
			if (pti->pWaitingCompletion->name)
				save_log("	Completion:wait_for_completion %s", pti->pWaitingCompletion->name );
			else
				printk("pti->pWaitingCompletion->name == NULL\r\n");
		}

		if (pti->pWaitingRTMutex != &fake_rtmutex && pti->pWaitingRTMutex != NULL) {
			struct task_struct *temp = rt_mutex_owner(pti->pWaitingRTMutex);
			if (temp)
				save_log("	RTMutex: Owned by pID(%d)", temp->pid);
			else
				printk("pti->pWaitingRTMutex->temp == NULL\r\n");
			if (temp->comm)
				save_log(" %s", temp->pid, temp->comm);
			else
				printk("pti->pWaitingRTMutex->temp->comm == NULL\r\n");
		}

		save_log("\r\n");
		show_stack1(pts, NULL);
		save_log("\r\n");

		ptis->pid = pts->pid;
		ptis->pts = pts;
		ptis->sum_exec_runtime = pts->se.sum_exec_runtime;
		ptis->vruntime = pts->se.vruntime;

		ptis_ptr->pnext = ptis;
		ptis_ptr = ptis;

		if (!thread_group_empty(pts)) {
			struct task_struct *p1 = next_thread(pts);
			do {
				pti = (struct thread_info *)((int)(p1->stack)  & ~(THREAD_SIZE - 1));
				ptis = kmalloc(sizeof( struct thread_info_save), GFP_KERNEL);
				if (!ptis) {
					printk("kmalloc ptis 2 failure\n");
					return;
				}
				memset(ptis, 0, sizeof( struct thread_info_save));

				ptis->pid = p1->pid;
				ptis->pts = p1;
				ptis->sum_exec_runtime = p1->se.sum_exec_runtime;
				ptis->vruntime = p1->se.vruntime;

				ptis_ptr->pnext = ptis;
				ptis_ptr = ptis;
				save_log(" %-7d", p1->pid);

				if (pts->parent)
					save_log("%-8d", p1->parent->pid);
				else
					save_log("%-8d", 0);

				save_log("%-20s", p1->comm);
				save_log("%lld.%06ld", SPLIT_NS(p1->se.sum_exec_runtime));
				save_log("	 %lld.%06ld	 ", SPLIT_NS(p1->se.vruntime));
				save_log("%-5d", p1->static_prio);
				save_log("%-5d", p1->normal_prio);
				save_log("%-15s", print_state((p1->state & TASK_REPORT) | p1->exit_state));
				save_log("%-6d", pti->preempt_count);

				if (pti->pWaitingMutex != &fake_mutex && pti->pWaitingMutex != NULL) {
					if (pti->pWaitingMutex->name) {
						save_log("	Mutex:%s,", pti->pWaitingMutex->name + 1);
						printk("	Mutex:%s,", pti->pWaitingMutex->name + 1);
					} else {
						printk("pti->pWaitingMutex->name == NULL\r\n");
					}

					if (pti->pWaitingMutex->mutex_owner_asusdebug) {
						save_log(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
						printk(" Owned by pID(%d)", pti->pWaitingMutex->mutex_owner_asusdebug->pid);
					} else {
						printk("pti->pWaitingMutex->mutex_owner_asusdebug == NULL\r\n");
					}

					if (pti->pWaitingMutex->mutex_owner_asusdebug->comm) {
						save_log(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
						printk(" %s",pti->pWaitingMutex->mutex_owner_asusdebug->comm);
					} else {
						printk("pti->pWaitingMutex->mutex_owner_asusdebug->comm == NULL\r\n");
					}
				}

				if (pti->pWaitingCompletion != &fake_completion && pti->pWaitingCompletion!=NULL) {
					if (pti->pWaitingCompletion->name)
						save_log("	Completion:wait_for_completion %s", pti->pWaitingCompletion->name );
					else
						printk("pti->pWaitingCompletion->name == NULL\r\n");
				}

				if (pti->pWaitingRTMutex != &fake_rtmutex && pti->pWaitingRTMutex != NULL) {
					struct task_struct *temp = rt_mutex_owner(pti->pWaitingRTMutex);
					if (temp)
						save_log("	RTMutex: Owned by pID(%d)", temp->pid);
					else
						printk("pti->pWaitingRTMutex->temp == NULL\r\n");
					if (temp->comm)
						save_log(" %s", temp->pid, temp->comm);
					else
						printk("pti->pWaitingRTMutex->temp->comm == NULL\r\n");
				}
				save_log("\r\n");
				show_stack1(p1, NULL);
				save_log("\r\n");

				p1 = next_thread(p1);
			} while(p1 != pts);
		}
	}
}
EXPORT_SYMBOL(save_all_thread_info);

void delta_all_thread_info(void)
{
	struct task_struct *pts;
	int ret = 0, ret2 = 0;

	save_log("\r\nDELTA INFO----------------------------------------------------------------------------------------------\r\n");
	save_log(" pID----ppID----NAME----------------SumTime---vruntime--SPri-NPri-State----------PmpCnt----Waiting\r\n");
	for_each_process(pts) {
		//printk("for pts %x,\n\r", pts);
		ret = find_thread_info(pts, 0);
		if (!thread_group_empty(pts)) {
			struct task_struct *p1 = next_thread(pts);
			ret2 = 0;
			do {
				ret2 += find_thread_info(p1, 0);
				p1 = next_thread(p1);
			} while(p1 != pts);
			if (ret2 && !ret)
				find_thread_info(pts, 1);
		}
		if (ret || ret2)
			save_log("-----------------------------------------------------\r\n\r\n-----------------------------------------------------\r\n");
	}
	save_log("\r\n\r\n\r\n\r\n");
}
EXPORT_SYMBOL(delta_all_thread_info);
///////////////////////////////////////////////////////////////////////////////////////////////////

static int asusdebug_open(struct inode * inode, struct file * file)
{
	g_read_pos = 0;
	return 0;
}

static int asusdebug_release(struct inode * inode, struct file * file)
{
	return 0;
}

static ssize_t asusdebug_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
	return 0;
}
static mm_segment_t oldfs;
static void initKernelEnv(void)
{
	oldfs = get_fs();
	set_fs(KERNEL_DS);
}

static void deinitKernelEnv(void)
{
	set_fs(oldfs);
}
char messages[256];

void save_phone_hang_log(void)
{
	int file_handle;
	int ret;
	//---------------saving phone hang log if any -------------------------------
	g_phonehang_log = (char*)PHONE_HANG_LOG_BUFFER;// phys_to_virt(PHONE_HANG_LOG_BUFFER);
	printk("save_phone_hang_log PRINTK_BUFFER=%x, PRINTK_BUFFER=PHONE_HANG_LOG_BUFFE=%x \n", PRINTK_BUFFER, PHONE_HANG_LOG_BUFFER);

	if (g_phonehang_log && ((strncmp(g_phonehang_log, "PhoneHang", 9) == 0) || (strncmp(g_phonehang_log, "ASUSSlowg", 9) == 0))) {
		printk("save_phone_hang_log-1\n");
		initKernelEnv();
		memset(messages, 0, sizeof(messages));
		strcpy(messages, ASDF_ROOT_DIR);
		strncat(messages, g_phonehang_log, 29);
		file_handle = sys_open(messages, O_CREAT|O_WRONLY|O_SYNC, 0);
		printk("save_phone_hang_log-2 file_handle %d, name=%s\n", file_handle, messages);
		if (!IS_ERR((const void *)file_handle)) {
			ret = sys_write(file_handle, (unsigned char*)g_phonehang_log, strlen(g_phonehang_log));
			sys_close(file_handle);
		}
		deinitKernelEnv();
	}

	if (g_phonehang_log) {
		g_phonehang_log[0] = 0;
	}
}
EXPORT_SYMBOL(save_phone_hang_log);

void save_last_shutdown_log(char* file_path)
{
	char *last_shutdown_log;
    int file_handle;
    unsigned long long t;
    unsigned long nanosec_rem;
    // ASUS_BSP +++
    char buffer[] = {"Kernel panic"};
    int i;
    // ASUS_BSP ---
    
    /* ASUS_BSP Paul +++ */
    char *last_logcat_buffer;
    ulong *printk_buffer_slot2_addr = (ulong *)PRINTK_BUFFER_SLOT2;
    int fd_kmsg, fd_logcat;
    ulong printk_buffer_index;
    /* ASUS_BSP Paul --- */

    t = cpu_clock(0);
	nanosec_rem = do_div(t, 1000000000);
    last_shutdown_log = (char*)PRINTK_BUFFER;
    /* ASUS_BSP Paul +++ */
    last_logcat_buffer = (char *)LOGCAT_BUFFER;
    printk_buffer_slot2_addr = (ulong *)PRINTK_BUFFER_SLOT2;
    /* ASUS_BSP Paul --- */

    if (file_path) {
		sprintf(messages, ASDF_ROOT_DIR"LastShutdown_%lu.%06lu.txt",
				(unsigned long) t,
				nanosec_rem / 1000);
	} else {
		sprintf(messages, ASDF_ROOT_DIR"last_kmsg.txt");
	}

	initKernelEnv();
	file_handle = sys_open(messages, O_CREAT|O_RDWR|O_SYNC, 0);

    if(!IS_ERR((const void *)(ulong)file_handle))
    {
        sys_write(file_handle, (unsigned char*)last_shutdown_log, PRINTK_BUFFER_SLOT_SIZE);
        sys_close(file_handle);
		// ASUS_BSP +++
        for(i=0; i<PRINTK_BUFFER_SLOT_SIZE; i++) {
            //
            // Check if it is kernel panic
            //
            if (strncmp((last_shutdown_log + i), buffer, strlen(buffer)) == 0) {
                ASUSEvtlog("[Reboot Kernel] Kernel panic\n");
                break;
            }
        }
        // ASUS_BSP ---
    } else {
		printk("[ASDF] save_last_shutdown_error: [%d]\n", file_handle);
	}


	// ASUS_BSP +++
	// Check PMIC register 0xA148 Bit0
	if (download_mode_value & 0x01) {
		ASUSEvtlog("[Reboot] Download mode\n");
	}
	// ASUS_BSP --

    /* ASUS_BSP Paul +++ */
    printk_buffer_index = *(printk_buffer_slot2_addr + 1);
    if ((printk_buffer_index < PRINTK_BUFFER_SLOT_SIZE) && (LAST_KMSG_SIZE < SZ_128K)) {
        fd_kmsg = sys_open("/asdf/last_kmsg_16K", O_CREAT | O_RDWR | O_SYNC, S_IRUGO);
        if (!IS_ERR((const void *)(ulong)fd_kmsg)) {
            char *buf = kzalloc(LAST_KMSG_SIZE, GFP_ATOMIC);
            if (!buf) {
                printk("[ASDF] failed to allocate buffer for last_kmsg\n");
            } else {
                if (printk_buffer_index > LAST_KMSG_SIZE) {
                    memcpy(buf, last_shutdown_log + printk_buffer_index - LAST_KMSG_SIZE, LAST_KMSG_SIZE);
                } else {
                    ulong part1 = LAST_KMSG_SIZE - printk_buffer_index;
                    ulong part2 = printk_buffer_index;
                    memcpy(buf, last_shutdown_log + PRINTK_BUFFER_SLOT_SIZE - part1, part1);
                    memcpy(buf + part1, last_shutdown_log, part2);
                }
                sys_write(fd_kmsg, buf, LAST_KMSG_SIZE);
                kfree(buf);
            }
                sys_close(fd_kmsg);
        } else {
            printk("[ASDF] failed to save last shutdown log to last_kmsg\n");
        }
    }
    fd_logcat = sys_open("/asdf/last_logcat_16K", O_CREAT | O_RDWR | O_SYNC, S_IRUGO);
	
    if (!IS_ERR((const void *)(ulong)fd_logcat)) {
           sys_write(fd_logcat, (unsigned char *)last_logcat_buffer, LOGCAT_BUFFER_SIZE);
           sys_close(fd_logcat);
    } else {
           printk("[ASDF] failed to save last logcat to last_logcat\n");
    }
    /* ASUS_BSP Paul --- */

    deinitKernelEnv();
}

#if defined(CONFIG_MSM_RTB)
extern struct msm_rtb_state msm_rtb;
int g_saving_rtb_log = 1;
	
void save_rtb_log(void)
{
	char *rtb_log;
	char rtb_log_path[256] = {0};
	//~ struct rtc_time tm;
	int file_handle;
	unsigned long long t;
	unsigned long nanosec_rem;

	//~ asus_rtc_read_time(&tm);
	rtb_log = (char*)msm_rtb.rtb;
	t = cpu_clock(0);
	nanosec_rem = do_div(t, 1000000000);
	snprintf(rtb_log_path, sizeof(rtb_log_path)-1, ASDF_ROOT_DIR"rtb_%lu.%06lu.bin",
		(unsigned long) t,
		nanosec_rem / 1000);

	initKernelEnv();
	file_handle = sys_open(rtb_log_path, O_CREAT|O_RDWR|O_SYNC, 0);
	if (!IS_ERR((const void *)file_handle)) {
		sys_write(file_handle, (unsigned char*)rtb_log, msm_rtb.size);
		sys_close(file_handle);
	}

	deinitKernelEnv();
}
#endif

typedef struct tzbsp_dump_cpu_ctx_s
{
	unsigned int mon_lr;
	unsigned int mon_spsr;
	unsigned int usr_r0;
	unsigned int usr_r1;
	unsigned int usr_r2;
	unsigned int usr_r3;
	unsigned int usr_r4;
	unsigned int usr_r5;
	unsigned int usr_r6;
	unsigned int usr_r7;
	unsigned int usr_r8;
	unsigned int usr_r9;
	unsigned int usr_r10;
	unsigned int usr_r11;
	unsigned int usr_r12;
	unsigned int usr_r13;
	unsigned int usr_r14;
	unsigned int irq_spsr;
	unsigned int irq_r13;
	unsigned int irq_r14;
	unsigned int svc_spsr;
	unsigned int svc_r13;
	unsigned int svc_r14;
	unsigned int abt_spsr;
	unsigned int abt_r13;
	unsigned int abt_r14;
	unsigned int und_spsr;
	unsigned int und_r13;
	unsigned int und_r14;
	unsigned int fiq_spsr;
	unsigned int fiq_r8;
	unsigned int fiq_r9;
	unsigned int fiq_r10;
	unsigned int fiq_r11;
	unsigned int fiq_r12;
	unsigned int fiq_r13;
	unsigned int fiq_r14;
} tzbsp_dump_cpu_ctx_t;

typedef struct tzbsp_dump_buf_s
{
	unsigned int sc_status[2];
	tzbsp_dump_cpu_ctx_t sc_ns[2];
	tzbsp_dump_cpu_ctx_t sec;
} tzbsp_dump_buf_t;

void save_last_watchdog_reg(void)
{
	tzbsp_dump_buf_t *last_watchdog_reg;
	struct rtc_time tm;
	int file_handle;

	asus_rtc_read_time(&tm);
	last_watchdog_reg = (tzbsp_dump_buf_t*)PHONE_HANG_LOG_BUFFER - PRINTK_BUFFER_SLOT_SIZE / 2;//phys_to_virt((PHONE_HANG_LOG_BUFFER - PRINTK_BUFFER_SLOT_SIZE / 2));
	if (*((int*)last_watchdog_reg) != PRINTK_BUFFER_MAGIC) {
		sprintf(messages, ASDF_ROOT_DIR"%s_%04d%02d%02d-%02d%02d%02d.txt", "WatchdogReg", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

		initKernelEnv();
		file_handle = sys_open(messages, O_CREAT|O_RDWR|O_SYNC, 0);
		if (!IS_ERR((const void *)file_handle)) {
			sys_write(file_handle, (unsigned char*)last_watchdog_reg, sizeof(tzbsp_dump_buf_t));
			sys_close(file_handle);
		}
		deinitKernelEnv();
	}
	memset(last_watchdog_reg, 0, sizeof(tzbsp_dump_buf_t));
	*((int*)last_watchdog_reg) = PRINTK_BUFFER_MAGIC;
}

void get_last_shutdown_log(void)
{
    char *last_shutdown_log;
    unsigned int *last_shutdown_log_addr;

    last_shutdown_log = (char*)PRINTK_BUFFER;//(phys_to_virt(PRINTK_BUFFER);
    last_shutdown_log_addr = (unsigned int *)((unsigned int)last_shutdown_log + (unsigned int)PRINTK_BUFFER_SLOT_SIZE);
    printk("get_last_shutdown_log: last_shutdown_log_addr=0x%08x, value=0x%08x\n", (unsigned int)last_shutdown_log_addr, *last_shutdown_log_addr);
    if(*last_shutdown_log_addr == (unsigned int)PRINTK_BUFFER_MAGIC)
    {
        save_last_shutdown_log("LastShutdown");
    }
    save_last_shutdown_log(NULL);
    printk_buffer_rebase();
    *last_shutdown_log_addr = PRINTK_BUFFER_MAGIC;
}
EXPORT_SYMBOL(get_last_shutdown_log);


static ssize_t asusdebug_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
#ifdef ASUS_USER_BUILD /* for user build */
	if (count > 256)
		count = 256;
	if (copy_from_user(messages, buf, count))
		return -EFAULT;
	if (strncmp(messages, "load", 4) == 0) {
		first = 1;
		return count;
	} else if (strncmp(messages, "panic", 5) == 0) {
		panic("panic test");
	} else if (strncmp(messages, "slowlog", 7) == 0) {
		printk("start to gi chk\n");
		save_all_thread_info();

		msleep(5 * 1000);

		printk("start to gi delta\n");
		delta_all_thread_info();
		save_phone_hang_log();
		return count;
	} else if (strncmp(messages, "adbreboot", 9) == 0) {
		printk("rebooting, reason: adb reboot\n");
	} else if (strncmp(messages, "get_lastshutdown_log", 20) == 0) {
		get_last_shutdown_log();
	}
	return count;
#else
	if (count > 256)
		count = 256;
	if (copy_from_user(messages, buf, count))
		return -EFAULT;

	if (strncmp(messages, "load", 4) == 0) {
		first = 1;
		return count;
	} else if (strncmp(messages, "slowlog", 7) == 0) {
		printk("start to gi chk\n");
		save_all_thread_info();

		msleep(5 * 1000);

		printk("start to gi delta\n");
		delta_all_thread_info();
		save_phone_hang_log();
		return count;
	} else if (strncmp(messages, "gichk", 5) == 0) {
		save_all_thread_info();
		return count;
	} else if (strncmp(messages, "gidelta", 7) == 0) {
		delta_all_thread_info();
		save_phone_hang_log();
		return count;
	} else if (strncmp(messages, "gi", 2) == 0) {
		print_all_thread_info();
		return count;
	} else if (strncmp(messages, "get_lastshutdown_log", 20) == 0) {
		get_last_shutdown_log();
	} else if (strncmp(messages, "get_phonehang_log", 17) == 0) {
		save_phone_hang_log();		
	} else if (strncmp(messages, "gichk", 5) == 0) {
		save_all_thread_info();
		return count;
	} else if (strncmp(messages, "gidelta", 7) == 0) {
		delta_all_thread_info();
		save_phone_hang_log(); 
		return count;
	} else if (strncmp(messages, "gi", 2) == 0) {
		print_all_thread_info();
		return count;
	} else if (strncmp(messages, "printk", 6) == 0) {
		die("test123", NULL, 0);
	} else if (strncmp(messages, "panic", 5) == 0) {
		panic("panic test");
	} else if (strncmp(messages, "die", 3) == 0) {
		die("die test", NULL, 0);
	} else if (strncmp(messages, "modem", 5) == 0) {
		#include <mach/subsystem_restart.h>
		subsystem_restart("external_modem");
	} else if (strncmp(messages, "adbreboot", 9) == 0) {
		printk("rebooting, reason: adb reboot\n");
	}
	return count;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////
////				  Asusdebug module initial function
/////////////////////////////////////////////////////////////////////////////////////////////
static const struct file_operations proc_asusdebug_operations = {
	.read     = asusdebug_read,
	.write    = asusdebug_write,
	.open     = asusdebug_open,
	.release  = asusdebug_release,
};

#ifdef CONFIG_HAS_EARLYSUSPEND
static void asusdebug_early_suspend(struct early_suspend *h)
{
	entering_suspend = 1;
}

static void asusdebug_early_resume(struct early_suspend *h)
{
	entering_suspend = 0;
}
#endif
EXPORT_SYMBOL(entering_suspend);

#ifdef CONFIG_HAS_EARLYSUSPEND
struct early_suspend asusdebug_early_suspend_handler = {
	.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN,
	.suspend = asusdebug_early_suspend,
	.resume = asusdebug_early_resume,
};
#endif

static ssize_t turnon_asusdebug_proc_read(struct file *filp, char __user *buff, size_t len, loff_t *off)
{
	char print_buf[32];
	unsigned int ret = 0,iret = 0;
	sprintf(print_buf, "asusdebug: %s\n", asusdebug_enable? "off":"on");
	ret = strlen(print_buf);
	iret = copy_to_user(buff, print_buf, ret);
	if (!readflag) {
		readflag = 1;
		return ret;
	} else {
		readflag = 0;
		return 0;
	}
}

static ssize_t turnon_asusdebug_proc_write(struct file *filp, const char __user *buff, size_t len, loff_t *off)
{
	char messages[256];
	memset(messages, 0, sizeof(messages));
	if (len > 256)
		len = 256;
	if (copy_from_user(messages, buff, len))
		return -EFAULT;
	if (strncmp(messages, "off", 3) == 0) {
		asusdebug_enable = 0x11223344;
	} else if (strncmp(messages, "on", 2) == 0) {
		asusdebug_enable = 0;
	}
	return len;
}

static struct file_operations turnon_asusdebug_proc_ops = {
	.read = turnon_asusdebug_proc_read,
	.write = turnon_asusdebug_proc_write,
};

/*ASUS-BBSP SubSys Health Record+++*/
static void do_write_subsys_worker(struct work_struct *work)
{
    int hfile = -MAX_ERRNO;
    hfile = sys_open(SUBSYS_HEALTH_MEDICAL_TABLE_PATH".txt", O_CREAT|O_WRONLY|O_SYNC, 0444);
    if(!IS_ERR((const void *)(ulong)hfile)) {
	if (sys_lseek(hfile, 0, SEEK_END) >= SZ_128K) {
	    ASUSEvtlog("[SSR-Info] SubSys is versy ill\n");
	    sys_close(hfile);
	    sys_unlink(SUBSYS_HEALTH_MEDICAL_TABLE_PATH"_old.txt");
	    sys_rename(SUBSYS_HEALTH_MEDICAL_TABLE_PATH".txt", SUBSYS_HEALTH_MEDICAL_TABLE_PATH"_old.txt");
	    hfile = sys_open(SUBSYS_HEALTH_MEDICAL_TABLE_PATH".txt", O_CREAT|O_RDWR|O_SYNC, 0444);
	}
	sys_write(hfile, g_SubSys_W_Buf, strlen(g_SubSys_W_Buf));
	sys_fsync(hfile);
	sys_close(hfile);
    } else {
	ASUSEvtlog("[SSR-Info] Save SubSys Medical Table Error: [0x%x]\n", hfile);
    }
}
static void do_count_subsys_worker(struct work_struct *work)
{
    int  hfile = -MAX_ERRNO;
    char r_buf[SUBSYS_R_MAXLEN];
    int  r_size = 0;
    int  index = 0;
    char keys[] = "[SSR]:";
    char *pch;
    char n_buf[64];
    char SubSysName[SUBSYS_NUM_MAX][10];
    int  Counts[SUBSYS_NUM_MAX] = { 0 };
    int  subsys_num = 0;
    char OutSubSysName[3][10] = { "modem", "wcnss", "adsp" };/* Confirm SubSys Name for Each Platform */
    int  OutCounts[4] = { 0 };/* MODEM, WIFI, ADSP, OTHERS */

    /* Search All SubSys Supported */
    for(index = 0 ; index < SUBSYS_NUM_MAX ; index++) {
        sprintf(n_buf, SUBSYS_BUS_ROOT"/subsys%d/name", index);

        hfile = sys_open(n_buf, O_RDONLY|O_SYNC, 0444);
        if(!IS_ERR((const void *)(ulong)hfile)) {
            memset(r_buf, 0, sizeof(r_buf));
            r_size = sys_read(hfile, r_buf, sizeof(r_buf));
            if (r_size > 0) {
                sprintf(SubSysName[index], r_buf, r_size-2);/* Skip \n\0 */
                SubSysName[index][r_size-1] = '\0';/* Insert \0 at last */
                subsys_num++;
            }
            sys_close(hfile);
        }
    }

    hfile = sys_open(SUBSYS_HEALTH_MEDICAL_TABLE_PATH".txt", O_CREAT|O_RDONLY|O_SYNC, 0444);
    if(!IS_ERR((const void *)(ulong)hfile)) {
	do {
	    memset(r_buf, 0, sizeof(r_buf));
	    r_size = sys_read(hfile, r_buf, sizeof(r_buf));
	    if (r_size != 0) {
		/* count */
		pch = strstr(r_buf, keys);
		while (pch != NULL) {
		    pch = pch + strlen(keys);
		    for (index = 0 ; index < subsys_num ; index++) {
			if (!strncmp(pch, SubSysName[index], strlen(SubSysName[index]))) {
			    Counts[index]++;
			    break;
			}
		    }
		    pch = strstr(pch, keys);
		}
	    }
	} while (r_size != 0);

	sys_close(hfile);
    }

    /* Map The Out Pattern */
    for(index = 0 ; index < subsys_num ; index++) {
        if (!strncmp(OutSubSysName[0], SubSysName[index], strlen(SubSysName[index]))) {
            OutCounts[0] += Counts[index]; /* MODEM */
        } else if (!strncmp(OutSubSysName[1], SubSysName[index], strlen(SubSysName[index])))
            {
            OutCounts[1] += Counts[index]; /* WIFI */
        } else if (!strncmp(OutSubSysName[2], SubSysName[index], strlen(SubSysName[index])))
            {
            OutCounts[2] += Counts[index]; /* ADSP */
        } else {
            OutCounts[3] += Counts[index]; /* OTHERS */
        }
    }

    hfile = sys_open(SUBSYS_HEALTH_MEDICAL_TABLE_PATH"_old.txt", O_RDONLY|O_SYNC, 0444);
    if(!IS_ERR((const void *)(ulong)hfile)) {
	do {
	    memset(r_buf, 0, sizeof(r_buf));
	    r_size = sys_read(hfile, r_buf, sizeof(r_buf));
	    if (r_size != 0) {
		/* count */
		pch = strstr(r_buf, keys);
		while (pch != NULL) {
		    pch = pch + strlen(keys);
		    for (index = 0 ; index < subsys_num ; index++) {
			if (!strncmp(pch, SubSysName[index], strlen(SubSysName[index]))) {
			    Counts[index]++;
			    break;
			}
		    }
		    pch = strstr(pch, keys);
		}
	    }
	} while (r_size != 0);

	sys_close(hfile);
    }
	
    sprintf(g_SubSys_C_Buf, "%s-%d-%d-%d-%d", r_buf, OutCounts[0], OutCounts[1], OutCounts[2], OutCounts[3]);/* MODEM, WCNSS, ADSP, OTHERS(VENUS) */
    complete(&SubSys_C_Complete);
}
	
static void do_delete_subsys_worker(struct work_struct *work)
{
    sys_unlink(SUBSYS_HEALTH_MEDICAL_TABLE_PATH".txt");
    sys_unlink(SUBSYS_HEALTH_MEDICAL_TABLE_PATH"_old.txt");
    ASUSEvtlog("[SSR-Info] SubSys Medical Table Deleted\n");
}
	
void SubSysHealthRecord(const char *fmt, ...)
{
    va_list args;
    char *w_buf;
    struct rtc_time tm;
    struct timespec ts;
    memset(g_SubSys_W_Buf, 0 , sizeof(g_SubSys_W_Buf));
    w_buf = g_SubSys_W_Buf;

    getnstimeofday(&ts);
    ts.tv_sec -= sys_tz.tz_minuteswest * 60;
    rtc_time_to_tm(ts.tv_sec, &tm);
    sprintf(w_buf, "%04d-%02d-%02d %02d:%02d:%02d : ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    va_start(args, fmt);
    vscnprintf(w_buf + strlen(w_buf), sizeof(g_SubSys_W_Buf) - strlen(w_buf), fmt, args);
    va_end(args);
    /*printk("g_SubSys_W_Buf = %s", g_SubSys_W_Buf);*/
    queue_work(ASUSSubsys_workQueue, &subsys_w_Work);

    schedule_work(&send_ssr_reason_dropbox_uevent_work); /* ASUS_BSP Paul +++ */
}
EXPORT_SYMBOL(SubSysHealthRecord);
	
static int SubSysHealth_proc_show(struct seq_file *m, void *v)
{
    unsigned long ret;
    queue_work(ASUSSubsys_workQueue, &subsys_c_Work);/* Issue to count */

    ret = wait_for_completion_timeout(&SubSys_C_Complete, msecs_to_jiffies(1000));
    if (!ret)
        ASUSEvtlog("[SSR-Info] Timed out on query SubSys count\n");
	seq_printf(m, "%s\n", g_SubSys_C_Buf);
	return 0;
}

static int SubSysHealth_proc_open(struct inode *inode, struct  file *file)
{
    return single_open(file, SubSysHealth_proc_show, NULL);
}
	
static ssize_t SubSysHealth_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    char keyword[] = "clear";
    char tmpword[10];
    memset(tmpword, 0, sizeof(tmpword));

    /* no data be written Or Input size is too large to write our buffer */
    if ((!count) || (count > (sizeof(tmpword) - 1)))
	return -EINVAL;

    if (copy_from_user(tmpword, buf, count))
	return -EFAULT;
	
    if (strncmp(tmpword, keyword, strlen(keyword)) == 0) {
	queue_work(ASUSSubsys_workQueue, &subsys_d_Work);
    }
    return count;
}
	
static const struct file_operations proc_SubSysHealth_operations = {
    .open = SubSysHealth_proc_open,
    .read = seq_read,
    .write = SubSysHealth_proc_write,
};
/*ASUS-BBSP SubSys Health Record---*/
/* ASUS_BSP Paul +++ */
static ssize_t last_logcat_proc_write(struct file *filp, const char __user *buff, size_t len, loff_t *off)
{

    char messages[1000];
    char *last_logcat_buffer;

    memset(messages, 0, 1000);

    if (len > 1000)
        len = 1000;

    if (copy_from_user(messages, buff, len))
        return -EFAULT;

    last_logcat_buffer = (char *)LOGCAT_BUFFER;

    if (logcat_buffer_index + len >= LOGCAT_BUFFER_SIZE) {
        ulong part1 = LOGCAT_BUFFER_SIZE - logcat_buffer_index;
        ulong part2 = len - part1;
        memcpy_nc(last_logcat_buffer + logcat_buffer_index, messages, part1);
        memcpy_nc(last_logcat_buffer, messages + part1, part2);
        logcat_buffer_index = part2;
    } else {
        memcpy_nc(last_logcat_buffer + logcat_buffer_index, messages, len);
        logcat_buffer_index += len;
    }

    return len;
}

static struct file_operations last_logcat_proc_ops = {
    .write = last_logcat_proc_write,
};

static void send_ssr_reason_dropbox_uevent_work_handler(struct work_struct *work)
{
        if (ssr_reason_kobj) {
                char uevent_buf[512];
                char *envp[] = { uevent_buf, NULL };
                snprintf(uevent_buf, sizeof(uevent_buf), "SSR_REASON=%s", g_SubSys_W_Buf);
                kobject_uevent_env(ssr_reason_kobj, KOBJ_CHANGE, envp);
        }
}

static void dropbox_uevent_release(struct kobject *kobj)
{
        kfree(kobj);
}

static struct kobj_type dropbox_uevent_ktype = {
        .release = dropbox_uevent_release,
};

static int dropbox_uevent_init(void)
{
        int ret;

        dropbox_uevent_kset = kset_create_and_add("dropbox_uevent", NULL, kernel_kobj);
        if (!dropbox_uevent_kset) {
                printk("%s: failed to create dropbox_uevent_kset", __func__);
                return -ENOMEM;
        }

        ssr_reason_kobj = kzalloc(sizeof(*ssr_reason_kobj), GFP_KERNEL);
        if (!ssr_reason_kobj) {
                printk("%s: failed to create ssr_reason_kobj", __func__);
                return -ENOMEM;
        }

        ssr_reason_kobj->kset = dropbox_uevent_kset;

        ret = kobject_init_and_add(ssr_reason_kobj, &dropbox_uevent_ktype, NULL, "ssr_reason");
        if (ret) {
                printk("%s: failed to init ssr_reason_kobj", __func__);
                kobject_put(ssr_reason_kobj);
                return -EINVAL;
        }

        kobject_uevent(ssr_reason_kobj, KOBJ_ADD);

        INIT_WORK(&send_ssr_reason_dropbox_uevent_work, send_ssr_reason_dropbox_uevent_work_handler);

        return 0;
}
/* ASUS_BSP Paul --- */

// ASUS_BSP +++ Vivian_Tsai [ZB501KL][Debug][NA][NA] Add LogUnlock
static ssize_t logunlock_read(struct file *file, char __user *buf,
			      size_t count, loff_t *ppos)
{
	return 0;
}

static ssize_t logunlock_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	char messages[256];
	int file_handle;
	
	memset(messages, 0, sizeof(char)*256);

	if (count > 256)
		count = 256;
	if (copy_from_user(messages, buf, count))
		return -EFAULT;
			
	initKernelEnv();
	file_handle = sys_open(ASDF_ROOT_DIR "LogUnlock.txt", O_CREAT | O_RDWR | O_SYNC, 0660);
	if (!IS_ERR((const void *)(ulong)file_handle)) {
		sys_write(file_handle, messages, strlen(messages));
		sys_close(file_handle);
	}else {
		printk("[LogTool] logunlock write error: [%d]\n", file_handle);
	}
	deinitKernelEnv();
			
	return count;
}

static const struct file_operations proc_logunlock_operations = {
	.read	= logunlock_read,
	.write	= logunlock_write,
};
// ASUS_BSP --- Vivian_Tsai [ZB501KL][Debug][NA][NA] Add LogUnlock

static int __init proc_asusdebug_init(void)
{
	proc_create("asusdebug", S_IALLUGO, NULL, &proc_asusdebug_operations);
	proc_create("asusdebug-switch", S_IRWXUGO, NULL, &turnon_asusdebug_proc_ops);
	proc_create("last_logcat", S_IWUGO, NULL, &last_logcat_proc_ops); /* ASUS_BSP Paul +++ */
	proc_create("logunlock", S_IRWXUGO, NULL, &proc_logunlock_operations);// ASUS_BSP [ZB501KL] Add LogUnlock
	PRINTK_BUFFER = (unsigned int)ioremap(PRINTK_BUFFER, PRINTK_BUFFER_SIZE);

	/*ASUS-BBSP SubSys Health Record+++*/
	proc_create("SubSysHealth", S_IRWXUGO, NULL, &proc_SubSysHealth_operations);
	init_completion(&SubSys_C_Complete);
        ASUSSubsys_workQueue  = create_singlethread_workqueue("ASUSSUBSYS_WORKQUEUE");
	/*ASUS-BBSP SubSys Health Record---*/

	fake_mutex.owner = current;
	fake_mutex.name = " fake_mutex";
	strcpy(fake_completion.name," fake_completion");
	fake_rtmutex.owner = current;

#ifdef CONFIG_HAS_EARLYSUSPEND
	register_early_suspend(&asusdebug_early_suspend_handler);
#endif

	dropbox_uevent_init(); /* ASUS_BSP Paul +++ */

	printk("\n\n[ASUSEvtlog]---------------System Boot----%s---------\n", ASUS_SW_VER);
	return 0;
}
module_init(proc_asusdebug_init);

EXPORT_COMPAT("qcom,asusdebug");
