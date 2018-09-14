/* Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
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

#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <mach/board.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>
#include <mach/socinfo.h>

#define WLAN_CLK	44
#define WLAN_SET	43
#define WLAN_DATA0	42
#define WLAN_DATA1	41
#define WLAN_DATA2	40

#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
#define CONFIG_ASUS_GPIO_POWER_CTRL
#define CONFIG_NC_GPIO
#define CONFIG_VARIANT_CONTROL_PIN
#endif

#ifdef CONFIG_USB_EHCI_MSM_HSIC
static struct gpiomux_setting hsic_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting hsic_act_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config msm_hsic_configs[] = {
	{
		.gpio = 115,               /* HSIC_STROBE */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
	{
		.gpio = 116,               /* HSIC_DATA */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
};
#endif

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
static struct gpiomux_setting smsc_hub_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting smsc_hub_susp_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config smsc_hub_configs[] = {
	{
		.gpio = 114, /* reset_n */
		.settings = {
			[GPIOMUX_ACTIVE] = &smsc_hub_act_cfg,
			[GPIOMUX_SUSPENDED] = &smsc_hub_susp_cfg,
		},
	},
	{
		.gpio = 8, /* clk_en */
		.settings = {
			[GPIOMUX_ACTIVE] = &smsc_hub_act_cfg,
			[GPIOMUX_SUSPENDED] = &smsc_hub_susp_cfg,
		},
	},
	{
		.gpio = 9, /* int_n */
		.settings = {
			[GPIOMUX_ACTIVE] = &smsc_hub_act_cfg,
			[GPIOMUX_SUSPENDED] = &smsc_hub_susp_cfg,
		},
	},
};
#endif //#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )

#define KS8851_IRQ_GPIO 115

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
static struct gpiomux_setting gpio_eth_config = {
	.pull = GPIOMUX_PULL_UP,
	.drv = GPIOMUX_DRV_2MA,
	.func = GPIOMUX_FUNC_GPIO,
};

static struct msm_gpiomux_config msm_eth_configs[] = {
	{
		.gpio = KS8851_IRQ_GPIO,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_eth_config,
		}
	},
};
#endif
#endif //#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )

static struct gpiomux_setting elan_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting elan_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting elan_reset_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting elan_reset_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};
//#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
/*static struct gpiomux_setting elan_tpid_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
//#endif

static struct gpiomux_setting elan_tpid_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
*/

static struct gpiomux_setting ltr553_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting gpio_keys_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting gpio_keys_suspend = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting gpio_spi_act_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_spi_cs_act_config = {
	.func = GPIOMUX_FUNC_1,
	// [5816][Camera][KentChou][151006][Begin] SPI control for DTV
#if 0
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
#else
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_UP,
#endif
	// [5816][Camera][KentChou][151006][End] SPI control for DTV
};
static struct gpiomux_setting gpio_spi_susp_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	//[5816][Camera][KentChou][151114][Begin] reduce 0.05ma suspend current on DTV
#if 1
	.pull = GPIOMUX_PULL_DOWN,
#else
	.pull = GPIOMUX_PULL_NONE, //Not Use It, it will cause spi failed
#endif
	//[5816][Camera][KentChou][151114][end] reduce 0.05ma suspend current on DTV
	//[5816][Camera][KentChou][151110][Begin] reduce 0.2ma suspend current on DTV
	.dir = GPIOMUX_IN,
	//[5816][Camera][KentChou][151110][end] reduce 0.2ma suspend current on DTV
};
//[5816][Camera][KentChou][151114][Begin] reduce 0.05ma suspend current on DTV
static struct gpiomux_setting gpio_dtv_susp_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
//[5816][Camera][KentChou][151114][end] reduce 0.05ma suspend current on DTV
// [5816][Camera][KentChou][150921][Begin] laser sensor for AF
#if 0
static struct gpiomux_setting gpio_spi_cs_eth_config = {
	.func = GPIOMUX_FUNC_4,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif
// [5816][Camera][KentChou][150921][End] laser sensor for AF
static struct gpiomux_setting wcnss_5wire_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5wire_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting wcnss_5gpio_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5gpio_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

// [5816][FlashLED][akenhsu] Set GPIO107, 108, 110 and 111 for FlashLED in ER1 20150922 BEGIN
#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )  //darren mark for DTV configure
static struct gpiomux_setting gpio_lm3644tt_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting gpio_lm3644tt_suspend = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE, // AKenHsu: for Reduce power consumption of LM3644 enable pins
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config msm_lm3644tt_configs[] __initdata = {
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	{
		.gpio = 107,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_lm3644tt_active,
			[GPIOMUX_SUSPENDED] = &gpio_lm3644tt_suspend,
		},
	},
	{
		.gpio = 108,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_lm3644tt_active,
			[GPIOMUX_SUSPENDED] = &gpio_lm3644tt_suspend,
		},
	},
	#endif
	{
		.gpio = 110,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_lm3644tt_active,
			[GPIOMUX_SUSPENDED] = &gpio_lm3644tt_suspend,
		},
	},
	{
		.gpio = 111,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_lm3644tt_active,
			[GPIOMUX_SUSPENDED] = &gpio_lm3644tt_suspend,
		},
	},
	{
		.gpio = 21,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_lm3644tt_active,
			[GPIOMUX_SUSPENDED] = &gpio_lm3644tt_suspend,
		},
	},
};
#endif
// [5816][FlashLED][akenhsu] 20150922 END

