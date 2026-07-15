#include "gpio.h"

#include <stdint.h>

/* Reference register map: GPIOA pin 5 drives the fan-enable signal. */
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830u)
#define GPIOA_MODER (*(volatile uint32_t *)0x40020000u)
#define GPIOA_OTYPER (*(volatile uint32_t *)0x40020004u)
#define GPIOA_OSPEEDR (*(volatile uint32_t *)0x40020008u)
#define GPIOA_PUPDR (*(volatile uint32_t *)0x4002000Cu)
#define GPIOA_BSRR (*(volatile uint32_t *)0x40020018u)

#define GPIOA_CLOCK_ENABLE (1u << 0)
#define FAN_ENABLE_PIN 5u

void gpio_init(void)
{
    RCC_AHB1ENR |= GPIOA_CLOCK_ENABLE;
    (void)RCC_AHB1ENR;

    GPIOA_MODER = (GPIOA_MODER & ~(3u << (FAN_ENABLE_PIN * 2u))) |
                  (1u << (FAN_ENABLE_PIN * 2u));
    GPIOA_OTYPER &= ~(1u << FAN_ENABLE_PIN);
    GPIOA_OSPEEDR &= ~(3u << (FAN_ENABLE_PIN * 2u));
    GPIOA_PUPDR &= ~(3u << (FAN_ENABLE_PIN * 2u));
    gpio_clear();
}

void gpio_set(void)
{
    GPIOA_BSRR = 1u << FAN_ENABLE_PIN;
}

void gpio_clear(void)
{
    GPIOA_BSRR = 1u << (FAN_ENABLE_PIN + 16u);
}
