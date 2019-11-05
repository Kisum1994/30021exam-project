#include "IRQ.h"



void init_TIM2(){
//Initialise timer

    uint8_t priority=0; // Timer priority (0 is highest)
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable timer 2 clock ;

    TIM2->CR1 = 0x0000; // Set timer 2 to ofF
    TIM2->ARR = 0x0009C3FF; // Set reload value
    TIM2->PSC = 0x00000000; // Set prescale value to 0
    //TIM2->PSC = 0; // Set prescale value

    TIM2->DIER |= 0x0001; // Enable timer 2 interrupts

    NVIC_SetPriority(TIM2_IRQn, priority); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt

    TIM2->CR1 |= 0x0001; // Set timer 2 to on
}

void TIM2_IRQHandler(void){
//Interupt action. Keep it short!

// First two lines are used for the timer
    interrupt = 1;  // Set interrupt flag high
    TIM2->SR &= ~0x0001; // Clear interrupt bit


    // Next lines are used for the alternate function timer to measure pulse width and duty cycle.
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

    uint32_t ICValue1 = TIM_GetCapture1(TIM2); // Period
    uint32_t ICValue2 = TIM_GetCapture2(TIM2); // Duty/Width
    uint16_t ICValid = 1;
    uint32_t PW = -ICValue2+ICValue1;
    //printf("%d %d \n", ICValue1,ICValue2);
}

