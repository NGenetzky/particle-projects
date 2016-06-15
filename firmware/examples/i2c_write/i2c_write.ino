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

// CMD { enables user to call commands (functions with no arguments).
#include "cmd.h"        // cmd_setup();
#include "cmd_board.h"  // cmd_board_setup();
#include "cmd_rgb.h"    // cmd_rgb_setup();
#include "cmd_i2c.h"    // cmd_i2c_setup();
// } CMD

// PUT { enables user to put a value to a particular path
#include "put.h"        // put_setup();
#include "put_rgb.h"        // put_rgb_setup();
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

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

// } CLASS INSTANCES    -------------------------------------------------------

// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

    wreg_setup();
    setup_nodes();
    setup_exposed_cmds();
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
        
    }
}

// Special function that will be called when serial data is recieved.
void serialEvent1(){ 
    auto char_avilable = Serial1.available();
    
    for(auto i=0; i< char_avilable; i++){

    }
}
// } SPECIAL FUNCTIONS  -------------------------------------------------------

int info_echo(const char *msg){
    info("echo", msg);
    return 0;
}

int i2c_write(const char *s){
    Wire.beginTransmission(0x06);
    Wire.write(String(s));
    return Wire.endTransmission();
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
    node_set(0, "ndef");
    add_put(0, std_err);
    add_post(0, std_err);
    
    node_set(1, "wreg");
    add_put(1, wreg_set);
    add_post(1, wreg_set);
    
    setup_put_rgb(); // Add put "rgb" at 2.
    
    // Post
    post_setup();
    bool success = Particle.subscribe("@d", post_handler, MY_DEVICES); // Requires --private flag.
    if( !success ){ error(1000); }
    
    node_set(3, "@d/i2c");
    add_post(3, i2c_write);
    
    node_set(4, "@d/pub");
    add_post(4, std_out);
    
    node_set(5, "i2c");
    add_put(5, i2c_write);
}
