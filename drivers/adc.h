#ifndef DRIVERS_ADC_H
#define DRIVERS_ADC_H

#include <stdint.h>

void adc_init(void);
int16_t adc_read_temperature(void);

#endif
