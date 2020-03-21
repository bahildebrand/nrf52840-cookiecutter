/**
 * @file board_init.c
 * @author Blake Hildebrand (baugusthildebrand@gmail.com)
 * @brief
 */

#include <nrfx_clock.h>
#include <nrfx_gpiote.h>
#include <string.h>

static void clk_event_handler(nrfx_clock_evt_type_t event);
static void clock_init(void);
static void gpio_init(void);

void board_init(void)
{
        clock_init();
        gpio_init();
}

static void gpio_init(void)
{
        nrfx_gpiote_init(10);
}

static void clock_init(void)
{
        nrfx_clock_init(clk_event_handler);
        nrfx_clock_enable();
        nrfx_clock_hfclk_start();
        // nrfx_clock_lfclk_start();
}

static void clk_event_handler(nrfx_clock_evt_type_t event)
{

}