#include "PMW.h"
// FUNCTIONS MUST BE CALLED IN THE ORDER THEY APPEAR HERE

void init_pmw_tim16_clock(){
    RCC->APB2ENR |= RCC_APB2Periph_TIM16; // Enable timer 2 clock ;
    TIM16->CR1 = 0x0000; // Set timer 2 to ofF

    // Set ARR to 254
    TIM16->ARR = 0x00FE;

    // Prescaler 24
    TIM16->PSC = 0x0018;

    TIM16->CR1 |= 0x0001; // Set timer 2 to on
}


void init_pmw_tim16(){
    TIM16->CR1 |= 0x0000;
    // Set counter compare channel as output
    TIM16->CCER &= ~TIM_CCER_CC1P & ~TIM_CCER_CC1E;
    TIM16->CCER |= TIM_CCER_CC1E; // Set capture/compare on

    //Setup the TIMx_CCMR1 register:
    TIM16->CCMR1 &= ~TIM_CCMR1_CC1S & ~TIM_CCMR1_OC1PE & ~TIM_CCMR1_OC1M;
    //TIM_CCMR1_CC1S set to 00
    TIM16->CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM16->CCMR1 |= TIM_CCMR1_OC1M_2;
    TIM16->CCMR1 |= TIM_CCMR1_OC1PE; //ENABLE output compare 1 preload enable

    //Setup the TIM16 break/dead time register (TIMx_BDTR) to enable OCx output
    TIM16->BDTR &= ~TIM_BDTR_MOE & ~TIM_BDTR_OSSI & ~TIM_BDTR_OSSR;
    TIM16->BDTR |= TIM_BDTR_MOE;

    //Set duty cycle to 50% by writing the CCRx register
    TIM16->CCR1 = 64;
    TIM16->CR1 |= 0x0001;

}


void init_pmw_tim16_gpio(){
    //Set alternate function 1 for PA6 to map PA6 and TIM16_CH1
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

    //Set mode register for A, mask PA6 (AlternateFunction)
    //Set mode register(0x00-Input,0x01-Output,0x02-AlternateFunction,0x03-Analog in/out)
    GPIOA->MODER &= ~(GPIO_MODER_MODER6);
    GPIOA->MODER |= GPIO_MODER_MODER6_1;

    //Set push/pull register(_0x00-No pull_,0x01-Pull-up,0x02-Pull-down)
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR6);

    //set speed register(0x01-10MHz, 0x02-2MHz,_0x03-50MHz_)
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6; //reset
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR6_0;


    //Set alternate function register (GPIOx_AFRH) for PA6
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1);

}



