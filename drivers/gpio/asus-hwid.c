#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/of.h>

// Get HW ID GPIO
#include "gpio-msm-common.h"

#ifdef ASUS_USER_BUILD
static bool asus_hwid_debug = false;
#else
static bool asus_hwid_debug = true;
#endif

// Get GPIO settings from struct gpiomux_setting
#include <mach/gpiomux.h>

extern int msm_gpiomux_get_setting(unsigned gpio, enum msm_gpiomux_setting which, struct gpiomux_setting *old_setting);

#define DRIVER_NAME "asus_hwid"

#define asus_hwid_PINCTRL_STATE_DEFAULT "asus_hwid_default"
#define asus_hwid_PINCTRL_STATE_SLEEP "asus_hwid_sleep"

struct asus_hwid_ctrl_pdata {
	int num_of_str;
	char board_sku[128];
};


static int asus_hwid_probe(struct platform_device *pdev)
{
	struct asus_hwid_ctrl_pdata *ctrl_pdata = NULL;
	int rc = 0;
	const char *ptmpstr;
	int ret;

	if(asus_hwid_debug) printk(KERN_INFO "%s, find device tree.\n",__func__);
	if (!pdev->dev.of_node) {
		pr_err("%s, No device tree.\n",__func__);
		return -ENOTSUPP;
	}

	if(asus_hwid_debug) printk(KERN_INFO "%s, allocate control data.\n",__func__);
	ctrl_pdata = platform_get_drvdata(pdev);
	if (!ctrl_pdata) {
		ctrl_pdata = devm_kzalloc(&pdev->dev,
					  sizeof(struct asus_hwid_ctrl_pdata),
					  GFP_KERNEL);
		if (!ctrl_pdata) {
			pr_err("%s: FAILED: cannot alloc gpio ctrl data\n",
			       __func__);
			rc = -ENOMEM;
			goto error_no_mem;
		}
	}

	// get board sku
	ret = of_property_read_string(pdev->dev.of_node, "boardsku",&ptmpstr);
	if (ret) {
		pr_err("Error: boardsku name not found\n");
		goto err;
	}
	strcpy(ctrl_pdata->board_sku, ptmpstr);
	printk(KERN_INFO "%s: Got board sku: %s\n", __func__,ptmpstr);

	platform_set_drvdata(pdev, ctrl_pdata);

error_no_mem:
err:
	if ( ctrl_pdata ) {
		devm_kfree(&pdev->dev, ctrl_pdata);
	}

	return rc;
}

