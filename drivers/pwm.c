#include "pwm.h"

#include <stdint.h>

/* Reference register map: TIM3 channel 1 is routed to GPIOB pin 4 (AF2). */
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830u)
#define RCC_APB1ENR (*(volatile uint32_t *)0x40023840u)
#define GPIOB_MODER (*(volatile uint32_t *)0x40020400u)
#define GPIOB_AFRL (*(volatile uint32_t *)0x40020420u)

#define TIM3_CR1 (*(volatile uint32_t *)0x40000400u)
#define TIM3_EGR (*(volatile uint32_t *)0x40000414u)
#define TIM3_CCMR1 (*(volatile uint32_t *)0x40000418u)
#define TIM3_CCER (*(volatile uint32_t *)0x40000420u)
#define TIM3_PSC (*(volatile uint32_t *)0x40000428u)
#define TIM3_ARR (*(volatile uint32_t *)0x4000042Cu)
#define TIM3_CCR1 (*(volatile uint32_t *)0x40000434u)

#define PWM_PERIOD_COUNTS 640u
#define PWM_PIN 4u

void pwm_init(void)
{
    RCC_AHB1ENR |= 1u << 1;
    RCC_APB1ENR |= 1u << 1;
    (void)RCC_APB1ENR;

    GPIOB_MODER = (GPIOB_MODER & ~(3u << (PWM_PIN * 2u))) |
                  (2u << (PWM_PIN * 2u));
    GPIOB_AFRL = (GPIOB_AFRL & ~(0xFu << (PWM_PIN * 4u))) |
                 (2u << (PWM_PIN * 4u));

    TIM3_CR1 = 0u;
    TIM3_PSC = 0u;
    TIM3_ARR = PWM_PERIOD_COUNTS - 1u; /* 25 kHz at a 16 MHz timer clock. */
    TIM3_CCR1 = 0u;
    TIM3_CCMR1 = (6u << 4) | (1u << 3); /* PWM mode 1, preload enabled. */
    TIM3_CCER = 1u;
    TIM3_EGR = 1u;
    TIM3_CR1 = (1u << 7) | 1u;
}

void pwm_set_duty(uint8_t duty)
{
    if (duty > 100u) {
        duty = 100u;
    }

    TIM3_CCR1 = (PWM_PERIOD_COUNTS * (uint32_t)duty) / 100u;
}
