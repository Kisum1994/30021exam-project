#include "openlog.h"


void init_pin_usart(uint32_t baud) {
    setbuf(stdout, NULL); // Set stdout to disable line buffering
    setbuf(stdin,  NULL); // Set stdin  to disable line buffering

    // Enable Clocks
    RCC->AHBENR  |= 0x00080000;    // Enable Clock for GPIO Bank C
    RCC->APB1ENR |= 0x00080000;    // Enable Clock for USART3

    // Connect pins to USART3
    // PC10 and PC11
    GPIOC->AFR[10 >> 0x03] &= ~(0x0000000F << ((10 & 0x00000007) * 4)); // Clear alternate function for PC10
    GPIOC->AFR[10 >> 0x03] |=  (0x00000007 << ((10 & 0x00000007) * 4)); // Set alternate 7 function (USART CONFIG) for PC10
    GPIOC->AFR[11 >> 0x03] &= ~(0x0000000F << ((11 & 0x00000007) * 4)); // Clear alternate function for PC11
    GPIOC->AFR[11 >> 0x03] |=  (0x00000007 << ((11 & 0x00000007) * 4)); // Set alternate 7 function (USART CONFIG) for PC11

    // Configure pins PC10 and PC11 for 10 MHz alternate function
    GPIOC->OSPEEDR &= ~(0x00000003 << (10 * 2) | 0x00000003 << (11 * 2));    // Clear speed register
    GPIOC->OSPEEDR |=  (0x00000001 << (10 * 2) | 0x00000001 << (11 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOC->OTYPER  &= ~(0x0001     << (10)     | 0x0001     << (11));        // Clear output type register
    GPIOC->OTYPER  |=  (0x0000     << (10)     | 0x0000     << (11));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOC->MODER   &= ~(0x00000003 << (10 * 2) | 0x00000003 << (11 * 2));    // Clear mode register
    GPIOC->MODER   |=  (0x00000002 << (10 * 2) | 0x00000002 << (11 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->PUPDR   &= ~(0x00000003 << (10 * 2) | 0x00000003 << (11 * 2));    // Clear push/pull register
    GPIOC->PUPDR   |=  (0x00000001 << (10 * 2) | 0x00000001 << (11 * 2));    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    //Configure USART3
    USART3->CR1 &= ~0x00000001; // Disable USART3
    USART3->CR2 &= ~0x00003000; // Clear CR2 Configuration
    USART3->CR2 |=  0x00000000; // Set 1 stop bits
    USART3->CR1 &= ~(0x00001000 | 0x00000400 | 0x00000200 | 0x00000008 | 0x00000004); // Clear CR1 Configuration
    USART3->CR1 |=  0x00000000; // Set word length to 8 bits
    USART3->CR1 |=  0x00000000; // Set parity bits to none
    USART3->CR1 |=  0x00000004 | 0x00000008; // Set mode to RX and TX
    USART3->CR3 &= ~(0x00000100 | 0x00000200); // Clear CR3 Configuration
    USART3->CR3 |=  0x00000000; // Set hardware flow control to none

    uint32_t divider = 0, apbclock = 0, tmpreg = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;
    RCC_GetClocksFreq(&RCC_ClocksStatus); // Get USART3 Clock frequency
    apbclock = RCC_ClocksStatus.USART3CLK_Frequency;

    if ((USART3->CR1 & 0x00008000) != 0) {
      // (divider * 10) computing in case Oversampling mode is 8 Samples
      divider = (2 * apbclock) / baud;
      tmpreg  = (2 * apbclock) % baud;
    } else {
      // (divider * 10) computing in case Oversampling mode is 16 Samples
      divider = apbclock / baud;
      tmpreg  = apbclock % baud;
    }

    if (tmpreg >=  baud / 2) {
        divider++;
    }

    if ((USART3->CR1 & 0x00008000) != 0) {
        // get the LSB of divider and shift it to the right by 1 bit
        tmpreg = (divider & (uint16_t)0x000F) >> 1;
        // update the divider value
        divider = (divider & (uint16_t)0xFFF0) | tmpreg;
    }

    USART3->BRR = (uint16_t)divider; // Configure baud rate
    USART3->CR1 |= 0x00000001; // Enable USART3
}


void uart_putc_3(uint8_t c) {
    USART_SendData(USART1, (uint8_t)c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)  == RESET){}
}



void init_pin_usart_2(uint32_t baud) {
    setbuf(stdout, NULL); // Set stdout to disable line buffering
    setbuf(stdin,  NULL); // Set stdin  to disable line buffering

    // Enable Clocks
    RCC->AHBENR  |= 0x00080000;    // Enable Clock for GPIO Bank C
    RCC->APB2ENR |= 0x00004000;    // Enable Clock for USART1

    // Connect pins to USART1
    // PC10 and PC11
    GPIOC->AFR[4 >> 0x03] &= ~(0x0000000F << ((4 & 0x00000007) * 4)); // Clear alternate function for PC10
    GPIOC->AFR[4 >> 0x03] |=  (0x00000007 << ((4 & 0x00000007) * 4)); // Set alternate 7 function (USART CONFIG) for PC10
    GPIOC->AFR[5 >> 0x03] &= ~(0x0000000F << ((5 & 0x00000007) * 4)); // Clear alternate function for PC11
    GPIOC->AFR[5 >> 0x03] |=  (0x00000007 << ((5 & 0x00000007) * 4)); // Set alternate 7 function (USART CONFIG) for PC11

    // Configure pins PC10 and PC11 for 10 MHz alternate function
    GPIOC->OSPEEDR &= ~(0x00000003 << (4 * 2) | 0x00000003 << (5 * 2));    // Clear speed register
    GPIOC->OSPEEDR |=  (0x00000001 << (4 * 2) | 0x00000001 << (5 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOC->OTYPER  &= ~(0x0001     << (4)     | 0x0001     << (5));        // Clear output type register
    GPIOC->OTYPER  |=  (0x0000     << (4)     | 0x0000     << (5));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOC->MODER   &= ~(0x00000003 << (4 * 2) | 0x00000003 << (5 * 2));    // Clear mode register
    GPIOC->MODER   |=  (0x00000002 << (4 * 2) | 0x00000002 << (5 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->PUPDR   &= ~(0x00000003 << (4 * 2) | 0x00000003 << (5 * 2));    // Clear push/pull register
    GPIOC->PUPDR   |=  (0x00000001 << (4 * 2) | 0x00000001 << (5 * 2));    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    //Configure USART1
    USART1->CR1 &= ~0x00000001; // Disable USART1
    USART1->CR2 &= ~0x00003000; // Clear CR2 Configuration
    USART1->CR2 |=  0x00000000; // Set 1 stop bits
    USART1->CR1 &= ~(0x00001000 | 0x00000400 | 0x00000200 | 0x00000008 | 0x00000004); // Clear CR1 Configuration
    USART1->CR1 |=  0x00000000; // Set word length to 8 bits
    USART1->CR1 |=  0x00000000; // Set parity bits to none
    USART1->CR1 |=  0x00000004 | 0x00000008; // Set mode to RX and TX
    USART1->CR3 &= ~(0x00000100 | 0x00000200); // Clear CR3 Configuration
    USART1->CR3 |=  0x00000000; // Set hardware flow control to none

    uint32_t divider = 0, apbclock = 0, tmpreg = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;
    RCC_GetClocksFreq(&RCC_ClocksStatus); // Get USART1 Clock frequency
    apbclock = RCC_ClocksStatus.USART1CLK_Frequency;

    if ((USART1->CR1 & 0x00008000) != 0) {
      // (divider * 10) computing in case Oversampling mode is 8 Samples
      divider = (2 * apbclock) / baud;
      tmpreg  = (2 * apbclock) % baud;
    } else {
      // (divider * 10) computing in case Oversampling mode is 16 Samples
      divider = apbclock / baud;
      tmpreg  = apbclock % baud;
    }

    if (tmpreg >=  baud / 2) {
        divider++;
    }

    if ((USART1->CR1 & 0x00008000) != 0) {
        // get the LSB of divider and shift it to the right by 1 bit
        tmpreg = (divider & (uint16_t)0x000F) >> 1;
        // update the divider value
        divider = (divider & (uint16_t)0xFFF0) | tmpreg;
    }

    USART1->BRR = (uint16_t)divider; // Configure baud rate
    USART1->CR1 |= 0x00000001; // Enable USART1
}









