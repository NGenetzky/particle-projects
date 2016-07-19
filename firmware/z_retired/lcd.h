#ifndef LCD_H
#define LCD_H

#include "application.h"

extern void error(int err_code);

void lcd_setup(unsigned i2c_address=39);
void lcd_update();
int lcd_print_upto60(String args);
void lcd_print_time(int r, int c);

#endif // LCD_H
