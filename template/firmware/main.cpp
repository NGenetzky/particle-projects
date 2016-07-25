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
// #include "board/board.h"

// Provide functions to set the color of the RGB on the photon and core.
// #include "rgb.h"

// Provides info(const char*,const char*) and error(int) funtions
// #include "logger.h"

// } Personal Libraries -------------------------------------------------------

// { User functions     -------------------------------------------------------

void per_2seconds();// A timer is used to run this every 2 sec

// int PF_function(String args);

// } User functions     -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------
//SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 

SYSTEM_MODE(SEMI_AUTOMATIC); // Does not connect to cloud automatically.
// STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.
// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

std::vector<char> s0;
std::vector<char> s1;
char data[MAX_VARIABLE_LENGTH];

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

Timer timer_2sec(2000, per_2seconds);

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

    // Particle.function("function", PF_function);
    // Particle.function("data", set_data);
    Particle.variable("data", data);

    strcpy(data, "Hello World");
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

// PF Particle Functions
// int PF_function(String args){
//     if(args.equals("led_on")){
//         return led_on();
//     } else if(args.equals("led_off")) {
//         return led_off();
//     }
// }

