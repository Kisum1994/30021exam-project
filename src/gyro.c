#include "gyro.h"

void init_spi_gyro() {
    // MISO PB10
    // MOSI PB15
    // SSEL PB12
    // SCLK PF1

    // Enable Clocks
    RCC->AHBENR  |= 0x00400000 | 0x00040000 | 0x00020000;    // Enable Clock for GPIO Banks A and B
    RCC->APB1ENR |= 0x00004000;                 // Enable Clock for SPI2

    // Connect pins to SPI2
    GPIOF->AFR[1 >> 0x03] &= ~(0x0000000F << ((1 & 0x00000007) * 4)); // Clear alternate function for PF1
    GPIOF->AFR[1 >> 0x03] |=  (0x00000005 << ((1 & 0x00000007) * 4)); // Set alternate 5 function for PF1 - SCLK
    GPIOB->AFR[15 >> 0x03] &= ~(0x0000000F << ((15 & 0x00000007) * 4)); // Clear alternate function for PB15
    GPIOB->AFR[15 >> 0x03] |=  (0x00000005 << ((15 & 0x00000007) * 4)); // Set alternate 5 function for PB15 - MOSI
    GPIOA->AFR[10 >> 0x03] &= ~(0x0000000F << ((10 & 0x00000007) * 4)); // Clear alternate function for PA10
    GPIOA->AFR[10 >> 0x03] |=  (0x00000005 << ((10 & 0x00000007) * 4)); // Set alternate 5 function for PA10 - MISO

    // Configure pins PB15 and PF1 for 10 MHz alternate function
    GPIOB->OSPEEDR &= ~(0x00000003 << (15 * 2));     // Clear speed register PB15
    GPIOF->OSPEEDR &= ~(0x00000003 << (1 * 2));      // Clear speed register PF1
    GPIOB->OSPEEDR |=  (0x00000001 << (15 * 2));     // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOF->OSPEEDR |=  (0x00000001 << (1 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER  &= ~(0x0001     << (15));           // Clear output type register
    GPIOF->OTYPER  &= ~(0x0001     << (1));        // Clear output type register
    GPIOB->OTYPER  |=  (0x0000     << (15));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOF->OTYPER  |=  (0x0000     << (1));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER   &= ~(0x00000003 << (15 * 2));   // Clear mode register
    GPIOF->MODER   &= ~(0x00000003 << (1 * 2));   // Clear mode register
    GPIOB->MODER   |=  (0x00000002 << (15 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOF->MODER   |=  (0x00000002 << (1 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR   &= ~(0x00000003 << (15 * 2));   // Clear push/pull register
    GPIOF->PUPDR   &= ~(0x00000003 << (1 * 2));   // Clear push/pull register
    GPIOB->PUPDR   |=  (0x00000000 << (15 * 2));  // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)
    GPIOF->PUPDR   |=  (0x00000000 << (1 * 2));  // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    // Configure pin PA10 for 10 MHz input MISO
    GPIOA->OSPEEDR &= ~(0x00000003 << (10 * 2));    // Clear speed register
    GPIOA->OSPEEDR |=  (0x00000001 << (10 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOA->OTYPER  &= ~(0x0001     << (10));       // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOA->OTYPER  |=  (0x0001     << (10));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOA->MODER   &= ~(0x00000003 << (10 * 2));    // Clear mode register
    GPIOA->MODER   |=  (0x00000002 << (10 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOA->PUPDR   &= ~(0x00000003 << (10 * 2));    // Clear push/pull register
    GPIOA->PUPDR   |=  (0x00000002 << (10 * 2));    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    // Configure pin PA12 for 10 MHz output CHIP SELECT
    GPIOB->OSPEEDR &= ~(0x00000003 << (12 * 2));    // Clear speed register
    GPIOB->OSPEEDR |=  (0x00000001 << (12 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER  &= ~(0x0001     << (12));        // Clear output type register
    GPIOB->OTYPER  |=  (0x0000     << (12));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER   &= ~(0x00000003 << (12 * 2));    // Clear mode register
    GPIOB->MODER   |=  (0x00000001 << (12 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR   &= ~(0x00000003 << (12 * 2));    // Clear push/pull register
    GPIOB->PUPDR   |=  (0x00000000 << (12 * 2));    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    // Configure SPI2
    SPI2->CR1 &= 0x3000; // Clear CR1 Register
    SPI2->CR1 |= 0x0000; // Configure direction (0x0000 - 2 Lines Full Duplex, 0x0400 - 2 Lines RX Only, 0x8000 - 1 Line RX, 0xC000 - 1 Line TX)
    SPI2->CR1 |= 0x0104; // Configure mode (0x0000 - Slave, 0x0104 - Master)
    SPI2->CR1 |= 0x0002; // Configure clock polarity (0x0000 - Low, 0x0002 - High)
    SPI2->CR1 |= 0x0001; // Configure clock phase (0x0000 - 1 Edge, 0x0001 - 2 Edge)
    SPI2->CR1 |= 0x0200; // Configure chip select (0x0000 - Hardware based, 0x0200 - Software based)
    SPI2->CR1 |= 0x0008; // Set Baud Rate Prescaler (0x0000 - 2, 0x0008 - 4, 0x0018 - 8, 0x0020 - 16, 0x0028 - 32, 0x0028 - 64, 0x0030 - 128, 0x0038 - 128)
    SPI2->CR1 |= 0x0000; // Set Bit Order (0x0000 - MSB First, 0x0080 - LSB First)

    // BIDIRECTIONAL DATA ENABLE
    //SPI2->CR1 |= 0x8000; // comment out for 2-line transmission

    SPI2->CR2 &= ~0x0F00; // Clear CR2 Register
    SPI2->CR2 |= 0x0700; // Set Number of Bits (0x0300 - 4, 0x0400 - 5, 0x0500 - 6, ...);
    SPI2->I2SCFGR &= ~0x0800; // Disable I2S
    SPI2->CRCPR = 7; // Set CRC polynomial order
    SPI2->CR2 &= ~0x1000;
    SPI2->CR2 |= 0x1000; // Configure RXFIFO return at (0x0000 - Half-full (16 bits), 0x1000 - Quarter-full (8 bits))
    SPI2->CR1 |= 0x0040; // Enable SPI2

}

void spi_set_bidirectional_tx(){
    SPI2->CR1 |= 0x4000;
}

void spi_set_bidirectional_rx(){
    SPI2->CR1 &= ~0x4000;
}

int8_t spi_read_byte(uint8_t adress) {
    int8_t val = 0x00;
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET) { }


    GPIOB->ODR &= ~(0x0001 << 12); // CS = 0 - Start Transmission

    SPI_SendData8(SPI2, adress);
    SPI_SendData8(SPI2, 0xF00);
    val = SPI_ReceiveData8(SPI2);

    for (int i=0; i<10; i++){ }

    GPIOB->ODR |=  (0x0001 << 12);

    return val;
}

int8_t spi_read_bidirectional(uint8_t adress) {
    int8_t val = 0x00;

    GPIOB->ODR &= ~(0x0001 << 12); // CS = 0 - Start Transmission
    SPI_SendData8(SPI2, adress); // Send adress to be read

    spi_set_bidirectional_rx(); // Set pin in receive mode
    val = SPI_ReceiveData8(SPI2); // Receive data

    spi_set_bidirectional_tx();
    for (int i=0; i<10; i++){ } // Delay

    GPIOB->ODR |=  (0x0001 << 12);

    return val;
}

void spi_write_byte(uint8_t adress, uint8_t data) {

    GPIOB->ODR &= ~(0x0001 << 12); // CS = 0 - Start Transmission

    SPI_SendData8(SPI2, adress);
    SPI_SendData8(SPI2, data);

    for (int i=0; i<10; i++){ }

    GPIOB->ODR |=  (0x0001 << 12);
}

void setup_gyro(){
    // CTRL_REG1
    spi_write_byte(0x20, 0x0F);

    // CTRL REG2 (NORMAL MODE RESET)
    spi_write_byte(0x21, 0x00);

    // CTRL_REG3 (Date Ready on DRDY/INT2) enabled
    spi_write_byte(0x22, 0x08);

     // CTRL_REG4 (Full scale enabled) 2000 dps
    spi_write_byte(0x23, 0x30);

    // CTRL_REG5 ()
    spi_write_byte(0x24, 0x00);

}



uint16_t read_gyro_x(){
    int16_t x = 0x0000;
    uint8_t x_H = 0x00;
    uint8_t x_L = 0x00;

    //Read data
    x_L = spi_read_byte(0xA8);
    x_H = spi_read_byte(0xA9);

    // Return 16bit value
    x = x_H << 8;
    x = x | x_L;
}

uint16_t read_gyro_y(){
    int16_t y = 0x0000;
    uint8_t y_H = 0x00;
    uint8_t y_L = 0x00;

    //Read data
    y_L = spi_read_byte(0xAA);
    y_H = spi_read_byte(0xAB);

    // Return 16bit value
    y = y_H << 8;
    y = y | y_L;

}

int16_t read_gyro_z(){
    int16_t z = 0x0000;
    uint8_t z_H = 0x00;
    uint8_t z_L = 0x00;

    //Read data
    z_L = spi_read_byte(0xAC);
    z_H = spi_read_byte(0xAD);


    // Return 16bit value
    z = z_H << 8;
    z = z | z_L;

    return z;
}

int8_t read_temp(){
    int8_t temp = 0x00;


    //Read data
    temp = spi_read_byte(0xA6);

    return temp;
}



