// STL includes
// { Standard Includes  -------------------------------------------------------
#include <vector>

// } STL  ---------------------------------------------------------------------

// { Public Library includes

// Required for Particle.
#include "application.h"

// Decodes and encodes base64 strings
// #include "Base64.h"

// } Public Library includes

// { Personal Libraries -------------------------------------------------------
#include "global.h"

// Provides access to functionality that is built into the board.
#include "board.h"

// Provide functions to set the color of the RGB on the photon and core.
#include "rgb.h"

// Provides info(const char*,const char*) and error(int) funtions
#include "logger.h"

// CMD { enables user to call commands (functions with no arguments).
#include "cmd.h"        // cmd_setup();
#include "cmd_board.h"  // cmd_board_setup();
// } CMD

// PUT { enables user to put a value to a particular path
#include "put.h"
#include "put_do.h"
// } PUT


// } Personal Libraries -------------------------------------------------------

// { User functions     -------------------------------------------------------

void per_2seconds();// A timer is used to run this every 2 sec

// int PF_function(String args);
int PF_set_charge_rate(String args);
int PF_send_pgn(String args);
void microgrid_setup();

// } User functions     -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------
//SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 

SYSTEM_MODE(SEMI_AUTOMATIC); // Does not connect to cloud automatically.
// STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.
// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

std::vector<char> s0;
std::vector<char> s1;
char PV_data[MAX_VARIABLE_LENGTH];
char PV_status[MAX_VARIABLE_LENGTH];
char PV_soc[10]; // state of charge as percentage
char PV_gen_schedule[MAX_VARIABLE_LENGTH]; // generator schedule
char PV_inv_schedule[MAX_VARIABLE_LENGTH]; // inverter/charger schedule

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

Timer timer_2sec(2000, per_2seconds);

// } CLASS INSTANCES    -------------------------------------------------------

// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    pinMode(DAC, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

    Serial.begin(9600);
    Serial1.begin(9600);

    // SEMI_AUTOMATIC
    if(Particle.connected() == false){
        Particle.connect();
    }

    // Particle.function("function", PF_function);
    Particle.variable("data", PV_data);

    cmd_setup(); // Adds the "do" function and cmds variable
    // Subscribe to general events
    cmd_board_setup();
    // Done with setup
    cmd_update(); // updates the "cmds" variable.

    put_setup();
    node_set(3, "rgb");
    add_put(3, put_rgb);
    put_do_setup(4);

    microgrid_setup();
    cmd_update(); // updates the "cmds" variable.

    timer_2sec.start();

    strcpy(PV_data, "Hello World");
    timer_2sec.start();
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
    noInterrupts(); // Don't interrupt me during a timer interrupt.

    interrupts();
}


void microgrid_setup(){
    // Variables
    Particle.variable("status", PV_status);
    strcpy(PV_status, "98%,GEN_ON,INV_ON");

    Particle.variable("soc", PV_soc); // state of charge as percentage
    strcpy(PV_soc, "98%");

    Particle.variable("battery_bank", PV_data); // Other variables on battery bank
    // strcpy(PV_data, "{soc:98%}");

    Particle.variable("gen_schedule", PV_gen_schedule); // generator schedule
    strcpy(PV_gen_schedule, "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");

    Particle.variable("inv_schedule", PV_inv_schedule); // inverter/charger schedule
    strcpy(PV_inv_schedule, "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");

    // Functions
    Particle.function("charge_rate", PF_set_charge_rate);
    Particle.function("send_pgn", PF_send_pgn);


    // cmds and nodes
    auto i = 100;
    cmd_set(i++, "gen_on", led_on);
    cmd_set(i++, "gen_off", led_off);
    cmd_set(i++, "gen_auto", led_off);

    cmd_set(i++, "inv_source", led_on);
    cmd_set(i++, "inv_absorb", led_off);
    cmd_set(i++, "inv_auto", led_off);
}



// PF Particle Functions
// int PF_function(String args){
//     if(args.equals("led_on")){
//         return led_on();
//     } else if(args.equals("led_off")) {
//         return led_off();
//     }
// }
int PF_set_charge_rate(String args){
    return -1;
}
int PF_send_pgn(String args){
    return -1;
}
