#include <linux/asusdebug.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/rtc.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <linux/workqueue.h>

char msg[256];

// ASUS_BSP +++
extern char evtlog_bootup_reason[100];
extern char evtlog_poweroff_reason[100];
extern char evtlog_warm_reset_reason[100];
extern u16 warm_reset_value;
// ASUS_BSP ---
#define ASUS_EVENTLOG_TO_KMSG 0

#if !ASUS_EVENTLOG_TO_KMSG
static struct workqueue_struct *ASUSEvtlog_workQueue;
static void do_write_event_worker(struct work_struct *work);
static DECLARE_WORK(eventLog_Work, do_write_event_worker);

extern int nSuspendInProgress;
static int g_hfileEvtlog = -MAX_ERRNO;
static char g_Asus_Eventlog[ASUS_EVTLOG_MAX_ITEM][ASUS_EVTLOG_STR_MAXLEN];
static int g_Asus_Eventlog_read = 0;
static int g_Asus_Eventlog_write = 0;
int evtlog_enable = 0;
#define AID_SDCARD_RW 1015
static struct mutex mA;
#endif

static int g_bEventlogEnable = 1;

#if !ASUS_EVENTLOG_TO_KMSG
static void do_write_event_worker(struct work_struct *work)
{
    char buffer[256];
    
    memset(buffer, 0, sizeof(char) * 256);
    if(IS_ERR((const void*)g_hfileEvtlog))
    {
        long size;         
        {          
            g_hfileEvtlog = sys_open(ASUS_EVTLOG_PATH".txt", O_CREAT|O_RDWR|O_SYNC, 0);
            if(g_hfileEvtlog < 0){
				printk("AsusEvtlog: open evtlog failed\n");
				return;
			}
            sys_chown(ASUS_EVTLOG_PATH".txt", AID_SDCARD_RW, AID_SDCARD_RW);
            
            size = sys_lseek(g_hfileEvtlog, 0, SEEK_END);
            if(size >= SZ_2M)
            {        
                sys_close(g_hfileEvtlog); 
                sys_rmdir(ASUS_EVTLOG_PATH"_old.txt");
                sys_rename(ASUS_EVTLOG_PATH".txt", ASUS_EVTLOG_PATH"_old.txt");
                g_hfileEvtlog = sys_open(ASUS_EVTLOG_PATH".txt", O_CREAT|O_RDWR|O_SYNC, 0);
            }    
        	// ASUS_BSP +++
        	if (warm_reset_value) {
    			snprintf(buffer, sizeof(buffer),
                "\n\n---------------System Boot----%s---------\n"
                "###### Warm reset Reason: %s ###### \n"
                "###### Bootup Reason: %s ######\n",
                ASUS_SW_VER,
                evtlog_warm_reset_reason,
                evtlog_bootup_reason);

        	} else {
    			snprintf(buffer, sizeof(buffer),
                "\n\n---------------System Boot----%s---------\n"
                "###### Power off Reason: %s ###### \n"
                "###### Bootup Reason: %s ######\n",
                ASUS_SW_VER,
                evtlog_poweroff_reason,
                evtlog_bootup_reason);
        	}
        	// ASUS_BSP ---
            sys_write(g_hfileEvtlog, buffer, strlen(buffer));
            sys_close(g_hfileEvtlog);
        }
    }
    if(!IS_ERR((const void*)g_hfileEvtlog))
    {
        int str_len;
        char* pchar;
        long size;

        g_hfileEvtlog = sys_open(ASUS_EVTLOG_PATH".txt", O_CREAT|O_RDWR|O_SYNC, 0);
        sys_chown(ASUS_EVTLOG_PATH".txt", AID_SDCARD_RW, AID_SDCARD_RW);

        size = sys_lseek(g_hfileEvtlog, 0, SEEK_END);
        if(size >= SZ_2M)
        {		 
            sys_close(g_hfileEvtlog); 
            sys_rmdir(ASUS_EVTLOG_PATH"_old.txt");
            sys_rename(ASUS_EVTLOG_PATH".txt", ASUS_EVTLOG_PATH"_old.txt");
            g_hfileEvtlog = sys_open(ASUS_EVTLOG_PATH".txt", O_CREAT|O_RDWR|O_SYNC, 0);
        }

        while(g_Asus_Eventlog_read != g_Asus_Eventlog_write)
        {

            mutex_lock(&mA);

            str_len = strlen(g_Asus_Eventlog[g_Asus_Eventlog_read]);
            pchar = g_Asus_Eventlog[g_Asus_Eventlog_read];
            g_Asus_Eventlog_read ++;
            g_Asus_Eventlog_read %= ASUS_EVTLOG_MAX_ITEM;   
            mutex_unlock(&mA);

            if (pchar[str_len - 1] != '\n') {
                if (str_len + 1 >= ASUS_EVTLOG_STR_MAXLEN)
                    str_len = ASUS_EVTLOG_STR_MAXLEN - 2;
                pchar[str_len] = '\n';
                pchar[str_len + 1] = '\0';
            }

            sys_write(g_hfileEvtlog, pchar, strlen(pchar));
            sys_fsync(g_hfileEvtlog);

        }
        sys_close(g_hfileEvtlog);
    }
}
#endif

