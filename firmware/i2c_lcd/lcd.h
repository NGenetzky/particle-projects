#ifndef LCD_H
#define LCD_H

#include "application.h"

extern void error(int err_code);

void lcd_setup();
int lcd_cli (int argc, char* argv[]);
void lcd_update();
int lcd_print_upto60(String args);
void lcd_print_time(int r, int c);

#endif // LCD_H