#include "fan_controller.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    assert(fan_controller_calculate_duty(20) == 20u);
    assert(fan_controller_calculate_duty(29) == 20u);
    assert(fan_controller_calculate_duty(30) == 20u);
    assert(fan_controller_calculate_duty(35) == 40u);
    assert(fan_controller_calculate_duty(40) == 60u);
    assert(fan_controller_calculate_duty(45) == 80u);
    assert(fan_controller_calculate_duty(50) == 100u);
    assert(fan_controller_calculate_duty(70) == 100u);

    puts("All fan controller tests passed.");
    return 0;
}