static struct msm_gpiomux_config msm_keypad_configs[] __initdata = {
	{
		.gpio = 106,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_keys_active,
			[GPIOMUX_SUSPENDED] = &gpio_keys_suspend,
		},
	},
	/*
	#if defined(CONFIG_BSP_HW_SKU_ZB501KL)
	{
		.gpio = 107,
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_keys_active,
			[GPIOMUX_SUSPENDED] = &gpio_keys_suspend,
		},
	},
	#endif
	*/
};

static struct gpiomux_setting lcd_id_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting lcd_id_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting lcd_rst_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_OUT_HIGH,
};

static struct gpiomux_setting lcd_rst_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config msm_lcd_configs[] __initdata = {

	{
		.gpio = 20,		/* LCD ID */
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_id_act_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_id_sus_cfg,
		},
	},

	{
		.gpio = 25,		/* LCD Reset */
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_rst_act_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_rst_sus_cfg,
		},
	},
	{
		.gpio = 69,		/* P_+5VSO1_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_rst_act_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_rst_sus_cfg,
		},
	},
};

/* --- [5816][LuboLu] Find tune suspend current consumption 20151027 begin ---  */
// [5816][Camera][KentChou][15100602][Begin] SPI control for DTV
static struct gpiomux_setting dtv_gpio_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
// [5816][Camera][KentChou][15100602][End] SPI control for DTV

//[5816][Camera][kentchou][10102201][Begin]fix power control for laser sensor
#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
#if defined(CONFIG_STMVL6180)
/*static struct gpiomux_setting gpio_laser_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};*/
static struct gpiomux_setting gpio_laser_susp_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
#endif
#endif
//[5816][Camera][kentchou][10102201][End]fix power control for laser sensor
/* ---  [5816][LuboLu] 20151027 end ---  */

// [5816][Power][akenhsu] Reduce I2C power comsumption of Camera CCI 20151118 BEGIN
#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
static struct gpiomux_setting gpio_camera_i2c_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
#endif
// [5816][Power][akenhsu] 20151118 END
// [5816][Power][akenhsu] Reduce I2C power comsumption of Flash 20151118 BEGIN
static struct gpiomux_setting gpio_flash_i2c_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
// [5816][Power][akenhsu] 20151118 END

static struct msm_gpiomux_config msm_blsp_configs[] __initdata = {
	{
		.gpio      = 0,		/* BLSP1 QUP1 SPI_DATA_MOSI */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio      = 1,		/* BLSP1 QUP1 SPI_DATA_MISO */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	// [5816][Camera][KentChou][15100603][Begin] SPI control for DTV
	{
		.gpio      = 2,		/* BLSP1 QUP1 SPI_CS1 */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_cs_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	// [5816][Camera][KentChou][15100603][End] SPI control for DTV
	{
		.gpio      = 3,		/* BLSP1 QUP1 SPI_CLK */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio = 6,	/* BLSP1 QUP1 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio = 7,	/* BLSP1 QUP1 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio = 34,	/* LTR553 INT */
		.settings = {
			[GPIOMUX_ACTIVE] = &ltr553_act_cfg,
			[GPIOMUX_SUSPENDED] = &ltr553_act_cfg,
		},
	},
	{
		.gpio = 33,	/* LTR553 INT */
		.settings = {
			[GPIOMUX_ACTIVE] = &ltr553_act_cfg,
			[GPIOMUX_SUSPENDED] = &ltr553_act_cfg,
		},
	},
/* --- [5816][LuboLu] Find tune suspend current consumption 20151027 begin ---  */
	// [5816][Camera][KentChou][15100605][Begin] SPI control for DTV
	{
		.gpio = 36, /* DTV_RESET_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &dtv_gpio_act_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_dtv_susp_config,
		},
	},
	{
		.gpio = 52, /* GPIO_TV/FM_RF_SW */
		.settings = {
			[GPIOMUX_ACTIVE]    = &dtv_gpio_act_cfg,
			//[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	{
		.gpio = 50, /* DTV_1V8_EN_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &dtv_gpio_act_cfg,
			//[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
	// [5816][Camera][KentChou][15100605][End] SPI control for DTV

	//[5816][Camera][kentchou][10102202][Begin]fix power control for laser sensor
#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
/*	{
		.gpio      = 14,	// BLSP1 QUP4 I2C_SDA 
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_laser_act_cfg,
			//[GPIOMUX_SUSPENDED] = &gpio_laser_susp_config,
		},
	},*/
	#if defined(CONFIG_STMVL6180)
	{
		.gpio      = 20,	/* BLSP1 QUP4 I2C_SDA */
		.settings = {
			//[GPIOMUX_ACTIVE] = &gpio_laser_act_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_laser_susp_config,
		},
	},
	#endif
/* ---  [5816][LuboLu] 20151027 end ---  */
#else
	{
		.gpio      = 14,	/* BLSP1 QUP4 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 15,	/* BLSP1 QUP4 I2C_SCL */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
#endif
	{
		.gpio      = 18,		/* BLSP1 QUP5 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 19,		/* BLSP1 QUP5 I2C_SCL */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},

	{					/*  NFC   */
		.gpio      = 10,		/* BLSP1 QUP3 I2C_DAT */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
// [5816][Power][akenhsu] Reduce I2C power comsumption of Flash 20151118 BEGIN
#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
			[GPIOMUX_SUSPENDED] = &gpio_flash_i2c_suspend_config,
#else
// [5816][Power][akenhsu] 20151118 END
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
// [5816][Power][akenhsu] Reduce I2C power comsumption of Flash 20151118 BEGIN
#endif
// [5816][Power][akenhsu] 20151118 END
		},
	},
	{					/*  NFC   */
		.gpio      = 11,		/* BLSP1 QUP3 I2C_CLK */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
// [5816][Power][akenhsu] Reduce I2C power comsumption of Flash 20151118 BEGIN
#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
			[GPIOMUX_SUSPENDED] = &gpio_flash_i2c_suspend_config,
#else
// [5816][Power][akenhsu] 20151118 END
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
// [5816][Power][akenhsu] Reduce I2C power comsumption of Flash 20151118 BEGIN
#endif
// [5816][Power][akenhsu] 20151118 END
		},
	},
};

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
static struct msm_gpiomux_config msm_blsp_spi_cs_config[] __initdata = {
	{
		.gpio      = 2,		/* BLSP1 QUP1 SPI_CS1 */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_cs_act_config,
			[GPIOMUX_SUSPENDED] = &gpio_spi_susp_config,
		},
	},
};
#endif

static struct msm_gpiomux_config msm_elan_configs[] __initdata = {
	//#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
/*	{
		.gpio = 15,
		.settings = {
			[GPIOMUX_ACTIVE] = &elan_tpid_act_cfg,
			[GPIOMUX_SUSPENDED] = &elan_tpid_sus_cfg,
		},
	},*/
	//#endif
	{
		.gpio = 16,
		.settings = {
			[GPIOMUX_ACTIVE] = &elan_reset_act_cfg,
			[GPIOMUX_SUSPENDED] = &elan_reset_sus_cfg,
		},
	},
	{
		.gpio = 17,
		.settings = {
			[GPIOMUX_ACTIVE] = &elan_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &elan_int_sus_cfg,
		},
	},
};

/* --- [5816][LuboLu] Modify GPIO config for suspend current consumption 20151022 begin ---  */

#ifdef CONFIG_NC_GPIO
static struct gpiomux_setting gpio_nc_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
#else
static struct gpiomux_setting gpio_nc_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif /* CONFIG_NC_GPIO */

/*
static struct gpiomux_setting gpio_input_no_pull_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
*/

#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
static struct gpiomux_setting gpio_input_pull_high_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
#endif

#ifdef CONFIG_VARIANT_CONTROL_PIN
#if defined(CONFIG_BSP_HW_SKU_ZB501KL)
static struct gpiomux_setting gpio_variant_control_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
#endif
#endif /* CONFIG_VARIANT_CONTROL_PIN */

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
static struct gpiomux_setting goodix_ldo_en_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting goodix_ldo_en_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
static struct gpiomux_setting goodix_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting goodix_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting goodix_reset_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting goodix_reset_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
static struct msm_gpiomux_config msm_skuf_blsp_configs[] __initdata = {
	{
		.gpio      = 2,		/* NC */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio      = 3,		/* NC */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio      = 4,		/* NC */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
/*	{
		.gpio      = 14,	// NC 
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},*/
};

static struct msm_gpiomux_config msm_skuf_goodix_configs[] __initdata = {
/*	{
		.gpio = 15,		// LDO EN 
		.settings = {
			[GPIOMUX_ACTIVE] = &goodix_ldo_en_act_cfg,
			[GPIOMUX_SUSPENDED] = &goodix_ldo_en_sus_cfg,
		},
	},*/
	{
		.gpio = 16,		/* RESET */
		.settings = {
			[GPIOMUX_ACTIVE] = &goodix_reset_act_cfg,
			[GPIOMUX_SUSPENDED] = &goodix_reset_sus_cfg,
		},
	},
	{
		.gpio = 17,		/* INT */
		.settings = {
			[GPIOMUX_ACTIVE] = &goodix_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &goodix_int_sus_cfg,
		},
	},
	{
		.gpio      = 18,		/* BLSP1 QUP5 I2C_SDA */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 19,		/* BLSP1 QUP5 I2C_SCL */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
};
#endif

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
static struct gpiomux_setting nfc_ldo_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting nfc_ldo_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting nfc_regc_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting nfc_regc_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting nfc_wake_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting nfc_wake_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config msm_skuf_nfc_configs[] __initdata = {
	{					/*  NFC  LDO EN */
		.gpio      = 0,
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_ldo_act_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_ldo_sus_cfg,
		},
	},
	{					/*  NFC  REGC*/
		.gpio      = 1,
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_regc_act_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_regc_sus_cfg,
		},
	},
	{					/*  NFC   WAKE */
		.gpio      = 5,
		.settings = {
			[GPIOMUX_ACTIVE] = &nfc_wake_act_cfg,
			[GPIOMUX_SUSPENDED] = &nfc_wake_sus_cfg,
		},
	},
	{					/*  NFC   */
		.gpio      = 10,		/* BLSP1 QUP3 I2C_DAT */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{					/*  NFC   */
		.gpio      = 11,		/* BLSP1 QUP3 I2C_CLK */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
};
#endif //#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )

static struct gpiomux_setting sd_card_det_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	/*.pull = GPIOMUX_PULL_NONE,*/
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting sd_card_det_sleep_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config sd_card_det __initdata = {
	.gpio = 38,
	.settings = {
		[GPIOMUX_ACTIVE]    = &sd_card_det_active_config,
		[GPIOMUX_SUSPENDED] = &sd_card_det_sleep_config,
	},
};

static struct msm_gpiomux_config wcnss_5wire_interface[] = {
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 41,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 43,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 44,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
};

static struct msm_gpiomux_config wcnss_5gpio_interface[] = {
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
	{
		.gpio = 41,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
	{
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
	{
		.gpio = 43,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
	{
		.gpio = 44,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5gpio_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5gpio_suspend_cfg,
		},
	},
};

static struct gpiomux_setting cam_settings[] = {
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 0 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 1 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
	},

	{
		.func = GPIOMUX_FUNC_1, /*i2c suspend*/ /* 2 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_KEEPER,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*active 0*/ /* 3 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*suspend 0*/ /* 4 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
	},

// [5816][Power][akenhsu] Reduce power consumption of Camera Reset pin 20151119 BEGIN
#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
	{
		.func = GPIOMUX_FUNC_GPIO, /*suspend 1*/ /* 5 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},
#endif
// [5816][Power][akenhsu] 20151119 END
};


static struct msm_gpiomux_config msm_sensor_configs[] __initdata = {
	{
		.gpio = 26, /* CAM_MCLK0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &cam_settings[1],
		},
	},
	{
		.gpio = 29, /* CCI_I2C_SDA0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
		// [5816][Power][akenhsu] Reduce I2C power comsumption of Camera CCI 20151118 BEGIN
		#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
			[GPIOMUX_SUSPENDED] = &gpio_camera_i2c_suspend_config,
		#else
		// [5816][Power][akenhsu] 20151118 END
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		// [5816][Power][akenhsu] Reduce I2C power comsumption of Camera CCI 20151118 BEGIN
		#endif
		// [5816][Power][akenhsu] 20151118 END
		},
	},
	{
		.gpio = 30, /* CCI_I2C_SCL0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
		// [5816][Power][akenhsu] Reduce I2C power comsumption of Camera CCI 20151118 BEGIN
		#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
			[GPIOMUX_SUSPENDED] = &gpio_camera_i2c_suspend_config,
		#else
		// [5816][Power][akenhsu] 20151118 END
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		// [5816][Power][akenhsu] Reduce I2C power comsumption of Camera CCI 20151118 BEGIN
		#endif
		// [5816][Power][akenhsu] 20151118 END
		},
	},
#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
	{
		.gpio = 36, /* CAM1_STANDBY_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
#endif
	{
		.gpio = 37, /* CAM1_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
		// [5816][Power][akenhsu] Reduce power consumption of Camera Reset pin 20151119 BEGIN
		#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
			[GPIOMUX_SUSPENDED] = &cam_settings[5],
		#else
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		#endif
		// [5816][Power][akenhsu] 20151119 END
		},
	},
#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
	{
		.gpio = 35, /* CAM2_STANDBY_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
#endif	
	{
		.gpio = 28, /* CAM2_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
		// [5816][Power][akenhsu] Reduce power consumption of Camera Reset pin 20151119 BEGIN
		#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
			[GPIOMUX_SUSPENDED] = &cam_settings[5],
		#else
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		#endif
		// [5816][Power][akenhsu] 20151119 END
		},
	},

};

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
static struct msm_gpiomux_config msm_sensor_configs_skuf_plus[] __initdata = {
	{
		.gpio = 22, /* CAM1_VDD */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
};
#endif

#ifdef CONFIG_MMC_MSM_SDC3_SUPPORT
static struct gpiomux_setting sdc3_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdc3_cmd_data_0_3_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdc3_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sdc3_data_1_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config msm8226_sdc3_configs[] __initdata = {
	{
		/* DAT3 */
		.gpio      = 39,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* DAT2 */
		.gpio      = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* DAT1 */
		.gpio      = 41,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_data_1_suspend_cfg,
		},
	},
	{
		/* DAT0 */
		.gpio      = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* CMD */
		.gpio      = 43,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* CLK */
		.gpio      = 44,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
};

static void msm_gpiomux_sdc3_install(void)
{
	msm_gpiomux_install(msm8226_sdc3_configs,
			    ARRAY_SIZE(msm8226_sdc3_configs));
}
#else
static void msm_gpiomux_sdc3_install(void) {}
#endif /* CONFIG_MMC_MSM_SDC3_SUPPORT */

/*
static struct gpiomux_setting sensor_output_cfg[] = {
	{
		.func = GPIOMUX_FUNC_GPIO,
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_HIGH,
	},
};

static struct msm_gpiomux_config sensor_gpio_control[] __initdata = {
	{
		.gpio = 65,
		.settings = {
			[GPIOMUX_SUSPENDED] = &sensor_output_cfg[0],
			[GPIOMUX_ACTIVE] = &sensor_output_cfg[0],
		},
	},
	{
		.gpio = 66,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_input_no_pull_cfg,
			[GPIOMUX_ACTIVE] = &gpio_input_no_pull_cfg,
		},
	},
};
*/
//ASUS_BSP Jessy +++
static struct gpiomux_setting mi2s_act_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mi2s_sus_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting acc_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting acc_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hall_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting hall_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config smart_amp_i2c[] __initdata = {
	{
		.gpio      = 14,		/* BLSP1 QUP4 I2C_DAT */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 15,		/* BLSP1 QUP4 I2C_CLK */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_i2c_config,
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},

};

static struct msm_gpiomux_config msm_pri_mi2s_configs[] __initdata = {
	{
		.gpio = 63,		/* pri mi2s sclk */
		.settings = {
			[GPIOMUX_SUSPENDED] = &mi2s_sus_cfg,
			[GPIOMUX_ACTIVE] = &mi2s_act_cfg,
		},
	},
	{
		.gpio = 64,		/* pri mi2s ws */
		.settings = {
			[GPIOMUX_SUSPENDED] = &mi2s_sus_cfg,
			[GPIOMUX_ACTIVE] = &mi2s_act_cfg,
		},
	},
/*	{
		.gpio = 65,		// pri mi2s data0
		.settings = {
			[GPIOMUX_SUSPENDED] = &mi2s_sus_cfg,
			[GPIOMUX_ACTIVE] = &mi2s_act_cfg,
		},
	},*/
	{
		.gpio = 66,		/* pri mi2s data1 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &mi2s_sus_cfg,
			[GPIOMUX_ACTIVE] = &mi2s_act_cfg,
		},
	},
	{
		.gpio = 67,
		.settings = {
			[GPIOMUX_SUSPENDED] = &hall_int_act_cfg,
			[GPIOMUX_ACTIVE] = &hall_int_sus_cfg,
		},
	},
	{
		.gpio = 27,
		.settings = {
			[GPIOMUX_ACTIVE]    = &acc_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &acc_int_sus_cfg,
		},
	},

};
//ASUS_BSP Jessy ---

#ifdef CONFIG_ASUS_GPIO_POWER_CTRL
static struct msm_gpiomux_config asus_gpio_power_ctrl[] __initdata = {
	//ACCL_INT_N
/*	{
		.gpio = 63,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_input_no_pull_cfg,
			[GPIOMUX_ACTIVE] = &gpio_input_no_pull_cfg,
		},
	},
	//PROXIMITY_INT_N
	{
		.gpio = 64,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_input_pull_high_cfg,
			[GPIOMUX_ACTIVE] = &gpio_input_pull_high_cfg,
		},
	},*/
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	//GPIO104_PU
	{
		.gpio = 104,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_input_pull_high_cfg,
			[GPIOMUX_ACTIVE] = &gpio_input_pull_high_cfg,
		},
	},
	#endif
#ifdef CONFIG_VARIANT_CONTROL_PIN
	#if defined(CONFIG_BSP_HW_SKU_ZB501KL)
	//Variant control pins
	//HW ID0
	{
		.gpio = 22,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_variant_control_cfg,
			[GPIOMUX_ACTIVE] = &gpio_variant_control_cfg,
		},
	},
	//HW ID1
	{
		.gpio = 23,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_variant_control_cfg,
			[GPIOMUX_ACTIVE] = &gpio_variant_control_cfg,
		},
	},
	//HW ID2
	{
		.gpio = 24,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_variant_control_cfg,
			[GPIOMUX_ACTIVE] = &gpio_variant_control_cfg,
		},
	},
	//HW ID4
	{
		.gpio = 31,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_variant_control_cfg,
			[GPIOMUX_ACTIVE] = &gpio_variant_control_cfg,
		},
	},
	//TP ID 1
	{
		.gpio = 104,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_variant_control_cfg,
			[GPIOMUX_ACTIVE] = &gpio_variant_control_cfg,
		},
	},
	//TP ID 0
	{
		.gpio = 107,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_variant_control_cfg,
			[GPIOMUX_ACTIVE] = &gpio_variant_control_cfg,
		},
	},
	//RF ID1
	{
		.gpio = 108,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_variant_control_cfg,
			[GPIOMUX_ACTIVE] = &gpio_variant_control_cfg,
		},
	},
	//RF ID0
	{
		.gpio = 109,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_variant_control_cfg,
			[GPIOMUX_ACTIVE] = &gpio_variant_control_cfg,
		},
	},
	#endif //#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
