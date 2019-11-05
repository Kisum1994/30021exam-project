/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/


#include "stm32f30x_conf.h" // STM32 config
#include "30021_io.h" // Input/output library for this course
#include "joystick.h"
#include "ansi.h"
#include "IRQ.h"
#include "ADC.h"
//#include "LCD.h"
#include <stdint.h>
#include <stdio.h>

/*

EXCERCISE 1
uint32_t power(uint32_t a, uint32_t exp) {
// calculates a^exp
 uint32_t i, r = a;
 for (i = 1; i <= exp-1; i++)
 r *= a;
 return(r);
}

int main(void)
    {
    uint32_t a;
    init_usb_uart( 9600 ); // Initialize USB serial at 9600 baud
    printf("\n\n x x^2 x^3 x^4\n");
    for (a = 0; a < 10; a++)
    printf("%8d%8d%8d%8d\n",a, power(a, 2), power(a, 3), power(a, 4));

    while(1){

    }
}
*/


int main(void){


init_usb_uart( 9600 );

init_adc();
init_joystick();
//init_led();
init_TIM2();
init_spi_lcd();
//init_TIM2_AF();
clrscr();

// Initializing variables
uint16_t adcread;
uint16_t VREFINT_DATA;
double VDDA = 3.3;
double VDDA2;
double volsum = 0;
double volavg;
uint16_t i = 0;
double corfac;

uint8_t buffer[512];
memset(buffer, 0xAA, 512); // Reset buffer

double absvol; // Voltage calculated using VDAA = 3.3
double absvol2; // Voltage calculated using internal reference

ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_19Cycles5);
ADC_StartConversion(ADC1); // Start ADC read
while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
VREFINT_DATA = ADC_GetConversionValue(ADC1);
VDDA2 = 3.3*(VREFINT_CAL)/(VREFINT_DATA);

gotoxy(1,1);
printf("ADC output");
gotoxy(20,1);
printf("Voltage 3.3");
gotoxy(40,1);
printf("Voltage INTREF");
gotoxy(1,4);
printf("Average voltage reading from multimeter input");
gotoxy(1,7);
printf("Correction factor");


lcd_write_string("Croissant", 0, 0, buffer);
lcd_write_string("Baguette", 64, 2, buffer);
lcd_push_buffer(buffer);

while(1){

adcread = read_adc(1);
absvol = VDDA/(4095)*adcread;
absvol2 = VDDA2/(4095)*adcread;


gotoxy(1,2);
printf("%d",adcread);
gotoxy(20,2);
printf("%f",absvol);
gotoxy(40,2);
printf("%f",absvol2);


volsum += absvol;
i += 1;

if (i == 16){
    volavg = volsum/16;
    gotoxy(1,5);
    printf("%f",volavg);
    i = 0;
    volsum = 0;
}

gotoxy(1,8);
corfac = 3.2/volavg;
printf("%f", corfac);



    }
}





















