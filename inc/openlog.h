#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h"
#include <stdint.h>
#include <stdio.h>

#ifndef _OPENLOG_H_
#define _OPENLOG_H_

void init_pin_usart(uint32_t baud);
void uart_putc_3(uint8_t c);
void init_pin_usart_2(uint32_t baud);

#endif _OPENLOG_H
