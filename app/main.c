#include "../firmware/fan_controller.h"

#include <stdint.h>

#define UPDATE_DELAY_CYCLES 1600000u

static void periodic_delay(void)
{
    for (volatile uint32_t count = 0u; count < UPDATE_DELAY_CYCLES; ++count) {
        /* Volatile loop provides a simple platform-independent busy wait. */
    }
}

int main(void)
{
    fan_controller_init();

    for (;;) {
        fan_controller_update();
        periodic_delay();
    }
}