void timer(void){
    // Stopwatch function

    init_joystick(); // Initialize joystick

    init_TIM2();  // Initialize TIM2 for stopwatch setup

    // Time variables for 1/100 second, seconds, minutes and hours
    uint8_t cs = 0;
    uint8_t s = 0;
    uint8_t m = 0;
    uint8_t h = 0;
    uint8_t watch = 1; // Set watch on = 1, off = 0. Used when pausing watch

    // Initialize joystick variables
    int8_t jstick_old = 0;
    int8_t jstick_new = 0;


    clrscr(); // Clear screen

    // Print stopwatch information
    gotoxy(1,1);
    printf("Time since start");
    gotoxy(1,2);
    printf("Split time 1");
    gotoxy(1,3);
    printf("Split time 2");
    gotoxy(20,2);
    printf("--:--:--");
    gotoxy(20,3);
    printf("--:--:--");




    while(1){

    // Count 1/100 second
    if (interrupt == 1 && watch == 1){
        interrupt = 0; // Disable interrupt flag
        cs += 1; // Count 1/100 second
    }
    if (cs == 100){
        cs = 0; // Reset 1/100 second counter
        s += 1; // Add 1 second
        }
    if (s == 60){
        s = 0; // Reset second counter
        m += 1; // Add minute
        }
    if (m == 60){
        m = 0; // Reset minute counter
        h += 1; // Add hour
        }

    gotoxy(20,1);
    printf("%2d:%2d:%2d",h,m,s); // Print current time

    jstick_new = read_joystick();

    if (jstick_old != jstick_new){
        jstick_old = read_joystick();

        if (jstick_new == 16 && watch == 1){
            watch = 0; // Pause watch if joystick input is center and watch is on
            continue;
        }
        if (jstick_new == 16 && watch == 0){
            watch = 1; // Start watch if joystick input is center and watch is off
            continue;
        }
        if (jstick_new == 4 && watch == 1){
            gotoxy(20,2);
            printf("%2d:%2d:%2d:%2d",h,m,s,cs); // Print first split time if joystick input is left
        }
        if (jstick_new == 8 && watch == 1){
            gotoxy(20,3);
            printf("%2d:%2d:%2d:%2d",h,m,s,cs); // // Print second split time if joystick input right
        }
        if (jstick_new == 2){
            cs = 0;
            s = 0;
            m = 0;
            h = 0;
            // Reset time if joystick is pressed down
        }
    }
}
}








    void init_TIM2_AF(){
    //Set alternate function 1 for PA5 to map PA5 and TIM2_CH1

    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    RCC->APB1ENR |= RCC_APB1Periph_TIM2;

    TIM2->CR1 = 0x0000; // Configure timer 2 to of

    //Set mode register for A, mask PA5 (AlternateFunction)
    //Set mode register(0x00-Input,0x01-Output,0x02-AlternateFunc,0x03-Analog in/out)
    GPIOA->MODER &= ~(GPIO_MODER_MODER5);
    GPIOA->MODER |= GPIO_MODER_MODER5_1; //0b10 - AlternateFunction

    //Set push/pull register(_0x00-No pull_,0x01-Pull-up,0x02-Pull-down)
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR5);
    //GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR0_0); //0b01 - pull up
    //Set alternate function register (GPIOx_AFRH) for PA5
    //AF1 - Alternate Function 1 corresponds to TIM2_CH1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_1);



    // SET CR2 TI1S REGISTERS
    TIM2->CR2 &= ~TIM_CR2_TI1S;
    TIM2->CR2 |= TIM_CR2_TI1S; //SET CR2 TO T1 XOR COMBINATION (0b1 XOR 0b0 noget andet)

    // disable counter capture by clearing the CC1E and CC2E bits in the TIMx_CCER register
    TIM2->CCER &= (~TIM_CCER_CC2E) & (~TIM_CCER_CC1E);


    //#1
    // Set the active input for TIMx_CCR1/2. CC1/2S bits set to ‘01’ in the TIMx_CCMR1 register:
    TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0; //0b01 – TI1 input

    //#2
    TIM2->CCMR1 &= ~TIM_CCMR1_CC2S;
    TIM2->CCMR1 |= TIM_CCMR1_CC2S_1; //0b10 – TI1 input

    //#1
    // Set the active polarity for TI1FP1. Rising edge
    TIM2->CCER &= ~(TIM_CCER_CC1NP) & ~(TIM_CCER_CC1P); //0b00 - Rising edge

    //#2
    TIM2->CCER &= ~(TIM_CCER_CC2NP) & ~(TIM_CCER_CC2P);
    // CC2P
    TIM2->CCER |= TIM_CCER_CC2P;




    // Set the input filter IC1F in the TIMx_CCMR1 register.
     TIM2->CCMR1 &= ~(TIM_CCMR1_IC1F);

    // Program the input prescaler IC1PSC in the TIMx_CCMR1 register
    TIM2->CCMR1 &= ~(TIM_CCMR1_IC1PSC);
    TIM2->CCMR1 &= ~(TIM_CCMR1_IC2PSC);


    // DIABLE SLAVES
    TIM2->SMCR &= ~TIM_SMCR_SMS;


    //TRIGGER INPUT ON RISING EDGE
    TIM2->SMCR &= (~TIM_SMCR_TS);
    TIM2->SMCR |= TIM_SMCR_TS_2;  //0b101
    TIM2->SMCR |= TIM_SMCR_TS_0;

    // SET SMS RESET MODE
    TIM2->SMCR |= TIM_SMCR_SMS_2;

    // ENABLE CC1E and CC2E to capture
    TIM2->CCER |= (TIM_CCER_CC1E);
    TIM2->CCER |= (TIM_CCER_CC2E);

    // PSC = 63
    // MAX TIME 4294 seconds
    //EXPECTED VALUES AROUND 50 and 100


    // SETTING PRESCALER
    TIM2->PSC = 0x003F;

    // SET AUTO LOAD REGUSTER
    TIM2->ARR = 0xFFFFFFFF;

    NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt

    // ENABLE TIMER
    TIM2->CR1 |= 0x0001; //Configure timer 2 to on

    // Reset + setup CC1 interrupts
    TIM2->DIER &= 0x0000;
    TIM2->DIER |= TIM_IT_CC1; //Enable TIM2 interrupts; TIM_IT_CC1
       TIM2->DIER |= TIM_IT_Update;



    }






















