#include <stdint.h>

void gpio_init(void)
{
}

void gpio_set(void)
{
}

void gpio_clear(void)
{
}

void pwm_init(void)
{
}

void pwm_set_duty(uint8_t duty)
{
    (void)duty;
}

void adc_init(void)
{
}

int16_t adc_read_temperature(void)
{
    return 25;
}

void log_info(const char *message)
{
    (void)message;
}

void log_error(const char *message)
{
    (void)message;
}