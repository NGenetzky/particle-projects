// STL includes
// { Standard Includes  -------------------------------------------------------
#include <vector>

// } STL  ---------------------------------------------------------------------
// Public Library includes

// { Personal Libraries -------------------------------------------------------
#include "global.h"

// Provides access to functionality that is built into the board.
#include "board.h"

// Provide functions to set the color of the RGB on the photon and core.
#include "rgb.h"

// Provides info(const char*,const char*) and error(int) funtions
#include "logger.h"

#include "node.h"
#include "node_var.h"

// CMD { enables user to call commands (functions with no arguments).
#include "cmd.h"        // cmd_setup();
#include "cmd_board.h"  // cmd_board_setup();
#include "cmd_rgb.h"    // cmd_rgb_setup();
// } CMD

// PUT { enables user to put a value to a particular path
#include "put.h"
#include "put_rgb.h"
#include "put_do.h"
#include "put_lcd.h"
// } PUT

// } Personal Libraries -------------------------------------------------------

// { User functions     -------------------------------------------------------

// A timer is used to run this every 2 sec
void per_2seconds();

// Specific to lcd
void lcd_setup(unsigned i2c_address=39);
int lcd_print_upto60(String args);
void lcd_print_time(int r, int c); // specify row and column

// } User functions     -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------
//SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 

SYSTEM_MODE(SEMI_AUTOMATIC); // Does not connect to cloud automatically.
// STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.
// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

std::vector<char> s0;
std::vector<char> s1;

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

Timer timer_2sec(2000, per_2seconds);
LiquidCrystal_I2C *lcd;

// } CLASS INSTANCES    -------------------------------------------------------

// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

    Serial.begin(9600);
    Serial1.begin(9600);

    // SEMI_AUTOMATIC
    if(Particle.connected() == false){
        Particle.connect();
    }

    lcd_setup(39);
    Particle.function("lcd", lcd_print_upto60);

    cmd_setup(); // Adds the "do" function and cmds variable
    // CMD {
    // Subscribe to general events
    cmd_board_setup();
    cmd_rgb_setup();
    // CMD }
    cmd_update(); // updates the "cmds" variable.

    put_setup();
    // PUT {
    put_rgb_setup(2); // 1
    put_do_setup(4); // 1
    put_lcd_setup(5, lcd); // 2
    // PUT }

    node_var_setup(); // exposes "nodes" variable

    timer_2sec.start();
}

// This routine gets called repeatedly, like once every 5-15 milliseconds.
// Spark firmware interleaves background CPU activity associated with WiFi + Cloud activity with your code. 
// Make sure none of your code delays or blocks for too long (like more than 5 seconds), or weird things can happen.
void loop(){
    // lcd is updated with timer.

}

// Special function that will be called when serial data is recieved.
void serialEvent(){
    auto char_avilable = Serial.available();
    
    for(auto i=0; i< char_avilable; i++){
        s0.push_back(Serial.read());       
    }
}

// Special function that will be called when serial data is recieved.
void serialEvent1(){ 
    auto char_avilable = Serial1.available();
    
    for(auto i=0; i< char_avilable; i++){
        s1.push_back(Serial1.read());       
    }
}
// } SPECIAL FUNCTIONS  -------------------------------------------------------

void per_2seconds(){
    noInterrupts(); // Don't interrupt me during a timer interrupt.

    interrupts();
}


// Defines "lcd"
void lcd_setup(unsigned i2c_address){
    lcd = new LiquidCrystal_I2C(i2c_address, 20, 4);
    lcd->init();
    lcd->backlight();
    lcd->clear();
}

// Requires "lcd" to be defined.
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

// Requires "lcd" to be defined.
void lcd_print_time(int r, int c){ // specify row and column
    lcd->setCursor(r,c);
    lcd->print(Time.hour() < 10? "0" : "");
    lcd->print(Time.hour());
    lcd->print(Time.minute() < 10? ":0": ":");
    lcd->print(Time.minute());
    lcd->print(Time.second() < 10? ":0": ":");
    lcd->print(Time.second());
}
