/*
8-Feb-2015
Jim Brower
bulldoglowell@gmail.com
https://github.com/BulldogLowell/LiquidCrystal_I2C_Spark
*/

#include "LiquidCrystal_I2C_Spark.h"

LiquidCrystal_I2C *lcd;

int lastSecond = 0;

void setup(void)
{
  Serial.begin(9600);
  lcd = new LiquidCrystal_I2C(39, 20, 4);
  lcd->init();
  lcd->backlight();
  lcd->clear();
  lcd->print("***Spark Time***");
  
  Time.zone(-5); // Central TZ is (-6) but to account for day light savings (-5).
}

void loop(void)
{
  if (Time.second() != lastSecond)
  {
    Serial.print(Time.timeStr());
    lcd->setCursor(0,1);
    lcd->print(Time.hour() < 10? "   0" : "    ");
    lcd->print(Time.hour());
    lcd->print(Time.minute() < 10? ":0": ":");
    lcd->print(Time.minute());
    lcd->print(Time.second() < 10? ":0": ":");
    lcd->print(Time.second());
    lastSecond = Time.second();
  }
}
