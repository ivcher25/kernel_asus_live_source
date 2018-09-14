/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
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
#include "msm_sensor.h"
#include "msm_camera_io_util.h"
#include <linux/fs.h>
#include <linux/proc_fs.h>

#define OV5695_SENSOR_NAME "ov5695"
DEFINE_MSM_MUTEX(ov5695_mut);
//uint16_t g_position = 0;

#define	POSITION_ov5695_PROC_FILE	"driver/ov5695_test"

//static struct proc_dir_entry *position_proc_file;
static struct proc_dir_entry *vcm_value;
static struct msm_sensor_ctrl_t ov5695_s_ctrl;
#define SENSOR_MAX_RETRIES      50 /* max counter for retry I2C access */
#define DBG_TXT_BUF_SIZE 256
static u32 i2c_get_value;

static char debugTxtBuf[DBG_TXT_BUF_SIZE];

static int sensor_read_reg(struct i2c_client *client, u16 addr, u16 *val)
{
	int err;

      
	err=ov5695_s_ctrl.sensor_i2c_client->i2c_func_tbl->i2c_read(ov5695_s_ctrl.sensor_i2c_client,addr,val,MSM_CAMERA_I2C_BYTE_ADDR);
//	CDBG("sensor_read_reg 0x%x   addr=0x%x \n",*val,addr);
	if(err <0)
		return -EINVAL;	
	else return 0;
	
}

static int sensor_write_reg(struct i2c_client *client, u16 addr, u16 val)
{
	int err;
	int retry = 0;
	do {
		err =ov5695_s_ctrl.sensor_i2c_client->i2c_func_tbl->i2c_write(ov5695_s_ctrl.sensor_i2c_client,addr,val,MSM_CAMERA_I2C_BYTE_ADDR);		

		if (err == 0)
			return 0;
		retry++;
		pr_err("yuv_sensor : i2c transfer failed, retrying %x %x\n", addr, val);
		msleep(1); //LiJen: increate i2c retry delay to avoid ISP i2c fail issue
	} while (retry <= SENSOR_MAX_RETRIES);

	if(err == 0) {
		printk("%s(%d): i2c_transfer error, but return 0!?\n", __FUNCTION__, __LINE__);
		err = 0xAAAA;
	}


	return err;
}
static ssize_t i2c_get_write(struct file *file, const char __user *buf, size_t count,
				loff_t *ppos)
{
  int len=0;
  int arg = 0;


	if (*ppos)
		return 0;	/* the end */
	 len=(count > DBG_TXT_BUF_SIZE-1)?(DBG_TXT_BUF_SIZE-1):(count);
	 if (copy_from_user(debugTxtBuf,buf,len))
		return -EFAULT;

	 debugTxtBuf[len]=0; //add string end

	sscanf(debugTxtBuf, "%x", &arg);
	
		
//+ parsing......


	sensor_read_reg(ov5695_s_ctrl.sensor_i2c_client->client, arg, (u16 *)&i2c_get_value);
	printk("the value is 0x%x\n", i2c_get_value);

	return len;	/* the end */
}

static ssize_t i2c_set_write(struct file *file, const char __user *buf, size_t count,
				loff_t *ppos)
{
 	int len=0;
	int arg[2];
  //int gpio, set;

  //char gpioname[8];

//  printk("%s: buf=%p, count=%d, ppos=%p\n", __FUNCTION__, buf, count, ppos);
	arg[0]=0;

	if (*ppos)
		return 0;	/* the end */
	len=(count > DBG_TXT_BUF_SIZE-1)?(DBG_TXT_BUF_SIZE-1):(count);
	if (copy_from_user(debugTxtBuf,buf,len))
		return -EFAULT;

	debugTxtBuf[len]=0; //add string end

	sscanf(debugTxtBuf, "%x %x", &arg[0], &arg[1]);



	*ppos=len;
//+ parsing......

  

	sensor_write_reg(ov5695_s_ctrl.sensor_i2c_client->client, arg[0], arg[1]);
	return len;	/* the end */
}

