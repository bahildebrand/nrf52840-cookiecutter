/**
 * @file main.c
 * @author Blake Hildebrand (baugusthildebrand@gmail.com)
 * @brief Main file for cortex-m4 bringup example.
 */

#include <stdint.h>

#include <nrfx_gpiote.h>

#define LED_PIN 14
#define LOOP_MAX 10000u

static void toggle_led(void);

int main(void)
{
        const nrfx_gpiote_out_config_t ledcfg = NRFX_GPIOTE_CONFIG_OUT_TASK_LOW;

        nrfx_gpiote_out_task_enable(LED_PIN);
        nrfx_gpiote_out_init(LED_PIN, &ledcfg);

        while(1) {
                toggle_led();
        }

        return 0;
}

static void toggle_led(void)
{
        uint32_t idx = 0u;

        nrfx_gpiote_out_toggle(LED_PIN);
        for(idx = 0; idx < 1000000; idx++) {;}
        nrfx_gpiote_out_toggle(LED_PIN);
        for(idx = 0; idx < 1000000; idx++) {;}
}