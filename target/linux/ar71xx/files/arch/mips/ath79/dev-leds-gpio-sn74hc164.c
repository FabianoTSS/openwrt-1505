/* Copyright(c) 2016 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		dev-leds-gpio-sn74hc164.c
 * brief	SN74HC164 GPIO LEDs support
 *
 * author       Lin Cheyu <tony.lin@tp-link.com>
 * version      1.0.0
 * date         30Mar16
 *
 * history      \arg 1.0.0, 30Mar16, Lin Cheyu, Create the file.
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
*/


#include <linux/init.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <asm/gpio.h>

#include "dev-leds-gpio-sn74hc164.h"

void __init ath79_register_sn74hc164_leds_gpio(unsigned num_gpios, struct led_gpio_set *gpios)
{
	int i, ret;
	for (i = 0; i < num_gpios; i++) {
                struct led_gpio_set *led_gpio = &gpios[i];

		if (!gpio_is_valid(led_gpio->gpio)){
			printk(KERN_INFO "Skipping unavailable LED gpio %d (%s)\n",
				led_gpio->gpio, led_gpio->name);
		return;
		}

		ret = gpio_request(led_gpio->gpio, led_gpio->name);
		if (ret < 0)
			return;

		ret = gpio_direction_output(led_gpio->gpio, 0);
	        if (ret < 0)
		{
			gpio_free(led_gpio->gpio);
			return;
		}
	}
}

void __init ath79_register_sn74hc164_leds_dev(int id,
				     unsigned num_leds,
				     struct gpio_led *leds)
{
	struct platform_device *pdev;
	struct gpio_led_platform_data pdata;
	struct gpio_led *p;
	int err;

	p = kmalloc(num_leds * sizeof(*p), GFP_KERNEL);
	if (!p)
		return;

	memcpy(p, leds, num_leds * sizeof(*p));

	pdev = platform_device_alloc("leds-sn74hc164", id);
	if (!pdev)
		goto err_free_leds;

	memset(&pdata, 0, sizeof(pdata));
	pdata.num_leds = num_leds;
	pdata.leds = p;

	err = platform_device_add_data(pdev, &pdata, sizeof(pdata));
	if (err)
		goto err_put_pdev;

	err = platform_device_add(pdev);
	if (err)
		goto err_put_pdev;

	return;

err_put_pdev:
	platform_device_put(pdev);

err_free_leds:
	kfree(p);
}
