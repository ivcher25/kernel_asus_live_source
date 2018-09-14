/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/module.h>
#include <linux/export.h>
#include "msm_led_flash.h"
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/gpio.h>

#define FLASH_NAME "qcom,led-flash1"

#define FLASH_PROC_FILE "driver/flash_proc"
static struct proc_dir_entry *flash_proc_file;

#define ASUS_FLASH_PROC_FILE "driver/asus_bmmi_flash_brightness"
static struct proc_dir_entry *asus_flash_proc_file;

#define PROC_ENTRY_ASUS_FLASH  "driver/asus_flash_brightness"
static struct proc_dir_entry *proc_asus;

#define CONFIG_MSMB_CAMERA_DEBUG
#undef CDBG
#if 1//def CONFIG_MSMB_CAMERA_DEBUG
#define CDBG(fmt, args...) pr_err(fmt, ##args)
#else
#define CDBG(fmt, args...) do { } while (0)
#endif

extern const char* module_name;

static struct msm_led_flash_ctrl_t fctrl;
static struct i2c_driver sky81296_i2c_driver;

#define FLASH1_CUR 0x00
#define FLASH2_CUR 0x01
#define FLASH_TIME 0x02
#define MOVIE_CUR  0x03
#define CONTROL      0x04

DEFINE_MSM_MUTEX(sky81296_mut);

static struct msm_camera_i2c_reg_array sky81296_init_array[] = {
	{0x04, 0x00},
//	{0x05, 0x07},
	{0x06, 0x65},
//	{0x00, 0x0A},
//	{0x01, 0x0A},
	{0x02, 0xFF},
//	{0x03, 0x11},
};

static struct msm_camera_i2c_reg_array sky81296_off_array[] = {
	{0x04, 0x00},
};

static struct msm_camera_i2c_reg_array sky81296_release_array[] = {
	{0x04, 0x00},
};
/*
static struct msm_camera_i2c_reg_array sky81296_low_array[] = {
  	{0x04, 0x11},
};

static struct msm_camera_i2c_reg_array sky81296_low_first_array[] = {
  	{0x04, 0x01},
};

static struct msm_camera_i2c_reg_array sky81296_low_second_array[] = {
  	{0x04, 0x10},
};
*/
static struct msm_camera_i2c_reg_array sky81296_high_array[] = {
  	{0x04, 0x22},
};
/*
static struct msm_camera_i2c_reg_array sky81296_high_first_array[] = {
  	{0x04, 0x02},
};

static struct msm_camera_i2c_reg_array sky81296_high_second_array[] = {
  	{0x04, 0x20},
};
*/

static int   Flashread_proc_read(struct seq_file *buf, void *v)
{	
	//int rc = 0;
	int ret = 0;
	uint16_t read_data = 255;
	uint16_t flash1current=0;
	uint16_t flash2current=0;
	uint16_t moviecurrent=0;
	uint16_t flashtime=0;

		ret = fctrl.flash_i2c_client->i2c_func_tbl->i2c_read(fctrl.flash_i2c_client, 0x03, &read_data, MSM_CAMERA_I2C_BYTE_DATA);
		moviecurrent = read_data;
		ret = fctrl.flash_i2c_client->i2c_func_tbl->i2c_read(fctrl.flash_i2c_client, 0x00, &read_data, MSM_CAMERA_I2C_BYTE_DATA);
	        flash1current = read_data;
		ret = fctrl.flash_i2c_client->i2c_func_tbl->i2c_read(fctrl.flash_i2c_client, 0x01, &read_data, MSM_CAMERA_I2C_BYTE_DATA);
		flash2current = read_data;
		ret = fctrl.flash_i2c_client->i2c_func_tbl->i2c_read(fctrl.flash_i2c_client, 0x02, &read_data, MSM_CAMERA_I2C_BYTE_DATA);
		flashtime = read_data;

			seq_printf(buf, "moviecurrent=0x%x /  flash1current=0x%x / flash2current=0x%x / time=0x%x  \n", moviecurrent,flash1current,flash2current,flashtime);

	return 0;
}

static int Flash_proc_open(struct inode *inode, struct  file *file)
{	
    return single_open(file, Flashread_proc_read, NULL);
}

static char debugTxtBuf[256];
int flashtime=0;
int flashcurrent=0;

