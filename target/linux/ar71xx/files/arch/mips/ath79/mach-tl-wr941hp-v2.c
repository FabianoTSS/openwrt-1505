#include <linux/platform_device.h>
#include <linux/ath9k_platform.h>
#include <linux/ar8216_platform.h>

#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "dev-m25p80.h"
#include "machtypes.h"
#include "pci.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#ifdef CONFIG_ATH79_DEV_LEDS_GPIO_SN74HC164
#include "dev-leds-gpio-sn74hc164.h"
#else
#include "dev-leds-gpio.h"
#endif
#include "dev-spi.h"
#include "dev-usb.h"
#include "dev-wmac.h"

#ifdef CONFIG_ATH79_DEV_LEDS_GPIO_SN74HC164
#define TL_WR941HP_V2_GPIO_LED_CLR              19
#define TL_WR941HP_V2_GPIO_LED_CLK              2
#define TL_WR941HP_V2_GPIO_LED_DATA             1
#else
#define TL_WR941HP_V2_GPIO_LED_PWR              18
#define TL_WR941HP_V2_GPIO_LED_WPS              3
#define TL_WR941HP_V2_GPIO_LED_LAN              7
#define TL_WR941HP_V2_GPIO_LED_WAN1             15
#define TL_WR941HP_V2_GPIO_LED_WAN2             14
#define TL_WR941HP_V2_GPIO_LED_WIFI2G           8
#define TL_WR941HP_V2_GPIO_LED_RE               6
#endif


#define TL_WR941HP_V2_GPIO_BTN_RE               5
#define TL_WR941HP_V2_GPIO_BTN_WPS              4
#define TL_WR941HP_V2_GPIO_BTN_WIFIONOFF        2
#define TL_WR941HP_V2_GPIO_BTN_RESET            1

#define TL_WR941HP_V2_KEYS_POLL_INTERVAL        20     /* msecs */
#define TL_WR941HP_V2_KEYS_DEBOUNCE_INTERVAL    (3 * TL_WR941HP_V2_KEYS_POLL_INTERVAL)

#define TL_WR941HP_V2_MAC0_OFFSET               0
#define TL_WR941HP_V2_MAC1_OFFSET               6
#define TL_WR941HP_V2_WMAC_CALDATA_OFFSET       0x1000

