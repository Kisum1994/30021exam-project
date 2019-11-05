#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h"
#include <stdint.h>
#include <stdio.h>

#ifndef _JOY_H_
#define _JOY_H_

int8_t read_joystick();
void init_joystick();
void print_joystick();

#endif
