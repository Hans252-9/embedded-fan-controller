#include "logger.h"

#include <stdint.h>

/* Polling USART2 logger on PA2, configured for 115200 baud at 16 MHz. */
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830u)
#define RCC_APB1ENR (*(volatile uint32_t *)0x40023840u)
#define GPIOA_MODER (*(volatile uint32_t *)0x40020000u)
#define GPIOA_AFRL (*(volatile uint32_t *)0x40020020u)
#define USART2_SR (*(volatile uint32_t *)0x40004400u)
#define USART2_DR (*(volatile uint32_t *)0x40004404u)
#define USART2_BRR (*(volatile uint32_t *)0x40004408u)
#define USART2_CR1 (*(volatile uint32_t *)0x4000440Cu)

static uint8_t logger_ready;

static void logger_init_once(void)
{
    if (logger_ready != 0u) {
        return;
    }

    RCC_AHB1ENR |= 1u << 0;
    RCC_APB1ENR |= 1u << 17;
    (void)RCC_APB1ENR;
    GPIOA_MODER = (GPIOA_MODER & ~(3u << 4)) | (2u << 4);
    GPIOA_AFRL = (GPIOA_AFRL & ~(0xFu << 8)) | (7u << 8);
    USART2_BRR = 0x008Bu;
    USART2_CR1 = (1u << 13) | (1u << 3);
    logger_ready = 1u;
}

static void write_text(const char *text)
{
    if (text == (const char *)0) {
        return;
    }
    while (*text != '\0') {
        while ((USART2_SR & (1u << 7)) == 0u) {
        }
        USART2_DR = (uint8_t)*text;
        ++text;
    }
}

static void log_message(const char *level, const char *message)
{
    logger_init_once();
    write_text(level);
    write_text(message);
    write_text("\r\n");
}

void log_info(const char *message)
{
    log_message("INFO: ", message);
}

void log_error(const char *message)
{
    log_message("ERROR: ", message);
}
