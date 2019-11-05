#include "joystick.h"
#include <stdint.h>
#include <stdio.h>
#include "stm32f30x_conf.h"


void init_joystick(){

	// INITIALISES JOYSTICK REGISTER INPUT

    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable port B
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable port C



    // %%%%%% RIGHT PC0 %%%%%%
    GPIOC->MODER &= ~(0x00000003 << (0 * 2));
    GPIOC->MODER |= (0x00000000 << (0 * 2));

    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2));
    GPIOC->PUPDR |= (0x00000002 << (0 * 2));

    // %%%%%% UP PA4 %%%%%%
    GPIOA->MODER &= ~(0x00000003 << (4 * 2));
    GPIOA->MODER |= (0x00000000 << (4 * 2));

    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2));
    GPIOA->PUPDR |= (0x00000002 << (4 * 2));

    // %%%%%% CENTER PB5 %%%%%%
    GPIOB->MODER &= ~(0x00000003 << (5 * 2));
    GPIOB->MODER |= (0x00000000 << (5 * 2));

    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2));
    GPIOB->PUPDR |= (0x00000002 << (5 * 2));

    // %%%%%% LEFT PC1 %%%%%%
    GPIOC->MODER &= ~(0x00000003 << (1 * 2));
    GPIOC->MODER |= (0x00000000 << (1 * 2));

    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2));
    GPIOC->PUPDR |= (0x00000002 << (1 * 2));

    // %%%%%% DOWN PB0 %%%%%%
    GPIOB->MODER &= ~(0x00000003 << (0 * 2));
    GPIOB->MODER |= (0x00000000 << (0 * 2));

    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2));
    GPIOB->PUPDR |= (0x00000002 << (0 * 2));
}



int8_t read_joystick(){
	// Return joystick integer depending on direction it is pressed
	//  int valfinal value
	// Nothing	0
	// UP		1
	// DOWN		2
	// LEFT		4
	// RIGHT	8
	// CENTER	16

    // Create joystick variables for each directio n
    uint16_t valfinal;
    uint16_t val0;
    uint16_t val1;
    uint16_t val2;
    uint16_t val3;
    uint16_t val4;

    valfinal = 0x0000; // Create return value variable and set return value to 0

    // valfinal is bitshifted depending on joystick input
    // UP
    val0 = (GPIOA->IDR & (0x0001 << 4)) >> 4;
    valfinal |= val0 << 0;

    // DOWN
    val1 = GPIOB->IDR & (0x0001 << 0);
    valfinal |= val1 << 1;

    // LEFT
    val2 = (GPIOC->IDR & (0x0001 << 1)) >> 1;
    valfinal |= val2 << 2;

    // RIGHT
    val3 = GPIOC->IDR & (0x0001 << 0);
    valfinal |= val3 << 3;

    // CENTER
    val4 = (GPIOB->IDR & (0x0001 << 5)) >> 5;
    valfinal |= val4 << 4;

    return valfinal;
}

void print_joystick(){
    // Prints joystick value only  when changed

    // Joystick parameters
    int8_t jstick_old = 0;
    int8_t jstick_new = 0;

    while(1){
    jstick_new = read_joystick(); // Read current joystick value

    if (jstick_old != jstick_new){
        printf("%d\n",jstick_new); // Prints current value
        jstick_old = read_joystick(); // Updates old joystick value
        }
    }

}



