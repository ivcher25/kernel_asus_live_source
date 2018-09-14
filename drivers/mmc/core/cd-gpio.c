/*
 * Generic GPIO card-detect helper
 *
 * Copyright (C) 2011, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/jiffies.h>
#include <linux/mmc/cd-gpio.h>
#include <linux/mmc/host.h>
#include <linux/module.h>
#include <linux/slab.h>

#ifdef CONFIG_SD_CD_WAKEUP
#include <linux/input.h>
#include <linux/notifier.h>
#include <linux/fb.h>
struct input_dev *cdgpio_input = 0;
static struct delayed_work __sdcard_wait_for_send_power_down_work;
static struct delayed_work __sdcard_wait_for_send_power_up_work;
//int cd_gpiot_fb_suspend = 0;
atomic_t cd_gpiot_fb_suspend;
static struct notifier_block cd_gpio_fb_notif;
#endif

struct mmc_cd_gpio {
	unsigned int gpio;
	bool status;
	char label[0];
};

static int mmc_cd_get_status(struct mmc_host *host)
{
	int ret = -ENOSYS;
	struct mmc_cd_gpio *cd = host->hotplug.handler_priv;

	if (!cd || !gpio_is_valid(cd->gpio))
		goto out;

	ret = !gpio_get_value_cansleep(cd->gpio) ^
		!!(host->caps2 & MMC_CAP2_CD_ACTIVE_HIGH);
out:
	return ret;
}

static irqreturn_t mmc_cd_gpio_irqt(int irq, void *dev_id)
{
	struct mmc_host *host = dev_id;
	struct mmc_cd_gpio *cd = host->hotplug.handler_priv;
	int status;

	status = mmc_cd_get_status(host);
	if (unlikely(status < 0))
		goto out;

#ifdef CONFIG_SD_CD_WAKEUP
	//if (cdgpio_input && cd_gpiot_fb_suspend) {
	if (cdgpio_input && atomic_read(&cd_gpiot_fb_suspend)) {
		schedule_delayed_work(&__sdcard_wait_for_send_power_down_work, msecs_to_jiffies(10));
		schedule_delayed_work(&__sdcard_wait_for_send_power_up_work, msecs_to_jiffies(100));
	}
#endif

	if (status ^ cd->status) {
		pr_info("%s: slot status change detected (%d -> %d), GPIO_ACTIVE_%s\n",
				mmc_hostname(host), cd->status, status,
				(host->caps2 & MMC_CAP2_CD_ACTIVE_HIGH) ?
				"HIGH" : "LOW");
		cd->status = status;

		/* Schedule a card detection after a debounce timeout */
		host->sd_rescan = 1;

	if (status)
		mmc_detect_change(host, msecs_to_jiffies(200));
	else
		mmc_detect_change(host, 0);

	}
out:
	return IRQ_HANDLED;
}

int mmc_cd_gpio_request(struct mmc_host *host, unsigned int gpio)
{
	size_t len = strlen(dev_name(host->parent)) + 4;
	struct mmc_cd_gpio *cd;
	int irq = gpio_to_irq(gpio);
	int ret;

	if (irq < 0)
		return irq;

	cd = kmalloc(sizeof(*cd) + len, GFP_KERNEL);
	if (!cd)
		return -ENOMEM;

	snprintf(cd->label, len, "%s cd", dev_name(host->parent));

	ret = gpio_request_one(gpio, GPIOF_DIR_IN, cd->label);
	if (ret < 0)
		goto egpioreq;

	cd->gpio = gpio;
	host->hotplug.irq = irq;
	host->hotplug.handler_priv = cd;

	ret = mmc_cd_get_status(host);
	if (ret < 0)
		goto eirqreq;

	cd->status = ret;

	ret = request_threaded_irq(irq, NULL, mmc_cd_gpio_irqt,
				   IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				   cd->label, host);

#ifdef CONFIG_SD_CD_WAKEUP
	if (!(host->caps & MMC_CAP_NONREMOVABLE)) {
		enable_irq_wake(irq);
	}
#endif

	if (ret < 0)
		goto eirqreq;

	return 0;

eirqreq:
	gpio_free(gpio);
egpioreq:
	kfree(cd);
	return ret;
}
EXPORT_SYMBOL(mmc_cd_gpio_request);

