// STL includes
#include <vector>

// Public Library includes

// { Personal Libraries -------------------------------------------------------
#include "global.h"

// Provides access to functionality that is built into the board.
#include "board.h"

// Provide functions to set the color of the RGB on the photon and core.
#include "rgb.h"

// Provides info(const char*,const char*) and error(int) funtions
#include "logger.h"

// Provides a character buffer that can be used by other applications,
// inserted in by the user, or can be manipulated.
#include "wreg.h"

#include "node.h"
#include "node_setup.h"

// CMD { enables user to call commands (functions with no arguments).
#include "cmd.h"        // cmd_setup();
#include "cmd_board.h"  // cmd_board_setup();
#include "cmd_rgb.h"    // cmd_rgb_setup();
#include "cmd_i2c.h"    // cmd_i2c_setup();
// } CMD

// PUT { enables user to put a value to a particular path
#include "put.h"
#include "put_rgb.h"
#include "put_serial.h"
#include "put_do.h"
// } PUT

// POST { enables user to post characters to a particular path
#include "post.h"
// } PUT

// } Personal Libraries -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------
// Defaults should be explicit
//SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 

// Change to SEMI_AUTOMATIC mode. Then cloud is disable if D6 is pulled HIGH.
SYSTEM_MODE(SEMI_AUTOMATIC);
STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is high.
// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

std::vector<char> s0;
std::vector<char> s1;

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

Timer timer_2sec(2000, per_2seconds);

// } CLASS INSTANCES    -------------------------------------------------------

// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

    wreg_setup();
    setup_exposed_cmds();
    
    Serial.begin(9600);
    Serial1.begin(9600);
    setup_nodes();
    
    timer_2sec.start();
    
    wreg_set("setup=done");
}

// This routine gets called repeatedly, like once every 5-15 milliseconds.
// Spark firmware interleaves background CPU activity associated with WiFi + Cloud activity with your code. 
// Make sure none of your code delays or blocks for too long (like more than 5 seconds), or weird things can happen.
void loop(){
    
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
    noInterrupts();
    if(s0.size() != 0) {
        s0.push_back('\0');
        // Serial1.print(s0.data());
        // info("serial0", s0.data());
        put_kv_pairs(s0.data());
        s0.clear();
    }
    if(s1.size() != 0) {
        s1.push_back('\0');
        // Serial.print(s1.data());
        // info("serial1", s1.data());
        put_kv_pairs(s1.data());
        s1.clear();
    }
    interrupts();
}

void setup_exposed_cmds(){
    // Subscribe to general events
    cmd_setup(); // Adds the "do" function and cmds variable
    cmd_board_setup();
    cmd_i2c_setup();
    cmd_rgb_setup();
    cmd_update(); // updates the "cmds" variable.
}
    

void setup_nodes(){
    put_setup();
    post_setup();
    
    put_rgb_setup(2); // hardcode 2
    put_serial_setup(3);
    put_do_setup(4);
}
