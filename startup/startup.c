#include <stdint.h>

typedef void (*exception_handler_t)(void);

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);
void Reset_Handler(void);
void Default_Handler(void);

#define WEAK_DEFAULT_HANDLER(name) \
    void name(void) __attribute__((weak, alias("Default_Handler")))

WEAK_DEFAULT_HANDLER(NMI_Handler);
WEAK_DEFAULT_HANDLER(HardFault_Handler);
WEAK_DEFAULT_HANDLER(MemManage_Handler);
WEAK_DEFAULT_HANDLER(BusFault_Handler);
WEAK_DEFAULT_HANDLER(UsageFault_Handler);
WEAK_DEFAULT_HANDLER(SVC_Handler);
WEAK_DEFAULT_HANDLER(DebugMon_Handler);
WEAK_DEFAULT_HANDLER(PendSV_Handler);
WEAK_DEFAULT_HANDLER(SysTick_Handler);

#define IRQ_1 Default_Handler
#define IRQ_2 IRQ_1, IRQ_1
#define IRQ_4 IRQ_2, IRQ_2
#define IRQ_8 IRQ_4, IRQ_4
#define IRQ_16 IRQ_8, IRQ_8
#define IRQ_32 IRQ_16, IRQ_16
#define IRQ_64 IRQ_32, IRQ_32

struct vector_table {
    const void *initial_stack;
    exception_handler_t reset;
    exception_handler_t nmi;
    exception_handler_t hard_fault;
    exception_handler_t memory_management;
    exception_handler_t bus_fault;
    exception_handler_t usage_fault;
    exception_handler_t reserved_7;
    exception_handler_t reserved_8;
    exception_handler_t reserved_9;
    exception_handler_t reserved_10;
    exception_handler_t supervisor_call;
    exception_handler_t debug_monitor;
    exception_handler_t reserved_13;
    exception_handler_t pend_sv;
    exception_handler_t systick;
    exception_handler_t external_irq[85];
};

__attribute__((section(".isr_vector"), used))
const struct vector_table interrupt_vectors = {
    .initial_stack = &_estack,
    .reset = Reset_Handler,
    .nmi = NMI_Handler,
    .hard_fault = HardFault_Handler,
    .memory_management = MemManage_Handler,
    .bus_fault = BusFault_Handler,
    .usage_fault = UsageFault_Handler,
    .reserved_7 = 0,
    .reserved_8 = 0,
    .reserved_9 = 0,
    .reserved_10 = 0,
    .supervisor_call = SVC_Handler,
    .debug_monitor = DebugMon_Handler,
    .reserved_13 = 0,
    .pend_sv = PendSV_Handler,
    .systick = SysTick_Handler,
    .external_irq = { IRQ_64, IRQ_16, IRQ_4, IRQ_1 }
};

void Reset_Handler(void)
{
    uint32_t *source = &_sidata;
    uint32_t *destination = &_sdata;

    while (destination < &_edata) {
        *destination = *source;
        ++destination;
        ++source;
    }

    destination = &_sbss;
    while (destination < &_ebss) {
        *destination = 0u;
        ++destination;
    }

    (void)main();
    for (;;) {
    }
}

void Default_Handler(void)
{
    for (;;) {
    }
}