static int asus_hwid_remove(struct platform_device *pdev)
{
	if(asus_hwid_debug) printk(KERN_INFO "%s\n", __func__);
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id asus_hwid_dt_ids[] = {
	{ .compatible = "asus,hwid" },
	{},
};
MODULE_DEVICE_TABLE(of,asus_hwid_dt_ids);
#endif

static struct platform_driver asus_hwid_driver = {
	.probe		= asus_hwid_probe,
	.remove		= asus_hwid_remove,
	.driver = {
		.name		= DRIVER_NAME,
		.owner		= THIS_MODULE,
		.of_match_table	= of_match_ptr(asus_hwid_dt_ids),
	},
};


static int __init asus_hwid_init(void)
{
	int err = -ENODEV;
	if(asus_hwid_debug) printk(KERN_INFO "%s\n", __func__);
	err = platform_driver_register(&asus_hwid_driver);
	if(asus_hwid_debug) printk(KERN_INFO "%s, register platform driver: %d\n", __func__,err);
//out:
	return err;
}

static void __exit asus_hwid_exit(void)
{

	printk(KERN_INFO "%s\n", __func__);
	platform_driver_unregister(&asus_hwid_driver);

}

#define ZB501KL_MAX_GPIO	121  //MSM8928 gpio_0 - gpio_120, total 121
#define MAX_GPIO_NUM		ZB501KL_MAX_GPIO

static bool dump_all_gpio = true;
static u8 part=0;
static int all_gpio_dump(char *buffer, const struct kernel_param *kp)
{
	int count = 0;
	u8 index = 0, max_num = 61;
	unsigned int cfg_val, inout_val;
	unsigned int pin_no = 0;

	count = sprintf(buffer, "========== Start dump GPIO part %d==========\n", (part%2)+1);
	count += sprintf(buffer + count, "Total GPIO pins : %d\n", MAX_GPIO_NUM);
	if (part%2){
		index = 61;
		max_num = MAX_GPIO_NUM;
	}

	for (pin_no = index; pin_no < max_num; pin_no++) {
		cfg_val = __get_gpio_tlmm_config(pin_no);
		inout_val = __msm_gpio_get_inout(pin_no);
		count += sprintf(buffer + count, "[GP][%03d] cfg_val  :0x%04x , inout_val:0x%04x\n", pin_no, cfg_val, inout_val);
	}

	part++;
	return count;
}
static struct kernel_param_ops dump_all_gp_ops = {
	.get = all_gpio_dump,
};
module_param_cb(dump_all_gpio, &dump_all_gp_ops, &dump_all_gpio, 0644);

static unsigned int gpio_dump_index = 0;
static int set_gpio_dump_index(const char *val, const struct kernel_param *kp)
{
	int ret = 0;

	ret = kstrtouint(val, 10, &gpio_dump_index);
	if (ret < 0)
		return -EINVAL;

	return 0;
}

static int single_gpio_dump(char *buffer, const struct kernel_param *kp)
{
	int count = 0;
	u8 bias, func, drv_ma, direct, value;
	unsigned int cfg_val, inout_val;

	if(gpio_dump_index > (MAX_GPIO_NUM-1)) {
		count = sprintf(buffer, "[GP][%03d] is not exist!!! Total pins are 0 ~ %d", gpio_dump_index, (MAX_GPIO_NUM-1));
		return count;
	}
	
	cfg_val = __get_gpio_tlmm_config(gpio_dump_index);
	inout_val = __msm_gpio_get_inout(gpio_dump_index);
	count = sprintf(buffer, "[GP][%03d] cfg_val  :0x%04x , inout_val:0x%04x\n", gpio_dump_index, cfg_val, inout_val);

	bias = cfg_val & 0x3;
	func = (cfg_val & 0x3C) >> 2;
	drv_ma = (cfg_val & 0x1c0) >> 6;
	direct = (cfg_val & 0x200) >> 9;
	value = inout_val & 0x1;

	printk("[Pinctrl] [GP][%03d] bias 0x%x func 0x%x drv_ma 0x%x direct 0x%x value 0x%x\n", gpio_dump_index, bias, func, drv_ma, direct, value);

	count += sprintf(buffer+count, "          ");
	// function
	count += sprintf(buffer+count, "FUN_%d, ", func);

	// drive
	count += sprintf(buffer+count, "DRV_");
	switch(drv_ma){
		case 0:
			count += sprintf(buffer+count, "2_MA, ");
		break;
		case 1:
			count += sprintf(buffer+count, "4_MA, ");
		break;
		case 2:
			count += sprintf(buffer+count, "6_MA, ");
		break;
		case 3:
			count += sprintf(buffer+count, "8_MA, ");
		break;
		case 4:
			count += sprintf(buffer+count, "10_MA, ");
		break;
		case 5:
			count += sprintf(buffer+count, "12_MA, ");
		break;
		case 6:
			count += sprintf(buffer+count, "14_MA, ");
		break;
		case 7:
			count += sprintf(buffer+count, "16_MA, ");
		break;
		default:
			count += sprintf(buffer+count, "UNKNOW, ");
	}

	// pull
	count += sprintf(buffer+count, "BIAS_");
	switch(bias){
		case 0:
			count += sprintf(buffer+count, "NO_PULL, ");
		break;
		case 1:
			count += sprintf(buffer+count, "PULL_DOWN, ");
		break;
		case 2:
			count += sprintf(buffer+count, "KEEPER, ");
		break;
		case 3:
			count += sprintf(buffer+count, "PULL_UP, ");
		break;
		default:
			count += sprintf(buffer+count, "UNKNOW, ");
		break;
	}

	// dir
	count += sprintf(buffer+count, "%s\n",direct?"OUTPUT":"INPUT" );

	// GPIO_IN
	count += sprintf(buffer+count, "GPIO_IN: %s\n",value?"H":"L" );

	return count;
}

static long dump_single_gpio;
static struct kernel_param_ops gpio_dump_ops = {
	.set = set_gpio_dump_index ,
	.get = single_gpio_dump,
};
module_param_cb(dump_single_gpio, &gpio_dump_ops, &dump_single_gpio, 0644);


//================================================================================
// Dump GPIOMUX Settings
//================================================================================
static unsigned int gpio_setting_index = 0;
static int set_gpio_setting_index(const char *val, const struct kernel_param *kp)
{
	int ret = 0;

	ret = kstrtouint(val, 10, &gpio_setting_index);
	if (ret < 0)
		return -EINVAL;

	return 0;
}

static const char *get_pull(enum gpiomux_pull pull) {

	switch(pull){
		case GPIOMUX_PULL_NONE:
			return "NONE";
		case GPIOMUX_PULL_DOWN:
			return "DOWN";
		case GPIOMUX_PULL_KEEPER:
			return "KEEPER";
		case GPIOMUX_PULL_UP:
			return "UP";

	}
	return "UNKNOWN PULL";
}


static const char *get_dir(enum gpiomux_dir dir) {

	switch(dir){
		case GPIOMUX_PULL_NONE:
			return "IN";
		case GPIOMUX_PULL_DOWN:
			return "OUT_HIGH";
		case GPIOMUX_PULL_KEEPER:
			return "OUT_LOW";
	}
	return "UNKNOWN DIR";
}

static int single_gpio_setting_dump(char *buffer, const struct kernel_param *kp)
{
	int count = 0;
	int err = 0;
	struct gpiomux_setting active_setting;
	struct gpiomux_setting suspend_setting;

	if(gpio_setting_index > (MAX_GPIO_NUM-1)) {
		count = sprintf(buffer, "[GP][%03d] is not exist!!! Total pins are 0 ~ %d\n", gpio_setting_index, (MAX_GPIO_NUM-1));
		return count;
	}

	// ACTIVE SETTING
	err = msm_gpiomux_get_setting(gpio_setting_index, GPIOMUX_ACTIVE, &active_setting);
	if(err) {
		count = sprintf(buffer, "[GP][%03d] Get ACTIVE gpio setting error, err: %d\n", gpio_setting_index, err);
		//return count;
	} else {
		count = sprintf(buffer, "[GP][%03d] ACTIVE: func: %d , drv: %dmA, pull: %s, dir: %s \n", 
			gpio_setting_index, active_setting.func, (active_setting.drv+1)*2, get_pull(active_setting.pull), get_dir(active_setting.dir));
	}

	// SUSPENDED SETTING
	err = msm_gpiomux_get_setting(gpio_setting_index, GPIOMUX_SUSPENDED, &suspend_setting);
	if(err) {
		count += sprintf(buffer+count, "[GP][%03d] Get SUSPEND gpio setting error, err: %d\n", gpio_setting_index, err);
		return count;
	}
	count += sprintf(buffer+count, "[GP][%03d] SUSPENDED: func: %d , drv: %dmA, pull: %s, dir: %s \n",
		gpio_setting_index, suspend_setting.func, (suspend_setting.drv+1)*2, get_pull(suspend_setting.pull), get_dir(suspend_setting.dir));

	return count;
}

static long dump_single_gpio_setting;
static struct kernel_param_ops gpio_setting_dump_ops = {
	.set = set_gpio_setting_index ,
	.get = single_gpio_setting_dump,
};
module_param_cb(dump_single_gpio_setting, &gpio_setting_dump_ops, &dump_single_gpio_setting, 0644);


// make initialization be latter than other drivers
late_initcall(asus_hwid_init);
//module_init(asus_hwid_init);
module_exit(asus_hwid_exit);

MODULE_AUTHOR("ASUS BSP team");
MODULE_DESCRIPTION("HW ID Driver for ASUS ZenFone Project");
MODULE_LICENSE("GPL");
