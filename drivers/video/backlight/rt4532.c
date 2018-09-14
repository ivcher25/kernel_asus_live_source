#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/regulator/consumer.h>
#include <linux/string.h>
#include <linux/of_gpio.h>
#include <linux/kernel.h>

static struct i2c_client *rt4532_client;
int bl_en_gpio;

char rt4532_I2C_read(struct i2c_client *client, u8 address)
{
	int ret = -1;
	struct i2c_msg msg;
	unsigned char buf[1];
	unsigned char r_buf[1];

	buf[0] = address;
	msg.addr = client->addr;
	msg.flags = 0; //Write
	msg.len = 1;
	msg.buf = (unsigned char *)buf;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if(ret == 1) { // 1 msg sent OK
		// Delay 1 ms, wait for f/w device data ready
		mdelay(2);
		//read back device information
		msg.addr = client->addr;
		msg.flags = I2C_M_RD; //Read
		msg.len = 1;
		msg.buf = (unsigned char *)r_buf;
		ret = i2c_transfer(client->adapter, &msg, 1);
		if (ret == 1) {
			printk("MDSS: %s: address(0x%x)=0x%02xh!\n", __FUNCTION__, address, r_buf[0]);
			return r_buf[0];
		}
	} else {
		printk("MDSS: %s: write failed !\n", __FUNCTION__);
		return 0xFF;
	}

	return r_buf[0];
}

void rt4532_I2C_write(struct i2c_client *client, u8 address, u8 value)
{
	int ret = -1;
	struct i2c_msg msg;
	unsigned char buf[2];

	buf[0] = address;
	buf[1] = value;
	msg.addr = client->addr;
	msg.flags = 0; //Write
	msg.len = 2;
	msg.buf = (unsigned char *)buf;
	ret = i2c_transfer(client->adapter, &msg, 1);
	printk("MDSS: %s: write i2c return 0x%x.\n", __FUNCTION__, ret);
}

void rt4532_I2C_readDeviceInfo(struct i2c_client *client)
{
	int ret = -1;
	struct i2c_msg msg;
	unsigned char buf[1];

	buf[0] = 0x00;
	msg.addr = client->addr;
	msg.flags = 0; //Write
	msg.len = 1;
	msg.buf = (unsigned char *)buf;
	printk("MDSS: %s: msg.addr (%x)\n", __func__, msg.addr);
	ret = i2c_transfer(client->adapter, &msg, 1);
	if( ret == 1) { // 1 msg sent OK
		unsigned char r_buf[1];
		// Delay 1 ms, wait for f/w device data ready
		printk("MDSS: %s: write OK!\n", __FUNCTION__);
		mdelay(2);
		//read back device information
		msg.addr = client->addr;
		msg.flags = I2C_M_RD; //Read
		msg.len = 1;
		msg.buf = (unsigned char *)r_buf;
		ret = i2c_transfer(client->adapter, &msg, 1);
		if (ret == 1) 
			printk("MDSS: %s: read OKKK REVID=0x%02xh.\n", __FUNCTION__,r_buf[0]);
	}
}

void rt4532_I2C_PWMmode_low_active(struct i2c_client *client)
{
	int ret = -1;
	struct i2c_msg msg;
	unsigned char buf[2];

	buf[0] = 0x02;
	buf[1] = 0xE7;
	msg.addr = client->addr;
	msg.flags = 0; //Write
	msg.len = 2;
	msg.buf = (unsigned char *)buf;
	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret != 1)
		printk("MDSS: %s: write 0x02 to 0xE7 failed.\n", __func__);
}

void rt4532_suspend(void)
{
	printk("MDSS: rt4532_suspend\n");
	if (rt4532_client) {
		rt4532_I2C_write(rt4532_client, 0x02, 0xC0);
		rt4532_I2C_read(rt4532_client, 0x02);
	}
	gpio_direction_output(bl_en_gpio, 0);
}
EXPORT_SYMBOL(rt4532_suspend);

void rt4532_resume(void)
{
	printk("MDSS: rt4532_resume\n");
	gpio_direction_output(bl_en_gpio, 1);
	if (rt4532_client) {
		rt4532_I2C_write(rt4532_client, 0x02, 0xC7);
		rt4532_I2C_read(rt4532_client, 0x02);
	}
}
EXPORT_SYMBOL(rt4532_resume);

