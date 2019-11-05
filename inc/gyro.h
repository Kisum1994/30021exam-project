/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f30x_conf.h"


#ifndef _GYRO_H_
#define _GYRO_H_

void init_spi_gyro();

void chip_select(uint8_t input);
int8_t spi_read_byte(uint8_t adress);
void spi_write_byte(uint8_t adress, uint8_t data);
void spi_set_bidirectional_rx();
void spi_set_bidirectional_tx();
int8_t spi_read_bidirectional(uint8_t adress);
uint16_t read_gyro_x();
uint16_t read_gyro_y();
int16_t read_gyro_z();
int8_t read_temp();

#endif _GYRO_H_
