/**
 * @file vectors.c
 * @author Blake Hildebrand (baugusthildebrand@gmail.com)
 * @brief Exception vectors for cortex-m MCUs
 */

#include <stdint.h>
#include <startup.h>
#include <board_init.h>

#include <nrfx_clock.h>

extern uint32_t _stack_end;

int main(void);

static void reset_handler(void);
static void nmi_handler(void);
static void hardfault_handler(void);
static void mem_management_fault_handler(void);
static void bus_fault_handler(void);
static void usage_fault_handler(void);
static void sv_call_handler(void);
static void pend_sv_handler(void);
static void systick_handler(void);

typedef void (*irq_func)(void);

/* Cortex-M vector table. These are all the core vectors as defined in the
 * Cortex-M spec. MCU vendors will expand this table with interrupt vectors
 * after the systick vector.
 * https://developer.arm.com/docs/dui0553/latest/the-cortex-m4-processor/exception-model/vector-table */
struct vector_table {
        void *stack_val;
        void *reset;
        void *nmi;
        void *hard_fault;
        void *mem_management_fault;
        void *bus_fault;
        void *usage_fault;
        void *reserved1[4];
        void *sv_call;
        void *debug;
        void *reserved2;
        void *pend_sv;
        void *systick;

        /* Begin IRQ handlers */
        irq_func power_clock;
        irq_func radio;
        irq_func uarte0_uart0;
        irq_func spim0_spis0_twim0_twis0_spi0_twi0;
        irq_func spim1_spis1_twim1_twis1_spi1_twi1;
        irq_func nfct;
        irq_func gpiote;
        irq_func saadc;
        irq_func timer0;
        irq_func time1;
        irq_func timer2;
        irq_func rtc0;
        irq_func temp;
        irq_func rng;
        irq_func ecb;
        irq_func ccm_aar;
        irq_func wdt;
        irq_func rtc1;
        irq_func qdec;
        irq_func comp_lpcomp;
        irq_func swi0_egu0;
        irq_func swi1_egu1;
        irq_func swi2_egu2;
        irq_func swi3_egu3;
        irq_func swi4_egu4;
        irq_func swi5_egu5;
        irq_func timer3;
        irq_func timer4;
        irq_func pwm0;
        irq_func pdm;
        irq_func mwu;
        irq_func pwm1;
        irq_func pwm2;
        irq_func spim2_spis2_spi2;
        irq_func rtc2;
        irq_func i2s;
        irq_func fpu;
        irq_func usbd;
        irq_func uarte1;
        irq_func qspi;
        irq_func cryptocell;
        irq_func pwm3;
        irq_func spim3;
};


/* Tells the linker to place vec_table in the .vecs section. This allows us to
 * place this section at the start of our memory map in the linker script. */
__attribute__ ((section(".vecs")))
struct vector_table vec_table = {
        .stack_val = (void*) &_stack_end,
        .reset = (void*) reset_handler,
        .nmi = (void*) nmi_handler,
        .hard_fault = (void*) hardfault_handler,
        .mem_management_fault = (void*) mem_management_fault_handler,
        .bus_fault = (void*) bus_fault_handler,
        .usage_fault = (void*) usage_fault_handler,
        .sv_call = (void*) sv_call_handler,
        .pend_sv = (void*) pend_sv_handler,
        .systick = (void*) systick_handler,
        /* IRQs */
        .power_clock = nrfx_clock_irq_handler,
};

static void reset_handler(void)
{
        init_mem();
        board_init();

        main();
}

static void nmi_handler(void)
{
        while(1) {;}
}

static void hardfault_handler(void)
{
        while(1) {;}
}

static void mem_management_fault_handler(void)
{
        while(1) {;}
}

static void bus_fault_handler(void)
{
        while(1) {;}
}

static void usage_fault_handler(void)
{
        while(1) {;}
}

static void sv_call_handler(void)
{

}

static void pend_sv_handler(void)
{

}

static void systick_handler(void)
{

}