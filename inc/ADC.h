/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f30x_conf.h"
#include "30021_io.h"

#define VREFINT_CAL *((uint16_t*) ((uint32_t) 0x1FFFF7BA))

#ifndef ADC_H
#define ADC_H

void init_adc();
uint16_t read_adc(uint8_t ch);

#endif
