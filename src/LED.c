    #include "LED.h"



void init_led(){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable port B
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable port C

    // Sets the 3 registers for each LED color

    // RED PB4
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2));
    GPIOB->OSPEEDR |= (0x00000002 << (4 * 2));

    GPIOB->OTYPER &= ~(0x0001 << (4));
    GPIOB->OTYPER |= (0x0000 << (4));

    GPIOB->MODER &= ~(0x00000003 << (4 * 2));
    GPIOB->MODER |= (0x00000001 << (4 * 2));


    // GREEN PC7
    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2));
    GPIOC->OSPEEDR |= (0x00000002 << (7 * 2));

    GPIOC->OTYPER &= ~(0x0001 << (7));
    GPIOC->OTYPER |= (0x0000 << (7));

    GPIOC->MODER &= ~(0x00000003 << (7 * 2));
    GPIOC->MODER |= (0x00000001 << (7 * 2));

    // BLUE PA9
    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2));
    GPIOA->OSPEEDR |= (0x00000002 << (9 * 2));

    GPIOA->OTYPER &= ~(0x0001 << (9));
    GPIOA->OTYPER |= (0x0000 << (9));

    GPIOA->MODER &= ~(0x00000003 << (9 * 2));
    GPIOA->MODER |= (0x00000001 << (9 * 2));
}

void set_led(uint8_t color){
    // Set LED color depending on integer value
    // Available colors are
    // red
    // green
    // blue
    // cyan
    // magenta
    // yellow
    // white

    // RED
    if (color == 1){
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOB->ODR |= (0x0000 << 4);

        GPIOC->ODR &= ~(0x0000 << 7);
        GPIOC->ODR |= (0x0001 << 7);

        GPIOA->ODR &= ~(0x0000 << 9);
        GPIOA->ODR |= (0x0001 << 9);
    }

    // GREEN
    if (color == 2){
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOB->ODR |= (0x0001 << 4);

        GPIOC->ODR &= ~(0x0001 << 7);
        GPIOC->ODR |= (0x0000 << 7);

        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOA->ODR |= (0x0001 << 9);
    }

    // BLUE
    if (color == 4){
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOB->ODR |= (0x0001 << 4);

        GPIOC->ODR &= ~(0x0001 << 7);
        GPIOC->ODR |= (0x0001 << 7);

        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOA->ODR |= (0x0000 << 9);
    }

    // CYAN
    if (color == 8){
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOB->ODR |= (0x0001 << 4);

        GPIOC->ODR &= ~(0x0001 << 7);
        GPIOC->ODR |= (0x0000 << 7);

        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOA->ODR |= (0x0000 << 9);
    }

    // MAGENTA
    if (color == 16){
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOB->ODR |= (0x0000 << 4);

        GPIOC->ODR &= ~(0x0001 << 7);
        GPIOC->ODR |= (0x0001 << 7);

        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOA->ODR |= (0x0000 << 9);
    }

    // YELLOW
    if (color == 32){
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOB->ODR |= (0x0000 << 4);

        GPIOC->ODR &= ~(0x0001 << 7);
        GPIOC->ODR |= (0x0000 << 7);

        GPIOA->ODR &= ~(0x0000 << 9);
        GPIOA->ODR |= (0x0001 << 9);
    }

// WHITE
    if (color == 64){
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOB->ODR |= (0x0000 << 4);

        GPIOC->ODR &= ~(0x0001 << 7);
        GPIOC->ODR |= (0x0000 << 7);

        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOA->ODR |= (0x0000 << 9);
    }
}


void jstick_led(){
    uint16_t jstick; // Create joystick varialbe
    jstick = read_joystick(); // Read joystick
    set_led(jstick); // Pass joystick value to set the LED color
}