static ssize_t Flash_proc_write(struct file *filp, const char __user *buff, size_t len, loff_t *data)
{
	int  strlen;
	int arg[2];

	arg[0] = 0;

	if(*data)
		return 0;
	
	strlen = (len > 256-1)? (256-1):(len);

	  if (copy_from_user(debugTxtBuf,buff,strlen))
		return -EFAULT;
	
	  sscanf(debugTxtBuf, "%x %x", &arg[0], &arg[1]);

	  printk("argument is arg1=0x%x arg2=0x%x\n",arg[0], arg[1]);

        flashtime = arg[0]; 
	flashcurrent = arg[1];
         return strlen;
	
#if 0
	int val;//, rc = 0;
	char messages[8];

	if (len > 8) {
		len = 8;
	}
	if (copy_from_user(messages, buff, len)) {
		pr_info("%s commond fail !!\n", __func__);
		return -EFAULT;
	}
	sscanf(messages, "%d",&val);	

	switch(val){
		case 0: //open
			printk(" ---- open f---- \n");
			gpio_set_value(110, 1);  //gpio_en
			msleep(20);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x06,0x65, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x00,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x01,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x02,0x66, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x03,0x11, MSM_CAMERA_I2C_BYTE_DATA);	
			break;
		case 1: //flash_1 enable
			printk(" ---- flash 1 f---- \n");
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x02, MSM_CAMERA_I2C_BYTE_DATA);
			break;
		case 2: //flash_2enable
			printk(" ---- flash 2 f---- \n");
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x20, MSM_CAMERA_I2C_BYTE_DATA);			
			break;
		case 3: //close
			printk(" ---- close  f---- \n");
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			gpio_set_value(110, 0);  //gpio_dis	
			break;
		}

	return len;
#endif	
}

static const struct file_operations Flash_proc_fops = {
		.owner = THIS_MODULE,
	       .open = Flash_proc_open,
		//.read = Cam_proc_read,
		.read = seq_read,
		.write = Flash_proc_write,
		//.llseek = seq_lseek,
	       //.release = single_release,
};
static void Flash_create_proc_file(void)
{
	flash_proc_file = proc_create(FLASH_PROC_FILE, 0776, NULL, &Flash_proc_fops);
	if(flash_proc_file)
		pr_info("  flash_proc_file create success");
	else
		pr_info("  flash_proc_file create failed!!!!!!");
}

//=====================================================================================================

static int ASUS_Flash_proc_open(struct inode *inode, struct  file *file)
{	
	//pr_info(" === %s ===",__func__);
	return 0;
}

static ssize_t ASUS_Flash_proc_write(struct file *filp, const char __user *buff, size_t len, loff_t *data)
{
	int val;//, rc = 0;
	char messages[8];

	if (len > 8) {
		len = 8;
	}
	if (copy_from_user(messages, buff, len)) {
		pr_info("%s commond fail !!\n", __func__);
		return -EFAULT;
	}
	sscanf(messages, "%d",&val);	
	
	switch(val){
		case 0: //open
			pr_info(" ---- close ---- \n");
			mutex_lock(&sky81296_mut);
			gpio_set_value(110, 1);  //gpio_en
			//msleep(2);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			gpio_set_value(110, 0);  //gpio_en
			//fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x06,0x65, MSM_CAMERA_I2C_BYTE_DATA);
		       //fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x00,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			//fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x01,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			//fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x02,0x06, MSM_CAMERA_I2C_BYTE_DATA);
			//fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x03,0x11, MSM_CAMERA_I2C_BYTE_DATA);
                     mutex_unlock(&sky81296_mut);
			pr_info(" ---- close ---- end\n");
			break;
		case 1: //flash_1 enable
			pr_info(" ---- flash 1---- \n");
			mutex_lock(&sky81296_mut);
			gpio_set_value(110, 1);  //gpio_en
			//msleep(2);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x06,0x65, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x00,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x01,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x02,0x06, MSM_CAMERA_I2C_BYTE_DATA);
		//current 0x00 : 25mA
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x03,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x01, MSM_CAMERA_I2C_BYTE_DATA);
//			msleep(700);
//			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
//			gpio_set_value(110, 0);  //gpio_dis
			mutex_unlock(&sky81296_mut);
			pr_info(" ---- flash 1 end ---- \n");
			break;
		case 2: //flash_2enable
			pr_info(" ---- flash 2 ---- \n");
			mutex_lock(&sky81296_mut);			
			gpio_set_value(110, 1);  //gpio_en
			//msleep(2);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x06,0x65, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x00,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x01,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x02,0xff, MSM_CAMERA_I2C_BYTE_DATA);
		//current 0x40 : 125mA
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x03,0x40, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x10, MSM_CAMERA_I2C_BYTE_DATA);
//			msleep(700);
//			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
//			gpio_set_value(110, 0);  //gpio_dis
			mutex_unlock(&sky81296_mut);
			pr_info(" ---- flash 2 ---- end\n");
			break;
		case 3: //close
			pr_info(" ---- close  ---- \n");
			mutex_lock(&sky81296_mut);
			gpio_set_value(110, 1);  //gpio_dis			
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			gpio_set_value(110, 0);  //gpio_dis
			mutex_unlock(&sky81296_mut);
			pr_info(" ---- close  ---- end \n");			
			break;
		}
	return len;
}

