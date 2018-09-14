/////////////////////////////////////////////////////////////////////////////////////////////
////                  ASUS Debugging mechanism
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ASUSDEBUG_H__
#define __ASUSDEBUG_H__

#include <linux/asusevtlog.h>

extern unsigned int PRINTK_BUFFER;
extern unsigned int RTB_BUFFER;
extern unsigned int LAST_KMSG_BUFFER;

#define PRINTK_BUFFER_SIZE      (0x00300000)

#define PRINTK_PARSE_SIZE       (0x00080000)

#define PRINTK_BUFFER_MAGIC     (0xFEEDBEEF)
#define PRINTK_BUFFER_SLOT_SIZE (0x00040000)

#define PRINTK_BUFFER_SLOT1     (PRINTK_BUFFER)
#define PRINTK_BUFFER_SLOT2     ((int)PRINTK_BUFFER + (int)PRINTK_BUFFER_SLOT_SIZE)

#define PHONE_HANG_LOG_BUFFER   ((int)PRINTK_BUFFER + (int)PRINTK_BUFFER_SLOT_SIZE + (int)PRINTK_BUFFER_SLOT_SIZE)
#define PHONE_HANG_LOG_SIZE     (0x00080000)

/* ASUS_BSP Paul +++ */
#define LOGCAT_BUFFER           ((void *)((ulong)PRINTK_BUFFER + (ulong)SZ_2M))
#define LOGCAT_BUFFER_SIZE      (SZ_16K)
#define LAST_KMSG_SIZE      (SZ_16K)
/* ASUS_BSP Paul --- */

/*ASUS-BBSP SubSys Health Record+++*/
#define SUBSYS_HEALTH_MEDICAL_TABLE_PATH "/asdf/SubSysMedicalTable"
#define SUBSYS_BUS_ROOT "/sys/bus/msm_subsys/devices"
#define SUBSYS_NUM_MAX 10
#define SUBSYS_W_MAXLEN (170) /*%04d-%02d-%02d %02d:%02d:%02d : [SSR]:name reason*/
#define SUBSYS_R_MAXLEN (512)
#define SUBSYS_C_MAXLEN (30)
/*ASUS-BBSP SubSys Health Record---*/

void save_all_thread_info(void);
void delta_all_thread_info(void);
void save_phone_hang_log(void);
void save_last_shutdown_log(char* file_path);
void SubSysHealthRecord(const char *fmt, ...);/*ASUS-BBSP SubSys Health Record+*/

#endif
