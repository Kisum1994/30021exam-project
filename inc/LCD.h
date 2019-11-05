#include <stdint.h>
#include <stdio.h>
#include "charset.h"
#include "30021_io.h"

#ifndef _LCD_H_
#define _LCD_H_


void lcd_write_string(char *str, uint16_t slice, uint16_t line, char *buffer);
void lcd_update(char *buffer);


#endif
