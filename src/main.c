/**
 * @file main.c
 * @author Blake Hildebrand (baugusthildebrand@gmail.com)
 * @brief Main file for cortex-m4 bringup example.
 */

#include <stdint.h>

#include <nrfx_gpiote.h>

#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */

#define LED_PIN 14
#define LOOP_MAX 10000u

#define LED_TASK_STACK_SZ (configMINIMAL_STACK_SIZE * 2)

static void green_led_task(void *args);

StackType_t green_led_stack[LED_TASK_STACK_SZ];
StaticTask_t green_led_task_buffer;

int main(void)
{
        const nrfx_gpiote_out_config_t ledcfg = NRFX_GPIOTE_CONFIG_OUT_TASK_LOW;

        nrfx_gpiote_out_task_enable(LED_PIN);
        nrfx_gpiote_out_init(LED_PIN, &ledcfg);

        xTaskCreateStatic(
                green_led_task,
                "LED",
                LED_TASK_STACK_SZ,
                NULL,
                4,
                green_led_stack,
                &green_led_task_buffer);

        vTaskStartScheduler();

        return 0;
}

static void green_led_task(void *args)
{
        const TickType_t delay_ticks = 500 / portTICK_PERIOD_MS;

        while(1) {
                nrfx_gpiote_out_toggle(LED_PIN);
                vTaskDelay(delay_ticks);
        }
}