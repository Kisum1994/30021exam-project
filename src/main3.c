
#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h" // Input/output library for this course
#include "joystick.h"
#include "ansi.h"
#include "IRQ.h"
#include "ADC.h"
#include "PMW.h"
#include "stepper.h"
//#include "keyboard.h"
//#include "LCD.h"
#include <stdint.h>
#include <stdio.h>


void main(void){


init_usb_uart( 9600 );

init_adc();
init_spi_lcd();
init_stepper();
init_pmw_tim16_clock();
init_pmw_tim16();
init_pmw_tim16_gpio();



clrscr();


// Initializing variables


uint16_t adcread;
uint16_t VREFINT_DATA;
double VDDA;
double volsum = 0;
double volavg;
uint16_t i = 0;
double corfac = 1.004;

uint8_t buffer[512];
memset(buffer, 0x00, 512); // Reset buffer

double absvol;

char arr[10];


ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_19Cycles5);
ADC_StartConversion(ADC1); // Start ADC read
while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
VREFINT_DATA = ADC_GetConversionValue(ADC1);
VDDA = 3.3*(VREFINT_CAL)/(VREFINT_DATA);

// This for loop is used for rotating the stepper motor 360 degrees
uint8_t i;
for (i=0;i<50;i++){
    set_coil(20);
}

while(1){

    adcread = read_adc(15);
    absvol = VDDA/(4095)*adcread*corfac;

    volsum += absvol;
    i += 1;
    if (i==50){
       absvol = volsum/50;

        sprintf(arr, "%f", absvol);
        lcd_write_string(arr, 0, 0, buffer);
        lcd_push_buffer(buffer);
        gotoxy(1,1);
        printf("%f",absvol);
        i = 0;
        volsum = 0;
    }
}
}