void ASUSEvtlog(const char *fmt, ...)
{
#if ASUS_EVENTLOG_TO_KMSG
    va_list args;

    struct rtc_time tm;
    struct timespec ts;
    getnstimeofday(&ts);
    ts.tv_sec -= sys_tz.tz_minuteswest * 60; // to get correct timezone information
    rtc_time_to_tm(ts.tv_sec, &tm);
    getrawmonotonic(&ts);
    printk("[ASUSEvtlog](%ld)%04d-%02d-%02d %02d:%02d:%02d :",ts.tv_sec,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    va_start(args, fmt);
    vprintk(fmt, args);
    va_end(args);
    
    return;
#else

    va_list args;
    char* buffer;
    
    if(g_bEventlogEnable == 0)
        return;
    //printk("-------------------------------g_Asus_Eventlog_write/asdf/ASUSEvtlog = %d\n", g_Asus_Eventlog_write);
    //mutex_lock(&mA);
    if (!in_interrupt() && !in_atomic() && !irqs_disabled())
        mutex_lock(&mA);//spin_lock(&spinlock_eventlog);
    
    buffer = g_Asus_Eventlog[g_Asus_Eventlog_write];
    //printk("g_Asus_Eventlog_write = %d\n", g_Asus_Eventlog_write);
    g_Asus_Eventlog_write ++;
    g_Asus_Eventlog_write %= ASUS_EVTLOG_MAX_ITEM;
        
    if (!in_interrupt() && !in_atomic() && !irqs_disabled())
        mutex_unlock(&mA);//spin_unlock(&spinlock_eventlog);
    //mutex_unlock(&mA);

    memset(buffer, 0, ASUS_EVTLOG_STR_MAXLEN);
    if(buffer)
    {
        struct rtc_time tm;
        struct timespec ts;
        
        getnstimeofday(&ts);
        ts.tv_sec -= sys_tz.tz_minuteswest * 60; // to get correct timezone information
        rtc_time_to_tm(ts.tv_sec, &tm);
        getrawmonotonic(&ts);
        sprintf(buffer, "(%ld)%04d-%02d-%02d %02d:%02d:%02d :",ts.tv_sec,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
        va_start(args, fmt);
        vscnprintf(buffer + strlen(buffer), ASUS_EVTLOG_STR_MAXLEN - strlen(buffer), fmt, args);
        va_end(args);
        printk(buffer);
        queue_work(ASUSEvtlog_workQueue, &eventLog_Work);
    }
    else
        printk("ASUSEvtlog buffer cannot be allocated");
	return;
#endif
}
EXPORT_SYMBOL(ASUSEvtlog);

static ssize_t evtlogswitch_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    if(strncmp(buf, "0", 1) == 0) {
        ASUSEvtlog("ASUSEvtlog disable !!");
        printk("[adbg] ASUSEvtlog disable !!");
        g_bEventlogEnable = 0;
    }

    if(strncmp(buf, "1", 1) == 0) {
        g_bEventlogEnable = 1;
        ASUSEvtlog("ASUSEvtlog enable !!");
        printk("[adbg] ASUSEvtlog enable !!");
    }

    return count;
}

static ssize_t asusevtlog_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    if (count > 256)
        count = 256;

    memset(msg, 0, sizeof(msg));
    if (copy_from_user(msg, buf, count))
        return -EFAULT;
    ASUSEvtlog(msg);

    return count;
}

static const struct file_operations proc_evtlogswitch_operations = {
    .write      = evtlogswitch_write,
};

static const struct file_operations proc_asusevtlog_operations = {
    .write      = asusevtlog_write,
};

static int __init proc_asusevtlog_init(void)
{

    proc_create("asusevtlog", S_IRWXUGO, NULL, &proc_asusevtlog_operations);
    proc_create("asusevtlog-switch", S_IRWXUGO, NULL, &proc_evtlogswitch_operations);
#if !ASUS_EVENTLOG_TO_KMSG
	mutex_init(&mA);
    ASUSEvtlog_workQueue  = create_singlethread_workqueue("ASUSEVTLOG_WORKQUEUE");
#endif
    ASUSEvtlog("ASUSEvtlog init\n");
    
    return 0;
}
module_init(proc_asusevtlog_init);
