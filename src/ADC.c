
#include "ADC.h"


void init_adc(){

RCC->AHBENR |= RCC_AHBPeriph_GPIOA;

// PA0
GPIOA->MODER &= ~(0x00000003 << (0 * 2));
GPIOA->MODER |= (0x00000000 << (0 * 2)); // Set PA0 to input

GPIOA->PUPDR &= ~(0x00000003 << (0 * 2));
GPIOA->PUPDR |= (0x00000002 << (0 * 2)); // Pull-down

// PA1
GPIOA->MODER &= ~(0x00000003 << (1 * 2));
GPIOA->MODER |= (0x00000000 << (1 * 2)); // Set PA0 to input

GPIOA->PUPDR &= ~(0x00000003 << (1 * 2));
GPIOA->PUPDR |= (0x00000002 << (1 * 2)); // Pull-down

//PA7

GPIOA->MODER &= ~(0x00000003 << (7 * 2));
GPIOA->MODER |= (0x00000000 << (7 * 2)); // Set PA0 to input

GPIOA->PUPDR &= ~(0x00000003 << (7 * 2));
GPIOA->PUPDR |= (0x00000002 << (7 * 2)); // Pull-down

RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV8; // Set ADC12 prescaler to 8
RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12


ADC1->CR = 0x00000000; // Clear CR register
ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

//Verify ADVREG state (ADC voltage regulator)
//1. Set ADVREGEN from '10' (disabled state) to '00' and then to '01' (enabled)
//2. Wait 10uS (worst case) before performing calibration and/or
ADC1->CR &= ~ADC_CR_ADVREGEN;
ADC1->CR |= ADC_CR_ADVREGEN_0;
//Wait for at least 10uS before continuing...
for(uint32_t i = 0; i < 10000; i++);

ADC1->CR &= ~ADC_CR_ADEN; //Make sure ADC is disabled
ADC1->CR &= ~ADC_CR_ADCALDIF; //Use single ended calibration
ADC1->CR |= ADC_CR_ADCAL; //Start calibration
while((ADC1->CR & ADC_CR_ADCAL) == ADC_CR_ADCAL){} //Wait for calibration to finish
//Wait > 4 ADC clock cycles after ADCAL bit is cleared
for(uint32_t i = 0; i <100; i++);


// ENABLE INTERNAL VREFEN
ADC1_2->CCR |= ADC12_CCR_VREFEN;

//Enable ADC peripheral
ADC1->CR |= ADC_CR_ADEN;
//wait for ADC1 to be ready to start conversion
while (!ADC1->ISR & ADC_ISR_ADRD){}

}



uint16_t read_adc(uint8_t ch){

uint16_t ADCval; // Return value

if (ch == 1){
ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
}

if (ch == 2){
ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);
}

if (ch == 15){
ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_1Cycles5);
}

ADC_StartConversion(ADC1); // Start ADC read
while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
ADCval = ADC_GetConversionValue(ADC1);

ADCval = ADC_GetConversionValue(ADC1);

return ADCval;
}