static const struct file_operations ASUS_Flash_proc_fops = {
		.owner = THIS_MODULE,
	       .open = ASUS_Flash_proc_open,
		//.read = Cam_proc_read,
		.read = seq_read,
		.write = ASUS_Flash_proc_write,
		//.llseek = seq_lseek,
	       //.release = single_release,
};

static void ASUS_Flash_create_proc_file(void)
{
	asus_flash_proc_file = proc_create(ASUS_FLASH_PROC_FILE, 0776, NULL, &ASUS_Flash_proc_fops);
	if(asus_flash_proc_file)
		pr_info(" asus_flash_proc_file create success");
	else
		pr_info("  asus_lash_proc_file create failed!!!!!!");

}

int32_t sky_msm_led_i2c_trigger_get_subdev_id(struct msm_led_flash_ctrl_t *fctrl,
	void *arg)
{
	uint32_t *subdev_id = (uint32_t *)arg;
	if (!subdev_id) {
		pr_err("failed\n");
		return -EINVAL;
	}
	*subdev_id = fctrl->subdev_id;

	CDBG("subdev_id %d\n", *subdev_id);
	return 0;
}
#if 0
int32_t sky_msm_led_i2c_trigger_config(struct msm_led_flash_ctrl_t *fctrl,
	void *data)
{
	int rc = 0;
	struct msm_camera_led_cfg_t *cfg = (struct msm_camera_led_cfg_t *)data;
	CDBG("called led_state %d\n", cfg->cfgtype);

	if (!fctrl->func_tbl) {
		pr_err("failed\n");
		return -EINVAL;
	}
	switch (cfg->cfgtype) {

	case MSM_CAMERA_LED_INIT:
		if (fctrl->func_tbl->flash_led_init)
			rc = fctrl->func_tbl->flash_led_init(fctrl);
		break;

	case MSM_CAMERA_LED_RELEASE:
		if (fctrl->func_tbl->flash_led_release)
			rc = fctrl->func_tbl->flash_led_release(fctrl);
		break;

	case MSM_CAMERA_LED_OFF:
		if (fctrl->func_tbl->flash_led_off)
			rc = fctrl->func_tbl->flash_led_off(fctrl);
		break;

	case MSM_CAMERA_LED_LOW:
		if (fctrl->func_tbl->flash_led_low)
			rc = fctrl->func_tbl->flash_led_low(fctrl);
		break;

	case MSM_CAMERA_LED_HIGH:
		if (fctrl->func_tbl->flash_led_high)
			rc = fctrl->func_tbl->flash_led_high(fctrl);
		break;
	default:
		rc = -EFAULT;
		break;
	}
	CDBG("flash_set_led_state: return %d\n", rc);
	return rc;
}
#endif

