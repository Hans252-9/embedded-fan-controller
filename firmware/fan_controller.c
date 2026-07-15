#include "fan_controller.h"

#include "../diagnostics/logger.h"
#include "../drivers/adc.h"
#include "../drivers/gpio.h"
#include "../drivers/pwm.h"

#include <stdint.h>

static uint8_t duty_for_temperature(int16_t temperature_c)
{
    if (temperature_c < 30) {
        return 20u;
    }
    if (temperature_c > 50) {
        return 100u;
    }

    return (uint8_t)(20 + ((temperature_c - 30) * 80) / 20);
}

void fan_controller_init(void)
{
    gpio_init();
    pwm_init();
    adc_init();

    pwm_set_duty(20u);
    gpio_set();
    log_info("fan controller initialized");
}

void fan_controller_update(void)
{
    const int16_t temperature_c = adc_read_temperature();
    const uint8_t duty = duty_for_temperature(temperature_c);

    pwm_set_duty(duty);
}
