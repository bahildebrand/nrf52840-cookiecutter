/**
 * @file main.c
 * @author Blake Hildebrand (baugusthildebrand@gmail.com)
 * @brief Main file for cortex-m4 bringup example.
 */

#include <stdint.h>

#define LED_PIN 14
#define LOOP_MAX 10000u

#define ENABLE_PIN 3

#define GPIO_REGISTER 0x50000000
#define GPIO_SET_OFFSET 0x508
#define GPIO_SET_CLR 0x50C
#define GPIO_CONFIG_OFFSET 0x700

#define GPIO_SET_ADDR (GPIO_REGISTER + GPIO_SET_OFFSET)
#define GPIO_CLR_ADDR (GPIO_REGISTER + GPIO_SET_CLR)
#define LED_14_PIN_CONFG_ADDR  (GPIO_REGISTER + GPIO_CONFIG_OFFSET + LED_PIN * 4)

static void toggle_led(void);

int main(void)
{
        uint32_t *conf_gpio_ptr = (uint32_t *) LED_14_PIN_CONFG_ADDR;
        *conf_gpio_ptr = ENABLE_PIN;

        while(1) {
                toggle_led();
        }

        return 0;
}

static void toggle_led(void)
{
        uint32_t *set_gpio_ptr = (uint32_t *)GPIO_SET_ADDR;
        uint32_t *clr_gpio_ptr = (uint32_t *)GPIO_CLR_ADDR;

        uint32_t idx = 0u;
        *set_gpio_ptr = (1 << LED_PIN);
        for(idx = 0; idx < 1000000; idx++) {;}
        *clr_gpio_ptr = (1 << LED_PIN);
        for(idx = 0; idx < 1000000; idx++) {;}
}