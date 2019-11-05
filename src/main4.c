
#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h" // Input/output library for this course
#include "ansi.h"
#include "openlog.h"
#include <stdint.h>
#include <stdio.h>


void main(void){

init_usb_uart( 9600 );
init_pin_usart_2( 9600 );

clrscr();

uint8_t x = 0xAA;

while(1){

uart_putc_3(x);
}
}








