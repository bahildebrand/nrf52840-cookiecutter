/**
 * @file startup.c
 * @author Blake Hildebrand (baugusthildebrand@gmail.com)
 * @brief Startup initialization for cortex-m MCUs.
 */

#include <stdint.h>

extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _data_lma;

void init_mem(void)
{
        /* initialize a pointer to the LMA address of the data section. */
        uint32_t *data_value_ptr = &_data_lma;

        /* Iterate through the entire bss section and initialize to 0. */
        for(uint32_t *bss_ptr = &_bss_start; bss_ptr < &_bss_end; bss_ptr++) {
                *bss_ptr = 0u;
        }

        /* Initialize data variables with values from data section in flash */
        for(uint32_t *data_ptr = &_data_start; data_ptr < &_data_end;) {
                *data_ptr++ = *data_value_ptr++;
        }
}