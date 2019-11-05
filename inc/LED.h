#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h"
#include "joystick.h"
#include <stdint.h>
#include <stdio.h>

#ifndef _LED_H_
#define _LED_H_

void init_led();
void set_led(uint8_t color);
void jstick_led();

#endif

