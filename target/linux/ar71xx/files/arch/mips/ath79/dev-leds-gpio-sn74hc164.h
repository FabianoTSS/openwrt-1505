/* Copyright(c) 2016 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		dev-leds-gpio-sn74hc164.h
 * brief	SN74HC164 GPIO LEDs support
 *
 * author       Lin Cheyu <tony.lin@tp-link.com>
 * version      1.0.0
 * date         30Mar16
 *
 * history      \arg 1.0.0, 30Mar16, Lin Cheyu, Create the file.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#ifndef _ATH79_DEV_LEDS_GPIO_SN74HC164_H
#define _ATH79_DEV_LEDS_GPIO_SN74HC164_H

#include <linux/leds.h>

void ath79_register_sn74hc164_leds_gpio(unsigned num_gpios, struct led_gpio_set *gpios);

void ath79_register_sn74hc164_leds_dev(int id,
			      unsigned num_leds,
			      struct gpio_led *leds);

#endif /* _ATH79_DEV_LEDS_GPIO_SN74HC164_H */