#ifdef CONFIG_ATH79_DEV_LEDS_GPIO_SN74HC164
/*
static struct led_gpio_set tl_wr941hp_v2_leds_gpio[] __initdata = {
	{
		.name		= "CLR",
		.gpio		= TL_WR941HP_V2_GPIO_LED_CLR,
	},
	{
                .name		= "CLK",
                .gpio		= TL_WR941HP_V2_GPIO_LED_CLK,
        },
	{
                .name		= "DATA",
                .gpio		= TL_WR941HP_V2_GPIO_LED_DATA,
        },
};

static struct gpio_led tl_wr941hp_v2_leds_dev[] __initdata = {
	{
		.name		= "wan1",
		.active_low	= 1,
		.gpio_clr	= TL_WR941HP_V2_GPIO_LED_CLR,
		.gpio_clk	= TL_WR941HP_V2_GPIO_LED_CLK,
		.gpio_data	= TL_WR941HP_V2_GPIO_LED_DATA,
        },
        {
		.name		= "wifi2g",
		.active_low	= 1,
		.gpio_clr	= TL_WR941HP_V2_GPIO_LED_CLR,
		.gpio_clk	= TL_WR941HP_V2_GPIO_LED_CLK,
		.gpio_data	= TL_WR941HP_V2_GPIO_LED_DATA,
        },
        {
		.name		= "wifi5g",
		.active_low	= 1,
		.gpio_clr	= TL_WR941HP_V2_GPIO_LED_CLR,
		.gpio_clk	= TL_WR941HP_V2_GPIO_LED_CLK,
		.gpio_data	= TL_WR941HP_V2_GPIO_LED_DATA,
        },
        {
		.name		= "re",
		.active_low	= 1,
		.gpio_clr	= TL_WR941HP_V2_GPIO_LED_CLR,
		.gpio_clk	= TL_WR941HP_V2_GPIO_LED_CLK,
		.gpio_data	= TL_WR941HP_V2_GPIO_LED_DATA,
        },
        {
		.name		= "wps",
		.active_low	= 1,
		.gpio_clr	= TL_WR941HP_V2_GPIO_LED_CLR,
		.gpio_clk	= TL_WR941HP_V2_GPIO_LED_CLK,
		.gpio_data	= TL_WR941HP_V2_GPIO_LED_DATA,
        },
        {
		.name		= "lan",
		.active_low	= 1,
		.gpio_clr	= TL_WR941HP_V2_GPIO_LED_CLR,
		.gpio_clk	= TL_WR941HP_V2_GPIO_LED_CLK,
		.gpio_data	= TL_WR941HP_V2_GPIO_LED_DATA,
        },
        {
		.name		= "wan2",
		.active_low	= 1,
		.gpio_clr	= TL_WR941HP_V2_GPIO_LED_CLR,
		.gpio_clk	= TL_WR941HP_V2_GPIO_LED_CLK,
		.gpio_data	= TL_WR941HP_V2_GPIO_LED_DATA,
        },
        {
		.name		= "status",
		.active_low	= 1,
		.gpio_clr	= TL_WR941HP_V2_GPIO_LED_CLR,
		.gpio_clk	= TL_WR941HP_V2_GPIO_LED_CLK,
		.gpio_data	= TL_WR941HP_V2_GPIO_LED_DATA,
        },
};
#else
static struct gpio_led tl_wr941hp_v2_leds_gpio[] __initdata = {
	{
		.name		= "wan1",
		.gpio		= TL_WR941HP_V2_GPIO_LED_WAN1,
		.active_low	= 1,
		.default_state	= LEDS_GPIO_DEFSTATE_KEEP,
	},
	{
		.name		= "wifi2g",
		.gpio		= TL_WR941HP_V2_GPIO_LED_WIFI2G,
		.active_low	= 1,
		.default_state	= LEDS_GPIO_DEFSTATE_KEEP,
	},
	{
		.name		= "re",
		.gpio		= TL_WR941HP_V2_GPIO_LED_RE,
		.active_low	= 1,
		.default_state	= LEDS_GPIO_DEFSTATE_KEEP,
	},
	{
		.name		= "wps",
		.gpio		= TL_WR941HP_V2_GPIO_LED_WPS,
		.active_low	= 1,
		.default_state	= LEDS_GPIO_DEFSTATE_KEEP,
	},
	{
		.name		= "lan",
		.gpio		= TL_WR941HP_V2_GPIO_LED_LAN,
		.active_low	= 1,
		.default_state	= LEDS_GPIO_DEFSTATE_KEEP,
	},
	{
		.name		= "wan2",
		.gpio		= TL_WR941HP_V2_GPIO_LED_WAN2,
		.active_low	= 1,
		.default_state	= LEDS_GPIO_DEFSTATE_KEEP,
	},
	{
		.name		= "status",
		.gpio		= TL_WR941HP_V2_GPIO_LED_PWR,
		.active_low	= 1,
		.default_state	= LEDS_GPIO_DEFSTATE_KEEP,
	},
};
#endif

static struct gpio_keys_button tl_wr941hp_v2_gpio_keys[] __initdata = {
	{
		.desc		= "RE button",
		.type		= EV_KEY,
		.code		= BTN_0,
		.debounce_interval = TL_WR941HP_V2_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= TL_WR941HP_V2_GPIO_BTN_RE,
		.active_low	= 1,
	},
	{
		.desc		= "WPS button",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = TL_WR941HP_V2_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= TL_WR941HP_V2_GPIO_BTN_WPS,
		.active_low	= 1,
	},
	{
		.desc		= "Wi-Fi ON/OFF button",
		.type		= EV_KEY,
		.code		= KEY_WLAN,
		.debounce_interval = TL_WR941HP_V2_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= TL_WR941HP_V2_GPIO_BTN_WIFIONOFF,
		.active_low	= 1,
	},
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = TL_WR941HP_V2_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= TL_WR941HP_V2_GPIO_BTN_RESET,
		.active_low	= 1,
	},
};
*/
static void __init tl_wr941hp_v2_setup(void)
{
	u8 *art = (u8 *) KSEG1ADDR(0x1fff0000);

	ath79_register_m25p80(NULL);

	ath79_register_usb();
	ath79_register_pci();

	ath79_register_wmac(art + TL_WR941HP_V2_WMAC_CALDATA_OFFSET, NULL);

	ath79_switch_data.phy4_mii_en = 1;

	ath79_register_mdio(0, 0x0);
	ath79_register_mdio(1, 0x0);

	ath79_init_mac(ath79_eth0_data.mac_addr, art + TL_WR941HP_V2_MAC0_OFFSET, 0);
	ath79_init_mac(ath79_eth1_data.mac_addr, art + TL_WR941HP_V2_MAC1_OFFSET, 0);

	/* WAN port */
	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_MII;
	ath79_eth0_data.speed = SPEED_100;
	ath79_eth0_data.duplex = DUPLEX_FULL;
	ath79_eth0_data.phy_mask = BIT(0);
	ath79_register_eth(0);

	/* LAN ports */
	ath79_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_GMII;
	ath79_eth1_data.speed = SPEED_100;
	ath79_eth1_data.duplex = DUPLEX_FULL;
	ath79_register_eth(1);

	ath79_switch_data.phy_poll_mask |= BIT(0);
	ath79_switch_data.phy4_mii_en = 1;
}

MIPS_MACHINE(ATH79_MACH_TL_WR941HP_V2, "TL-WR941HP-v2", "TP-LINK TL-WR941HP/v2",
	     tl_wr941hp_v2_setup);