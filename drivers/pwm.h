#ifndef DRIVERS_PWM_H
#define DRIVERS_PWM_H

#include <stdint.h>

void pwm_init(void);
void pwm_set_duty(uint8_t duty);

#endif
