/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f30x_conf.h"


#ifndef _ANSI_H_
#define _ANSI_H_

#define ESC 0x1B

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void goleft(int steps);
void gotoxy(int x, int y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
void window(uint8_t x1,uint8_t x2,uint8_t y1,uint8_t y2); // , char title[10], uint8_t style

#endif /* _ANSI_H */