static ssize_t rt4532_register_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	ssize_t count = 0;
	char ps_data[6];

	ps_data[0] = rt4532_I2C_read(rt4532_client, 0x00);
	ps_data[1] = rt4532_I2C_read(rt4532_client, 0x01);
	ps_data[2] = rt4532_I2C_read(rt4532_client, 0x02);
	ps_data[3] = rt4532_I2C_read(rt4532_client, 0x03);
	ps_data[4] = rt4532_I2C_read(rt4532_client, 0x04);
	ps_data[5] = rt4532_I2C_read(rt4532_client, 0x05);

	count += snprintf(&buf[count], PAGE_SIZE, "0x00 = 0x%x\n", ps_data[0]);
	count += snprintf(&buf[count], PAGE_SIZE, "0x01 = 0x%x\n", ps_data[1]);
	count += snprintf(&buf[count], PAGE_SIZE, "0x02 = 0x%x\n", ps_data[2]);
	count += snprintf(&buf[count], PAGE_SIZE, "0x03 = 0x%x\n", ps_data[3]);
	count += snprintf(&buf[count], PAGE_SIZE, "0x04 = 0x%x\n", ps_data[4]);
	count += snprintf(&buf[count], PAGE_SIZE, "0x05 = 0x%x\n", ps_data[5]);

	return count;
}

static ssize_t rt4532_register_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned int reg;
	unsigned int val;

	if (sscanf(buf, "%u %u\n", &reg, &val) < 2) {
		printk("MDSS: rt4532_register_store: argument error\n");
		return -EINVAL;
	}

	rt4532_I2C_write(rt4532_client, reg, val);

	return size;
}

static DEVICE_ATTR(register, S_IRUGO, rt4532_register_show, rt4532_register_store);

static struct attribute *rt4532_attr[] = {
	&dev_attr_register.attr,
	NULL
};

static const struct attribute_group rt4532_attr_group = {
	.attrs = rt4532_attr,
};

static int rt4532_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int addr, res;

	rt4532_client = client;
	addr = client->addr; //Slave Addr

	bl_en_gpio = of_get_named_gpio_flags(client->dev.of_node, "rt,bl-en-gpio", 0, NULL);
	if (gpio_request(bl_en_gpio, "bl_en_gpio") != 0)
		pr_err("MDSS: %s: request bl_en_gpio failed.\n", __func__);
	else
		gpio_direction_output(bl_en_gpio, 1);

	printk("MDSS: %s: Slave addr[%x] BL_EN(%d)\n", __func__, addr, bl_en_gpio);

#if 0
	rt4532_I2C_read(client, 0x02);
	rt4532_I2C_write(client, 0x02, 0x87); //set to manual config backlight by i2c
	rt4532_I2C_read(client, 0x02);
	rt4532_I2C_write(client, 0x04, 0xFF); //set backlight to 0xFF
#endif

	res = sysfs_create_group(&client->dev.kobj, &rt4532_attr_group);
	if (res) {
		dev_err(&client->dev, "sysfs create group failed\n");
	}

	return 0;
}

static struct of_device_id rt4532_i2c_table[] = {
	{ .compatible = "rt,4532"}, //Compatible node must match dts
	{ },
};

static const struct i2c_device_id rt4532_id[] = {
	{ "rt4532", 0 },
	{ },
};

//I2C Driver Info
static struct i2c_driver rt4532_driver = {
	.driver = {
		.name = "rt4532",
		.owner = THIS_MODULE,
		.of_match_table = rt4532_i2c_table,
	},
	.probe = rt4532_probe,
	.id_table = rt4532_id,
};


static int __init rt4532_I2C_init(void)
{
	int ret = 0;
	printk("MDSS: %s: started.\n",__func__);
	ret = i2c_add_driver(&rt4532_driver);

	return ret;
}

static void __exit rt4532_I2C_exit(void)
{
	return;
}

module_init(rt4532_I2C_init);
module_exit(rt4532_I2C_exit);

MODULE_DESCRIPTION("rt4532");
MODULE_LICENSE("GPL v2");