#endif /* CONFIG_VARIANT_CONTROL_PIN */

#ifdef CONFIG_NC_GPIO
	//NC
	{
		.gpio = 4,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	{
		.gpio = 5,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	{
		.gpio = 31,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	#if defined(CONFIG_BSP_HW_SKU_ZB501KL)
	{
		.gpio = 32,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
    #if defined(CONFIG_BSP_HW_SKU_ZB501KL)
	{
		.gpio = 35,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	{
		.gpio = 49,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 51,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 52,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	/*
	#if defined(CONFIG_BSP_HW_SKU_ZB501KL)
	{
		.gpio = 56,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	*/
	{
		.gpio = 62,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 75,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 76,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 77,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 78,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 79,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 80,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 82,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 83,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 84,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 85,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 86,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	{
		.gpio = 88,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 89,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 90,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 91,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	{
		.gpio = 92,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 93,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	{
		.gpio = 94,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	{
		.gpio = 97,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 98,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 103,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	{
		.gpio = 109,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	{
		.gpio = 112,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#if defined(CONFIG_BSP_HW_SKU_ZB551KL)
	{
		.gpio = 114,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	#if defined(CONFIG_BSP_HW_SKU_ZB501KL)
	{
		.gpio = 115,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	#endif
	{
		.gpio = 117,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
	{
		.gpio = 118,
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_nc_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_nc_cfg,
		},
	},
#endif /* CONFIG_NC_GPIO */
};
#endif //#ifdef CONFIG_ASUS_GPIO_POWER_CTRL

void __init msm8226_init_gpiomux(void)
{
	int rc;

	rc = msm_gpiomux_init_dt();
	if (rc) {
		pr_err("%s failed %d\n", __func__, rc);
		return;
	}
#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
	msm_gpiomux_install(msm_eth_configs, ARRAY_SIZE(msm_eth_configs));
#endif
#endif

// [5816][FlashLED][akenhsu] Set GPIO107, 108, 110 and 111 for FlashLED in ER1 20150922 BEGIN
#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )  //darren mark for DTV configure
	msm_gpiomux_install(msm_lm3644tt_configs,
			ARRAY_SIZE(msm_lm3644tt_configs));
#endif
// [5816][FlashLED][akenhsu] 20150922 END

//Jessy +++
	msm_gpiomux_install(smart_amp_i2c,
			ARRAY_SIZE(smart_amp_i2c));

	msm_gpiomux_install(msm_pri_mi2s_configs,
			ARRAY_SIZE(msm_pri_mi2s_configs));
//Jessy ---


	msm_gpiomux_install(msm_keypad_configs,
			ARRAY_SIZE(msm_keypad_configs));

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
	if (of_board_is_skuf())
		msm_gpiomux_install(msm_skuf_blsp_configs,
			ARRAY_SIZE(msm_skuf_blsp_configs));
	else {
		msm_gpiomux_install(msm_blsp_configs,
			ARRAY_SIZE(msm_blsp_configs));
		if (machine_is_msm8226())
			msm_gpiomux_install(msm_blsp_spi_cs_config,
				ARRAY_SIZE(msm_blsp_spi_cs_config));
	}
#else
	msm_gpiomux_install(msm_blsp_configs,
		ARRAY_SIZE(msm_blsp_configs));
#endif
	msm_gpiomux_install(wcnss_5wire_interface,
				ARRAY_SIZE(wcnss_5wire_interface));

	msm_gpiomux_install(&sd_card_det, 1);
#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
	if (of_board_is_skuf())
		msm_gpiomux_install(msm_skuf_goodix_configs,
				ARRAY_SIZE(msm_skuf_goodix_configs));
	else
		msm_gpiomux_install(msm_elan_configs,
				ARRAY_SIZE(msm_elan_configs));
#else
	msm_gpiomux_install(msm_elan_configs,
			ARRAY_SIZE(msm_elan_configs));
#endif

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
	if (of_board_is_skuf())
		msm_gpiomux_install(msm_skuf_nfc_configs,
				ARRAY_SIZE(msm_skuf_nfc_configs));
#endif

	msm_gpiomux_install_nowrite(msm_lcd_configs,
			ARRAY_SIZE(msm_lcd_configs));

	msm_gpiomux_install(msm_sensor_configs, ARRAY_SIZE(msm_sensor_configs));


#if ( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
//	msm_gpiomux_install(sensor_gpio_control,
//			ARRAY_SIZE(sensor_gpio_control));
#else
	if (of_board_is_skuf())
		msm_gpiomux_install(msm_sensor_configs_skuf_plus,
			ARRAY_SIZE(msm_sensor_configs_skuf_plus));
#endif

	msm_gpiomux_sdc3_install();

	/*
	 * HSIC STROBE gpio is also used by the ethernet. Install HSIC
	 * gpio mux config only when HSIC is enabled. HSIC config will
	 * be disabled when ethernet config is enabled.
	 */
#ifdef CONFIG_USB_EHCI_MSM_HSIC
	msm_gpiomux_install(msm_hsic_configs, ARRAY_SIZE(msm_hsic_configs));
#endif

#if !( defined(CONFIG_BSP_HW_SKU_ZB551KL) || defined(CONFIG_BSP_HW_SKU_ZB501KL) )
	if (machine_is_msm8926() && of_board_is_mtp())
		msm_gpiomux_install(smsc_hub_configs,
			ARRAY_SIZE(smsc_hub_configs));
#endif

#ifdef CONFIG_ASUS_GPIO_POWER_CTRL
	msm_gpiomux_install(asus_gpio_power_ctrl,
		ARRAY_SIZE(asus_gpio_power_ctrl));
#endif
}

static void wcnss_switch_to_gpio(void)
{
	/* Switch MUX to GPIO */
	msm_gpiomux_install(wcnss_5gpio_interface,
			ARRAY_SIZE(wcnss_5gpio_interface));

	/* Ensure GPIO config */
	gpio_direction_input(WLAN_DATA2);
	gpio_direction_input(WLAN_DATA1);
	gpio_direction_input(WLAN_DATA0);
	gpio_direction_output(WLAN_SET, 0);
	gpio_direction_output(WLAN_CLK, 0);
}

static void wcnss_switch_to_5wire(void)
{
	msm_gpiomux_install(wcnss_5wire_interface,
			ARRAY_SIZE(wcnss_5wire_interface));
}

u32 wcnss_rf_read_reg(u32 rf_reg_addr)
{
	int count = 0;
	u32 rf_cmd_and_addr = 0;
	u32 rf_data_received = 0;
	u32 rf_bit = 0;

	wcnss_switch_to_gpio();

	/* Reset the signal if it is already being used. */
	gpio_set_value(WLAN_SET, 0);
	gpio_set_value(WLAN_CLK, 0);

	/* We start with cmd_set high WLAN_SET = 1. */
	gpio_set_value(WLAN_SET, 1);

	gpio_direction_output(WLAN_DATA0, 1);
	gpio_direction_output(WLAN_DATA1, 1);
	gpio_direction_output(WLAN_DATA2, 1);

	gpio_set_value(WLAN_DATA0, 0);
	gpio_set_value(WLAN_DATA1, 0);
	gpio_set_value(WLAN_DATA2, 0);

	/* Prepare command and RF register address that need to sent out.
	 * Make sure that we send only 14 bits from LSB.
	 */
	rf_cmd_and_addr  = (((WLAN_RF_READ_REG_CMD) |
		(rf_reg_addr << WLAN_RF_REG_ADDR_START_OFFSET)) &
		WLAN_RF_READ_CMD_MASK);

	for (count = 0; count < 5; count++) {
		gpio_set_value(WLAN_CLK, 0);

		rf_bit = (rf_cmd_and_addr & 0x1);
		gpio_set_value(WLAN_DATA0, rf_bit ? 1 : 0);
		rf_cmd_and_addr = (rf_cmd_and_addr >> 1);

		rf_bit = (rf_cmd_and_addr & 0x1);
		gpio_set_value(WLAN_DATA1, rf_bit ? 1 : 0);
		rf_cmd_and_addr = (rf_cmd_and_addr >> 1);

		rf_bit = (rf_cmd_and_addr & 0x1);
		gpio_set_value(WLAN_DATA2, rf_bit ? 1 : 0);
		rf_cmd_and_addr = (rf_cmd_and_addr >> 1);

		/* Send the data out WLAN_CLK = 1 */
		gpio_set_value(WLAN_CLK, 1);
	}

	/* Pull down the clock signal */
	gpio_set_value(WLAN_CLK, 0);

	/* Configure data pins to input IO pins */
	gpio_direction_input(WLAN_DATA0);
	gpio_direction_input(WLAN_DATA1);
	gpio_direction_input(WLAN_DATA2);

	for (count = 0; count < 2; count++) {
		gpio_set_value(WLAN_CLK, 1);
		gpio_set_value(WLAN_CLK, 0);
	}

	rf_bit = 0;
	for (count = 0; count < 6; count++) {
		gpio_set_value(WLAN_CLK, 1);
		gpio_set_value(WLAN_CLK, 0);

		rf_bit = gpio_get_value(WLAN_DATA0);
		rf_data_received |= (rf_bit << (count * 3 + 0));

		if (count != 5) {
			rf_bit = gpio_get_value(WLAN_DATA1);
			rf_data_received |= (rf_bit << (count * 3 + 1));

			rf_bit = gpio_get_value(WLAN_DATA2);
			rf_data_received |= (rf_bit << (count * 3 + 2));
		}
	}

	gpio_set_value(WLAN_SET, 0);
	wcnss_switch_to_5wire();

	return rf_data_received;
}
