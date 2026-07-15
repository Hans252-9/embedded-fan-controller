#ifndef FIRMWARE_FAN_CONTROLLER_H
#define FIRMWARE_FAN_CONTROLLER_H

#include <stdint.h>

void fan_controller_init(void);
void fan_controller_update(void);

/* Pure logic function that can be unit-tested on the host PC. */
uint8_t fan_controller_calculate_duty(int16_t temperature_c);

#endif