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
// #include "node_setup.h"

// CMD { enables user to call commands (functions with no arguments).
#include "cmd.h"        // cmd_setup();
#include "cmd_board.h"  // cmd_board_setup();
#include "cmd_rgb.h"    // cmd_rgb_setup();
// } CMD

// PUT { enables user to put a value to a particular path
#include "put.h"
#include "put_do.h"
// } PUT

#include "sc_remote.h"
// } Personal Libraries -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------
//SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 

SYSTEM_MODE(SEMI_AUTOMATIC); // Does not connect to cloud automatically.
// STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.
// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

std::vector<char> s0;
std::vector<char> s1;

// } VARIABLES          -------------------------------------------------------

// { USER FUNCTIONS     -------------------------------------------------------
void per_2seconds();
// } USER FUNCTIONS     -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

Timer timer_2sec(2000, per_2seconds);

// } CLASS INSTANCES    -------------------------------------------------------

// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    pinMode(DAC, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

    Serial.begin(9600);
    Serial1.begin(9600);

    if(Particle.connected() == false){
        Particle.connect();
    }

    cmd_setup(); // Adds the "do" function and cmds variable
    // Subscribe to general events
    cmd_board_setup();
    cmd_rgb_setup();
    // Done with setup
    cmd_update(); // updates the "cmds" variable.

    put_setup();
    node_set(3, "rgb");
    add_put(3, put_rgb);
    put_do_setup(4);

    SCR::setup();
    SCR::variable_sc_remote();

    timer_2sec.start();
}

// This routine gets called repeatedly, like once every 5-15 milliseconds.
// Spark firmware interleaves background CPU activity associated with WiFi + Cloud activity with your code. 
// Make sure none of your code delays or blocks for too long (like more than 5 seconds), or weird things can happen.
void loop(){
    SCR::loop();
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

    // publish to dweet.io

    // publish to thinkspeak

    interrupts();
}
