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

static struct i2c_client *as358a_client;

char as358a_I2C_read(struct i2c_client *client, u8 address)
{
	int ret = -1;
	struct i2c_msg msg;
	unsigned char buf[1];

	buf[0] = address;
	msg.addr = client->addr;
	msg.flags = 0; //Write
	msg.len = 1;
	msg.buf = (unsigned char *)buf;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if(ret == 1) { // 1 msg sent OK
		unsigned char r_buf[1];
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
	}

	return 0xFF;
}

void as358a_I2C_write(struct i2c_client *client, u8 address, u8 value)
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
}

void as358a_suspend(void)
{
}
EXPORT_SYMBOL(as358a_suspend);

void as358a_resume(void)
{
	if (!as358a_client)
		return;

	as358a_I2C_write(as358a_client, 0x00, 0x0D);
	as358a_I2C_read(as358a_client, 0x00);
	as358a_I2C_write(as358a_client, 0x01, 0x0D);
	as358a_I2C_read(as358a_client, 0x01);
}
EXPORT_SYMBOL(as358a_resume);

static int as358a_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int addr;

	as358a_client = client;
	addr = client->addr; //Slave Addr

	printk("MDSS: %s: Slave addr[%x]\n", __func__, addr);

	as358a_I2C_write(as358a_client, 0x00, 0x0D);
	as358a_I2C_read(as358a_client, 0x00);
	as358a_I2C_write(as358a_client, 0x01, 0x0D);
	as358a_I2C_read(as358a_client, 0x01);

	return 0;
}

static struct of_device_id as358a_i2c_table[] = {
	{ .compatible = "novatek,4532"}, //Compatible node must match dts
	{ },
};

static const struct i2c_device_id as358a_id[] = {
	{ "as358a", 0 },
	{ },
};

//I2C Driver Info
static struct i2c_driver as358a_driver = {
	.driver = {
		.name = "as358a",
		.owner = THIS_MODULE,
		.of_match_table = as358a_i2c_table,
	},
	.probe = as358a_probe,
	.id_table = as358a_id,
};


static int __init as358a_I2C_init(void)
{
	int ret = 0;
	printk("MDSS: %s: started.\n",__func__);
	ret = i2c_add_driver(&as358a_driver);

	return ret;
}

static void __exit as358a_I2C_exit(void)
{
	return;
}

module_init(as358a_I2C_init);
module_exit(as358a_I2C_exit);

MODULE_DESCRIPTION("as358a");
MODULE_LICENSE("GPL v2");
