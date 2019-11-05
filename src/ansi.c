#include "ansi.h"
#define ESC 0x1B


void clrscr(){
// Clears screen
    printf("%c[2J",ESC);
}


void gotoxy(int x, int y){
// Go to coordinates (x,y)
    printf("%c[%d;%dH",ESC,y,x);
}