u8 g_asus_input_value1;
static int flash_read_asus (char *page, char **start, off_t off, int count,
	int *eof, void *data_unused)
{
	int len = 0;
	CDBG("[%s] BEGIN \n", __func__);

	len = scnprintf(page, 1024, "%d\n", g_asus_input_value1);
	if (len <= off+count) *eof = 1;
	*start = page + off;
	 len -= off;
	 if (len > count) len = count;
	 if (len < 0) len = 0;

	CDBG("[%s] END page=%s \n", __func__, page);
	return len;
}
static int flash_write_asus (struct file *file, const char __user *buffer,
       unsigned long count, void *data)
{
	char buf[] = "0x00000000";
	unsigned long len = min((unsigned long)sizeof(buf) - 1, count);
	//u32 torch_cr;

	CDBG("[%s] BEGIN Buff=%s \n", __func__, buffer);
	if (copy_from_user(buf, buffer, len)) return count;
	buf[len] = 0;
	if (sscanf(buf, "%hhu", &g_asus_input_value1) != 1) {
		return -EINVAL;
	}

	if(g_asus_input_value1!=0)
		{
			gpio_set_value(110, 1);  //gpio_en
			msleep(20);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x06,0x65, MSM_CAMERA_I2C_BYTE_DATA);
			//fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x00,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
			//fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x01,buf, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x02,0xff, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x03,g_asus_input_value1<<4, MSM_CAMERA_I2C_BYTE_DATA);				
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x10, MSM_CAMERA_I2C_BYTE_DATA);	
			//msleep(600);
			//fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			//gpio_set_value(110, 0);  //gpio_dis
		}else 
		{
			fctrl.flash_i2c_client->i2c_func_tbl->i2c_write(fctrl.flash_i2c_client,0x04,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			 gpio_set_value(110, 0);  //gpio_dis
		}
			
	return strnlen(buf, count);;
}


int sky_msm_flash_led_init(struct msm_led_flash_ctrl_t *fctrl)
{
	//int rc = 0;
	struct msm_camera_sensor_board_info *flashdata = NULL;
	//struct msm_camera_power_ctrl_t *power_info = NULL;
	CDBG("%s:%d called\n", __func__, __LINE__);
	mutex_lock(&sky81296_mut);
	flashdata = fctrl->flashdata;

	gpio_set_value(110, 1);  //gpio_en
	gpio_set_value(21, 0);  // CAM_FLASH_FLINH
	msleep(2);
	fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,CONTROL,0x00, MSM_CAMERA_I2C_BYTE_DATA);
	fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,0x06,0x65, MSM_CAMERA_I2C_BYTE_DATA);
	fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,FLASH1_CUR,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
	fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,FLASH2_CUR,0x0a, MSM_CAMERA_I2C_BYTE_DATA);
	fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,FLASH_TIME,0x66, MSM_CAMERA_I2C_BYTE_DATA);
	fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,MOVIE_CUR,0x11, MSM_CAMERA_I2C_BYTE_DATA);	
	mutex_unlock(&sky81296_mut);
	return 0; 
}

int sky_msm_flash_led_release(struct msm_led_flash_ctrl_t *fctrl)
{
	//int rc = 0;
	struct msm_camera_sensor_board_info *flashdata = NULL;
	//struct msm_camera_power_ctrl_t *power_info = NULL;
	CDBG("%s:%d called\n", __func__, __LINE__);
	mutex_lock(&sky81296_mut);
	flashdata = fctrl->flashdata;
	gpio_set_value(110, 0);  //gpio_en	
	mutex_unlock(&sky81296_mut);	
	return 0;
}

int sky_msm_flash_led_off(struct msm_led_flash_ctrl_t *fctrl)
{
	//int rc = 0;
	struct msm_camera_sensor_board_info *flashdata = NULL;
	//struct msm_camera_power_ctrl_t *power_info = NULL;
	CDBG("%s:%d called\n", __func__, __LINE__);
	mutex_lock(&sky81296_mut);
	flashdata = fctrl->flashdata;
	gpio_set_value(110, 1);  //gpio_en
	fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,CONTROL,0x00, MSM_CAMERA_I2C_BYTE_DATA);
	mutex_unlock(&sky81296_mut);
	return 0;
}

int sky_msm_flash_led_low(struct msm_led_flash_ctrl_t *fctrl)
{
	//int rc = 0;
	struct msm_camera_sensor_board_info *flashdata = NULL;
	//struct msm_camera_power_ctrl_t *power_info = NULL;
	CDBG("%s:%d called module_name=%s \n", __func__, __LINE__,module_name);
	mutex_lock(&sky81296_mut);

	flashdata = fctrl->flashdata;

	if(!strcmp(module_name,"ov13850")) // back camera -> led1  200mA/
		{
		//current 0x40 : 125mA
		fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,MOVIE_CUR,0x04<<4, MSM_CAMERA_I2C_BYTE_DATA);
		fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,CONTROL,0x10, MSM_CAMERA_I2C_BYTE_DATA);
		}
	else
		{
		//current 0x00 : 25mA
	      fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,MOVIE_CUR,0x00, MSM_CAMERA_I2C_BYTE_DATA);
		fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,CONTROL,0x01, MSM_CAMERA_I2C_BYTE_DATA);
		}
	mutex_unlock(&sky81296_mut);	
	return 0;
}

