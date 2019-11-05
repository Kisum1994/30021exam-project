/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f30x_conf.h"
#include "ansi.h"
#include "joystick.h"


#ifndef IRQ_H
#define IRQ_H

volatile uint8_t interrupt; // Global interupt


void init_TIM2();
void TIM2_IRQHandler(void);
void timer(void);
void init_TIM2_AF();
void TIM2_IRQHandler_AF(void);

#endif /* IRQ_H */

