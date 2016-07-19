#pragma once

#include "LiquidCrystal_I2C_Spark.h"

int put_lcd_setup(unsigned int start, LiquidCrystal_I2C *lcd);
int put_cursor(const char *s);
int put_lcd(const char *s);