int sky_msm_flash_led_high(struct msm_led_flash_ctrl_t *fctrl)
{
	//int rc = 0;
	struct msm_camera_sensor_board_info *flashdata = NULL;
	//struct msm_camera_power_ctrl_t *power_info = NULL;
	CDBG("%s:%d called\n", __func__, __LINE__);
	mutex_lock(&sky81296_mut);

	flashdata = fctrl->flashdata;
	
	if(!strcmp(module_name,"ov13850")) // back camera
		{
		//current : 0xf = 1A
		fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,FLASH1_CUR, 0xf, MSM_CAMERA_I2C_BYTE_DATA);
		//flash time : 0x88 = 760mA
		fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,FLASH_TIME,  0x88, MSM_CAMERA_I2C_BYTE_DATA);
		//0x20 = flash2 in flash mode
		fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,CONTROL,0x20, MSM_CAMERA_I2C_BYTE_DATA);
		}else
			{
			//current 0x00 : 25mA
	      		fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,MOVIE_CUR,0x00, MSM_CAMERA_I2C_BYTE_DATA);
			fctrl->flash_i2c_client->i2c_func_tbl->i2c_write(fctrl->flash_i2c_client,CONTROL,0x01, MSM_CAMERA_I2C_BYTE_DATA);
			}
	mutex_unlock(&sky81296_mut);		
		return 0;	
}

static void __exit msm_flash_sky81296_i2c_remove(void)
{
	i2c_del_driver(&sky81296_i2c_driver);
	return;
}

static const struct of_device_id sky81296_trigger_dt_match[] = {
	{.compatible = "qcom,led-flash1", .data = &fctrl},
	{}
};

MODULE_DEVICE_TABLE(of, sky81296_trigger_dt_match);

static const struct i2c_device_id flash_i2c_id[] = {
	{"qcom,led-flash1", (kernel_ulong_t)&fctrl},
	{ }
};

static const struct i2c_device_id sky81296_i2c_id[] = {
	{FLASH_NAME, (kernel_ulong_t)&fctrl},
	{ }
};

static int msm_flash_sky81296_i2c_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	pr_info("%s entry\n", __func__);
	if (!id) {
		pr_err("msm_flash_sky81296_i2c_probe: id is NULL");
		id = sky81296_i2c_id;
	}
	    Flash_create_proc_file(); //darren ++
           ASUS_Flash_create_proc_file();//darren ++

	if ((proc_asus = create_proc_entry(PROC_ENTRY_ASUS_FLASH, S_IRUGO | S_IWUGO, NULL))) {
		proc_asus->read_proc = flash_read_asus;
		proc_asus->write_proc = flash_write_asus;
	}

	return msm_flash_i2c_probe(client, id);
}

static struct i2c_driver sky81296_i2c_driver = {
	.id_table = sky81296_i2c_id,
	.probe  = msm_flash_sky81296_i2c_probe,
	.remove = __exit_p(msm_flash_sky81296_i2c_remove),
	.driver = {
		.name = FLASH_NAME,
		.owner = THIS_MODULE,
		.of_match_table = sky81296_trigger_dt_match,
	},
};

static int msm_flash_sky81296_platform_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;

	pr_info("%s entry\n", __func__);
	match = of_match_device(sky81296_trigger_dt_match, &pdev->dev);
	if (!match)
		return -EFAULT;

	return msm_flash_probe(pdev, match->data);
}

static struct platform_driver sky81296_platform_driver = {
	.probe = msm_flash_sky81296_platform_probe,
	.driver = {
		.name = "qcom,led-flash1",
		.owner = THIS_MODULE,
		.of_match_table = sky81296_trigger_dt_match,
	},
};

static int __init msm_flash_sky81296_init_module(void)
{
	int32_t rc = 0;
	pr_info("%s entry\n", __func__);

	#if 0
	rc = platform_driver_register(&sky81296_platform_driver);
	if (!rc)
		return rc;
	#endif
	pr_info("%s:%d rc %d\n", __func__, __LINE__, rc);

	return i2c_add_driver(&sky81296_i2c_driver);
}

