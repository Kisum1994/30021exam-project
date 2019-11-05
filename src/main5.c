
#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h" // Input/output library for this course
#include "ansi.h"
#include "gyro.h"
#include <stdint.h>
#include <stdio.h>



void main(void){

init_usb_uart(9600);
init_spi_gyro();
setup_gyro();

clrscr();
uint16_t x = 0;
uint16_t y = 0;
int16_t z = 0;
uint8_t data_ready;
uint8_t data_status1;
uint8_t data_status2;
int8_t test;

uint8_t whoami = 0x0F;

while(1){

    for (int i=0; i<1000; i++){ // Delay
    }

    z = read_gyro_x();
    printf("%d  \n ", z);


}
}







