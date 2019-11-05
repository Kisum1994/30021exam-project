#include "LCD.h"


void lcd_write_string(char *str, uint16_t slice, uint16_t line, char *buffer){
    uint16_t bufnum = slice + 128*line;
    uint8_t i = 0;
    uint8_t j = 0;

        while (str[i] != '\0'){

        for (j = 0; j <=4; j++){
                buffer[bufnum] = character_data[str[i]-32][j];
                bufnum += 1;
            }
            i++;
        }

    return;
    }

void lcd_update(char *buffer){

    char bufferclear[512];
    memset(bufferclear, 0x00, 512);

    lcd_push_buffer(bufferclear);
    lcd_push_buffer(buffer);

    return;
}