static void __exit msm_flash_sky81296_exit_module(void)
{
printk("---%s---",__func__);
	if (fctrl.pdev)
		platform_driver_unregister(&sky81296_platform_driver);
	else
		i2c_del_driver(&sky81296_i2c_driver);
}

static struct msm_camera_i2c_client sky81296_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
};

static struct msm_camera_i2c_reg_setting sky81296_init_setting = {
	.reg_setting = sky81296_init_array,
	.size = ARRAY_SIZE(sky81296_init_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};

static struct msm_camera_i2c_reg_setting sky81296_off_setting = {
	.reg_setting = sky81296_off_array,
	.size = ARRAY_SIZE(sky81296_off_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};

static struct msm_camera_i2c_reg_setting sky81296_release_setting = {
	.reg_setting = sky81296_release_array,
	.size = ARRAY_SIZE(sky81296_release_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};

/*static struct msm_camera_i2c_reg_setting sky81296_low_setting = {
	.reg_setting = sky81296_low_array,
	.size = ARRAY_SIZE(sky81296_low_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};*/

/*static struct msm_camera_i2c_reg_setting sky81296_low_first_setting = {
	.reg_setting = sky81296_low_first_array,
	.size = ARRAY_SIZE(sky81296_low_first_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};*/

/*static struct msm_camera_i2c_reg_setting sky81296_low_second_setting = {
	.reg_setting = sky81296_low_second_array,
	.size = ARRAY_SIZE(sky81296_low_second_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};*/

static struct msm_camera_i2c_reg_setting sky81296_high_setting = {
	.reg_setting = sky81296_high_array,
	.size = ARRAY_SIZE(sky81296_high_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};

/*static struct msm_camera_i2c_reg_setting sky81296_high_first_setting = {
	.reg_setting = sky81296_high_first_array,
	.size = ARRAY_SIZE(sky81296_high_first_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};

static struct msm_camera_i2c_reg_setting sky81296_high_second_setting = {
	.reg_setting = sky81296_high_second_array,
	.size = ARRAY_SIZE(sky81296_high_second_array),
	.addr_type = MSM_CAMERA_I2C_BYTE_ADDR,
	.data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.delay = 0,
};*/

static struct msm_led_flash_reg_t sky81296_regs = {
	.init_setting = &sky81296_init_setting,
	.off_setting = &sky81296_off_setting,
	//.low_setting = &sky81296_low_setting,
	//.low_first_setting = &sky81296_low_first_setting,
	//.low_second_setting = &sky81296_low_second_setting,
	.high_setting = &sky81296_high_setting,
	//.high_first_setting = &sky81296_high_first_setting,
	//.high_second_setting = &sky81296_high_second_setting,
	.release_setting = &sky81296_release_setting,
};

static struct msm_flash_fn_t sky81296_func_tbl = {
	.flash_get_subdev_id = sky_msm_led_i2c_trigger_get_subdev_id,
	.flash_led_config = msm_led_i2c_trigger_config,
	.flash_led_init = sky_msm_flash_led_init,
	.flash_led_release = sky_msm_flash_led_release,
	.flash_led_off = sky_msm_flash_led_off,
	.flash_led_low = sky_msm_flash_led_low,
	.flash_led_high = sky_msm_flash_led_high,	
#if 0	
	.flash_get_subdev_id = msm_led_i2c_trigger_get_subdev_id,
	.flash_led_config = msm_led_i2c_trigger_config,
	.flash_led_init = msm_flash_led_init,
	.flash_led_release = msm_flash_led_release,
	.flash_led_off = msm_flash_led_off,
	.flash_led_low = msm_flash_led_low,
	//.flash_led_low_first = msm_flash_led_low_first,
	//.flash_led_low_second = msm_flash_led_low_second,
	.flash_led_high = msm_flash_led_high,
	//.flash_led_high_first = msm_flash_led_high_first,
	//.flash_led_high_second = msm_flash_led_high_second,
#endif
};

static struct msm_led_flash_ctrl_t fctrl = {
	.flash_i2c_client = &sky81296_i2c_client,
	.reg_setting = &sky81296_regs,
	.func_tbl = &sky81296_func_tbl,
};

/*subsys_initcall(msm_flash_i2c_add_driver);*/
module_init(msm_flash_sky81296_init_module);
module_exit(msm_flash_sky81296_exit_module);
MODULE_DESCRIPTION("sky81296 FLASH");
MODULE_LICENSE("GPL v2");
