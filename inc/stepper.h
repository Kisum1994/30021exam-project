#include <stdio.h>
#include "stm32f30x_conf.h"
#include "30021_io.h"

#ifndef STEPPER_H
#define STEPPER_H

void init_stepper();
void set_coil(uint16_t delay);

#endif STEPPER_H