static const struct file_operations i2c_set_fops = {
//	.open		= i2c_set_open,
	//.read		= i2c_config_read,
	//.llseek		= seq_lseek,
	//.release	= single_release,
	.write = i2c_set_write,
};

static const struct file_operations i2c_get_fops = {
//	.open		= i2c_get_open,
//	.read		= i2c_get_read,
	//.llseek		= seq_lseek,
	//.release	= single_release,
	.write = i2c_get_write,
};


static int vcm_value_write (struct file *file, const char __user *buffer,
       unsigned long count, void *parg)
{
	char buf[] = "000000000";
	unsigned long len = min((unsigned long)sizeof(buf) - 1, count);
	int input_value;
//	u16 addr, value;

	if (copy_from_user(buf, buffer, len)) return count;
	buf[len] = 0;
	if (sscanf(buf, "%d", &input_value) != 1) {
		return -EINVAL;
	}

	printk("set_dac: 0x%x", input_value);
    switch (input_value){
		case 0:
			printk(" power up\n");
		ov5695_s_ctrl.func_tbl->sensor_power_up(&ov5695_s_ctrl);
			break;
		case 1:
			ov5695_s_ctrl.func_tbl->sensor_power_down(&ov5695_s_ctrl);
			printk(" power down\n");
			break;
    }
	return strnlen(buf, count);;
} 




static struct msm_sensor_ctrl_t ov5695_s_ctrl;

static struct msm_sensor_power_setting ov5695_power_setting[] = {
//reset low
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_RESET,
		.config_val = GPIO_OUT_LOW,
		.delay = 0,
	},
//vana
	{	.seq_type = SENSOR_VREG,
		.seq_val = CAM_VANA,
		.config_val = 0,
		.delay = 2,
	},
//vio
	{	.seq_type = SENSOR_VREG,
		.seq_val = CAM_VIO,
		.config_val = 0,
		.delay = 2,
	},
//vdig
	{	.seq_type = SENSOR_VREG,
		.seq_val = CAM_VDIG,
		.config_val = 0,
		.delay = 2,
	},
//vi2c
	{	.seq_type = SENSOR_VREG,
		.seq_val = CAM_VI2C,
		.config_val = 0,
		.delay = 2,
	},
//reset hi
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_RESET,
		.config_val = GPIO_OUT_HIGH,
		.delay = 1,
	},
//mclk
	{
		.seq_type = SENSOR_CLK,
		.seq_val = SENSOR_CAM_MCLK,
		.config_val = 19200000,
		.delay = 1,
	},
//i2c mux
	{
		.seq_type = SENSOR_I2C_MUX,
		.seq_val = 0,
		.config_val = 0,
		.delay = 0,
	},	
#if 0	
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_RESET,
		.config_val = GPIO_OUT_LOW,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_VANA,
		.config_val = GPIO_OUT_LOW,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_VIO,
		.config_val = GPIO_OUT_LOW,
		.delay = 30,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_VANA,
		.config_val = GPIO_OUT_HIGH,
		.delay = 40,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_VIO,
		.config_val = GPIO_OUT_HIGH,
		.delay = 0,
	},
	{	.seq_type = SENSOR_VREG,
		.seq_val = CAM_VDIG,
		.config_val = 0,
		.delay = 0,
	},
		
	{	.seq_type = SENSOR_VREG,  ///only USE for i2c pull high 	
		.seq_val = CAM_VIO,
		.config_val = 0,
		.delay = 0,
	},
//[BSP][CAMERA][Kent][33449][01Begin]add the power control for AF
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_VAF,
		.config_val = GPIO_OUT_LOW,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_VAF,
		.config_val = GPIO_OUT_HIGH,
		.delay = 0,
	},
