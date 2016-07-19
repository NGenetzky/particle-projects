#include "lcd.h"
#include "application.h"

#include "LiquidCrystal_I2C_Spark.h"

LiquidCrystal_I2C *lcd;


// {{ Declare a timer
#if defined (STM32F10X_MD) // Core hardware specific code.
// Particle Core does not support any code utilizing Software Timers.
#include "SparkIntervalTimer.h"
IntervalTimer lcd_timer;
#endif
// TODO: Should be for photon or electron
#if defined (STM32F2XX) // Photon hardware specific code.
Timer lcd_timer(1000, lcd_update); //(period, callback, one_shot)
#endif
// Declare a timer }}

void lcd_setup(unsigned i2c_address){
    Particle.function("lcd", lcd_print_upto60);

    lcd = new LiquidCrystal_I2C(i2c_address, 20, 4);
    lcd->init();
    lcd->backlight();
    lcd->clear();
    // Print header. Begining is later overwritten by clock
    lcd->print("00:00:00       lcd>>");


    // {{ Start the timer
    #if defined (STM32F10X_MD) // Core hardware specific code.
    // Particle Core does not support any code utilizing Software Timers.
    lcd_timer.begin(lcd_update, 2*1000, hmSec); // hmSec= Half Milisecond
    #endif

    #if defined (STM32F2XX) // Photon hardware specific code.
    lcd_timer.start();
    #endif
    // Start the timer }}
}

void lcd_update(){
    lcd_print_time(0,0);
}

int lcd_print_upto60(String args){
    int len = args.length();
    if( 3*20 < len){
        len=3*20;
    }
    for(auto i=0; i<3*20; ++i){
        if(i==0){
            lcd->setCursor(0,1);
        } else if(i==20) {
            lcd->setCursor(0,2);
        } else if(i==40){
            lcd->setCursor(0,3);
        }

        if(i<len){
            lcd->print(args.charAt(i));
        } else {
            lcd->print(' '); // Clear unused spaces.
        }
    }
    return 0;
}

void lcd_print_time(int r, int c){ // specify row and column
    lcd->setCursor(r,c);
    lcd->print(Time.hour() < 10? "0" : "");
    lcd->print(Time.hour());
    lcd->print(Time.minute() < 10? ":0": ":");
    lcd->print(Time.minute());
    lcd->print(Time.second() < 10? ":0": ":");
    lcd->print(Time.second());
}