void mmc_cd_gpio_free(struct mmc_host *host)
{
	struct mmc_cd_gpio *cd = host->hotplug.handler_priv;

	if (!cd || !gpio_is_valid(cd->gpio))
		return;

	free_irq(host->hotplug.irq, host);
	gpio_free(cd->gpio);
	cd->gpio = -EINVAL;
	kfree(cd);
}
EXPORT_SYMBOL(mmc_cd_gpio_free);

#ifdef CONFIG_SD_CD_WAKEUP

void sdcard_wait_for_send_power_down_work(struct work_struct *work)
{
	if (cdgpio_input) {
		input_report_key(cdgpio_input, 116,1);
		input_sync(cdgpio_input);
		#ifndef ASUS_USER_BUILD
		printk("[CDGPIO] power key DOWN sent! \n");
		#endif
	}
}

void sdcard_wait_for_send_power_up_work(struct work_struct *work)
{
	if (cdgpio_input) {
		input_report_key(cdgpio_input, 116,0);
		input_sync(cdgpio_input);
		#ifndef ASUS_USER_BUILD
		printk("[CDGPIO] power key UP sent! \n");
		#endif
	}
}


static __init int cdgpio_config_input(void)
{

	#ifndef ASUS_USER_BUILD
	pr_info("%s: begin\n", __func__);
	#endif

	if (cdgpio_input) {
		pr_info("%s: power key wakeup for sdcard was set.\n", __func__);
		return 0;
	}

	cdgpio_input = input_allocate_device();
	if (!cdgpio_input) {
		pr_err("%s:Can't allocate cdgpio input device.\n", __func__);
		return -ENOMEM;
	}
	cdgpio_input->name = "cdgpioinput";
	cdgpio_input->phys = "cdgpioinput/input0";

	/* don't send dummy release event when system resumes */
	__set_bit(INPUT_PROP_NO_DUMMY_RELEASE, cdgpio_input->propbit);
	input_set_capability(cdgpio_input, EV_KEY, 116);

	/* register the input device */
	if (input_register_device(cdgpio_input)) {
		pr_err("%s:Can't register gpio power key.\n", __func__);
		return -ENOMEM;
	}

	INIT_DELAYED_WORK(&__sdcard_wait_for_send_power_down_work, sdcard_wait_for_send_power_down_work);
	INIT_DELAYED_WORK(&__sdcard_wait_for_send_power_up_work, sdcard_wait_for_send_power_up_work);

	return 0;
}

#ifdef CONFIG_SD_CD_WAKEUP
static int cd_gpio_fb_notifier_callback(struct notifier_block *self,
				 unsigned long event, void *data)
{
	int blank;
	struct fb_event *evdata = data;

	if (evdata && evdata->data && event == FB_EVENT_BLANK) {
		blank = *(int *)(evdata->data);
		if (blank == FB_BLANK_UNBLANK) {
			//cd_gpiot_fb_suspend = 0;
			atomic_set(&cd_gpiot_fb_suspend, 0);
		} else if (blank == FB_BLANK_POWERDOWN) {
			//cd_gpiot_fb_suspend = 1;
			atomic_set(&cd_gpiot_fb_suspend, 1);
		}
	}

	return 0;
}
#endif

static int __init cdgpio_init(void)
{
#ifdef CONFIG_SD_CD_WAKEUP
	int error;
#endif
	cdgpio_config_input();

#ifdef CONFIG_SD_CD_WAKEUP
	atomic_set(&cd_gpiot_fb_suspend, 0);
	cd_gpio_fb_notif.notifier_call = cd_gpio_fb_notifier_callback;
	error = fb_register_client(&cd_gpio_fb_notif);
	if (error) {
		printk("[CDGPIO] Unable to register cd_gpio_fb_notif: %d\n", error);
	}
#endif
	return 0;
}
module_init(cdgpio_init);
#endif