//[BSP][CAMERA][Kent][33449][01End]add the power control for AF
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_RESET,
		.config_val = GPIO_OUT_HIGH,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_CLK,
		.seq_val = SENSOR_CAM_MCLK,
		.config_val = 19200000,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_I2C_MUX,
		.seq_val = 0,
		.config_val = 0,
		.delay = 0,
	},
#endif	
};

static struct v4l2_subdev_info ov5695_subdev_info[] = {
	{
		.code   = V4L2_MBUS_FMT_SGRBG10_1X10,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.fmt    = 1,
		.order    = 0,
	},
};

static const struct i2c_device_id ov5695_i2c_id[] = {
	{OV5695_SENSOR_NAME, (kernel_ulong_t)&ov5695_s_ctrl},
	{ }
};

static int32_t msm_ov5695_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	return msm_sensor_i2c_probe(client, id, &ov5695_s_ctrl);
}

static struct i2c_driver ov5695_i2c_driver = {
	.id_table = ov5695_i2c_id,
	.probe  = msm_ov5695_i2c_probe,
	.driver = {
		.name = OV5695_SENSOR_NAME,
	},
};

static struct msm_camera_i2c_client ov5695_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};

static const struct of_device_id ov5695_dt_match[] = {
	{.compatible = "qcom,ov5695", .data = &ov5695_s_ctrl},
	{}
};

MODULE_DEVICE_TABLE(of, ov5695_dt_match);

static struct platform_driver ov5695_platform_driver = {
	.driver = {
		.name = "qcom,ov5695",
		.owner = THIS_MODULE,
		.of_match_table = ov5695_dt_match,
	},
};

static int32_t ov5695_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	const struct of_device_id *match;
	pr_info("%s:%d\n", __func__, __LINE__);	
	match = of_match_device(ov5695_dt_match, &pdev->dev);
	rc = msm_sensor_platform_probe(pdev, match->data);
	
vcm_value = create_proc_entry(POSITION_ov5695_PROC_FILE, S_IRUGO | S_IWUGO, NULL);
//			vcm_value->read_proc = vcm_value_read;
			vcm_value->write_proc = vcm_value_write;
		

		
	pr_info("%s:%d\n", __func__, __LINE__);	
	return rc;
}

static int __init ov5695_init_module(void)
{
	int32_t rc = 0;
	pr_info("%s:%d\n", __func__, __LINE__);
	rc = platform_driver_probe(&ov5695_platform_driver,
		ov5695_platform_probe);
	#ifdef ASUS_FACTORY_BUILD
	struct dentry *dent ;
	dent= debugfs_create_dir("ov5695", NULL);	\
	(void) debugfs_create_file("i2c_set", S_IRWXUGO,
					dent, NULL, &i2c_set_fops);
	(void) debugfs_create_file("i2c_get", S_IRWXUGO,
					dent, NULL, &i2c_get_fops);
	#endif
	if (!rc)
		return rc;
	pr_err("%s:%d rc %d\n", __func__, __LINE__, rc);
	return i2c_add_driver(&ov5695_i2c_driver);
}

static void __exit ov5695_exit_module(void)
{
	pr_info("%s:%d\n", __func__, __LINE__);
	if (ov5695_s_ctrl.pdev) {
		msm_sensor_free_sensor_data(&ov5695_s_ctrl);
		platform_driver_unregister(&ov5695_platform_driver);

	} else
		i2c_del_driver(&ov5695_i2c_driver);
	return;
}

static struct msm_sensor_ctrl_t ov5695_s_ctrl = {
	.sensor_i2c_client = &ov5695_sensor_i2c_client,
	.power_setting_array.power_setting = ov5695_power_setting,
	.power_setting_array.size = ARRAY_SIZE(ov5695_power_setting),
	.msm_sensor_mutex = &ov5695_mut,
	.sensor_v4l2_subdev_info = ov5695_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(ov5695_subdev_info),
};

module_init(ov5695_init_module);
module_exit(ov5695_exit_module);
MODULE_DESCRIPTION("ov5695");
MODULE_LICENSE("GPL v2");
