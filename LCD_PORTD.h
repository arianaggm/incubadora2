#ifndef LCD_PORTD_H
#define LCD_PORTD_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "LCD_commands.h"
#define _XTAL_FREQ 8000000

#define RS LATDbits.LD7 //McLab2
//#define RS PORTEbits.RE2 //PicGenios
#define EN LATDbits.LD6
#define LINE_UP 0
#define LINE_DOWN 1

void iniLCD(void);
void LCDcommand(char a);
void LCDchar(char a);
void LCDprint(int size, char a[], int wait_ms);
void MoveCursor(char x, char y);
void MoveLCD(char dir, char inc);
void GenChar(char a[8]);
void LCDint(int a);

#endif /* LCD_PORTD_H */
