#include "stepper.h"

void init_stepper(){
	// INITIALISES STEPPER MOTOR REGISTER OUTPUT

	// ENABLING PORTS
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable port B



    // %% PC8
    GPIOC->OSPEEDR &= ~(0x00000003 << (8 * 2));
    GPIOC->OSPEEDR |= (0x00000002 << (8 * 2));

    GPIOC->OTYPER &= ~(0x0001 << (8));
    GPIOC->OTYPER |= (0x0000 << (8));

    GPIOC->MODER &= ~(0x00000003 << (8 * 2));
    GPIOC->MODER |= (0x00000001 << (8 * 2));


    // %% PC6 %%
    GPIOC->OSPEEDR &= ~(0x00000003 << (6 * 2));
    GPIOC->OSPEEDR |= (0x00000002 << (6 * 2));

    GPIOC->OTYPER &= ~(0x0001 << (6));
    GPIOC->OTYPER |= (0x0000 << (6));

    GPIOC->MODER &= ~(0x00000003 << (6 * 2));
    GPIOC->MODER |= (0x00000001 << (6 * 2));

    // %% PC5%%
    GPIOC->OSPEEDR &= ~(0x00000003 << (5 * 2));
    GPIOC->OSPEEDR |= (0x00000002 << (5 * 2));

    GPIOC->OTYPER &= ~(0x0001 << (5));
    GPIOC->OTYPER |= (0x0000 << (5));

    GPIOC->MODER &= ~(0x00000003 << (5 * 2));
    GPIOC->MODER |= (0x00000001 << (5 * 2));

    // %% PB2%%
    GPIOB->OSPEEDR &= ~(0x00000003 << (2 * 2));
    GPIOB->OSPEEDR |= (0x00000002 << (2 * 2));

    GPIOB->OTYPER &= ~(0x0001 << (2));
    GPIOB->OTYPER |= (0x0000 << (2));

    GPIOB->MODER &= ~(0x00000003 << (2 * 2));
    GPIOB->MODER |= (0x00000001 << (2 * 2));
}


void set_coil(uint16_t delay){
    // delay in ms
     //uint8_t POSITIONS[4] = { 0b0101, 0b1001, 0b1010, 0b0110 };
     // PC8 PC6 PC5 PB2

     GPIOC->ODR &= ~(0x0001 << 8);
     GPIOC->ODR |= (0x0001 << 8); //HIGH

     GPIOC->ODR &= ~(0x0001 << 6);
     GPIOC->ODR |= (0x0000 << 6); //LOW

     GPIOC->ODR &= ~(0x0001 << 5);
     GPIOC->ODR |= (0x0001 << 5); //HIGH

     GPIOB->ODR &= ~(0x0001 << 2);
     GPIOB->ODR |= (0x0000 << 2);//LOW


    for (uint16_t i=0;i<delay*1000;i++){

    }

     GPIOC->ODR &= ~(0x0001 << 8);
     GPIOC->ODR |= (0x0001 << 8); //HIGH

     GPIOC->ODR &= ~(0x0001 << 6);
     GPIOC->ODR |= (0x0000 << 6); //LOW

     GPIOC->ODR &= ~(0x0001 << 5);
     GPIOC->ODR |= (0x0000 << 5); //LOW

     GPIOB->ODR &= ~(0x0001 << 2);
     GPIOB->ODR |= (0x0001 << 2);//HIGH

    for (uint16_t i=0;i<delay*1000;i++){

    }

     GPIOC->ODR &= ~(0x0001 << 8);
     GPIOC->ODR |= (0x0000 << 8); //LOW

     GPIOC->ODR &= ~(0x0001 << 6);
     GPIOC->ODR |= (0x0001 << 6); //HIGH

     GPIOC->ODR &= ~(0x0001 << 5);
     GPIOC->ODR |= (0x0000 << 5); //LOW

     GPIOB->ODR &= ~(0x0001 << 2);
     GPIOB->ODR |= (0x0001 << 2);//HIGH

     for (uint16_t i=0;i<delay*1000;i++){

    }

     GPIOC->ODR &= ~(0x0001 << 8);
     GPIOC->ODR |= (0x0000 << 8); //LOW

     GPIOC->ODR &= ~(0x0001 << 6);
     GPIOC->ODR |= (0x0001 << 6); //HIGH

     GPIOC->ODR &= ~(0x0001 << 5);
     GPIOC->ODR |= (0x0001 << 5); //HIGH

     GPIOB->ODR &= ~(0x0001 << 2);
     GPIOB->ODR |= (0x0000 << 2);//LOW

    for (uint16_t i=0;i<delay*1000;i++){

    }
}

