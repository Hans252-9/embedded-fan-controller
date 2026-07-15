#include "adc.h"

#include <stdint.h>

/* Reference register map: a linear 10 mV/degree C sensor is on ADC1 channel 0. */
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830u)
#define RCC_APB2ENR (*(volatile uint32_t *)0x40023844u)
#define GPIOA_MODER (*(volatile uint32_t *)0x40020000u)
#define GPIOA_PUPDR (*(volatile uint32_t *)0x4002000Cu)

#define ADC1_SR (*(volatile uint32_t *)0x40012000u)
#define ADC1_CR2 (*(volatile uint32_t *)0x40012008u)
#define ADC1_SMPR2 (*(volatile uint32_t *)0x40012010u)
#define ADC1_SQR3 (*(volatile uint32_t *)0x40012034u)
#define ADC1_DR (*(volatile uint32_t *)0x4001204Cu)

#define ADC_FULL_SCALE 4095u
#define ADC_REFERENCE_MV 3300u

void adc_init(void)
{
    RCC_AHB1ENR |= 1u << 0;
    RCC_APB2ENR |= 1u << 8;
    (void)RCC_APB2ENR;

    GPIOA_MODER |= 3u; /* PA0 in analog mode. */
    GPIOA_PUPDR &= ~3u;
    ADC1_SMPR2 = (ADC1_SMPR2 & ~7u) | 4u;
    ADC1_SQR3 = 0u;
    ADC1_CR2 = 1u;
}

int16_t adc_read_temperature(void)
{
    uint32_t sample;
    uint32_t millivolts;

    ADC1_CR2 |= 1u << 30;
    while ((ADC1_SR & (1u << 1)) == 0u) {
        /* Conversion completes in hardware. */
    }

    sample = ADC1_DR & ADC_FULL_SCALE;
    millivolts = (sample * ADC_REFERENCE_MV) / ADC_FULL_SCALE;
    return (int16_t)(millivolts / 10u);
}
