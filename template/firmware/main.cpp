// STL includes
// { Standard Includes  -------------------------------------------------------
#include <vector>

// } STL  ---------------------------------------------------------------------

// { Public Library includes

#include "application.h" // Required for Particle.

// #include "Base64.h" // Decodes and encodes base64 strings


// } Public Library includes

// { Personal Libraries -------------------------------------------------------
#include "global.h"


// Provides access to functionality that is built into the board.
// #include "board.h"

// Provide functions to set the color of the RGB on the photon and core.
// #include "rgb.h"

// Functions to use I2C utility functions.
// #include "i2c_utility.h"

// } Personal Libraries -------------------------------------------------------

// { User functions     -------------------------------------------------------

// Describe these two functions here or declare extern.
// void info(const char * name, const char * data);
// void error(int error_id);
// Expect another file to provide these two methods:


// int PF_function(String args);

// } User functions     -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------
//SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 

SYSTEM_MODE(SEMI_AUTOMATIC); // Does not connect to cloud automatically.
// STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.
// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

char data[MAX_VARIABLE_LENGTH];

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

// } CLASS INSTANCES    -------------------------------------------------------

#define USE_SERIAL0
#define USE_SERIAL1
#define USE_TIMER_2SEC
#define USE_LOGGER


#ifdef USE_SERIAL0
    void serialEvent(); // Special function in Particle.
    std::vector<char> s0; // Vector to hold data collected from serial.
#endif // USE_SERIAL0

#ifdef USE_SERIAL1
    void serialEvent1(); // Special function in Particle.
    std::vector<char> s1; // Vector to hold data collected from serial.
#endif // USE_SERIAL0

#ifdef USE_TIMER_2SEC
    void per_2seconds();// A timer is used to run this every 2 sec
    Timer timer_2sec(2000, per_2seconds);
#endif // USE_TIMER_2SEC

#ifdef USE_LOGGER
    // Provides functions that inform the user. Such as:
        // error(int)
        // info(const char*,const char*)
    #include "logger.h"
#else
    extern void info(const char * name, const char * data);
    extern void error(int error_id);
#endif


// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    // pinMode(DAC, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

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
    
    #ifdef USE_TIMER_2SEC
        timer_2sec.start();
    #endif // USE_TIMER_2SEC
}

// This routine gets called repeatedly, like once every 5-15 milliseconds.
// Spark firmware interleaves background CPU activity associated with WiFi + Cloud activity with your code. 
// Make sure none of your code delays or blocks for too long (like more than 5 seconds), or weird things can happen.
void loop(){

}

// } SPECIAL FUNCTIONS  -------------------------------------------------------

// PF Particle Functions
// int PF_function(String args){
//     if(args.equals("led_on")){
//         return led_on();
//     } else if(args.equals("led_off")) {
//         return led_off();
//     }
// }

// TEMPLATE FUNCTIONS  { -------------------------------------------------------

#ifdef USE_SERIAL0
// Special function that will be called when serial data is recieved.
void serialEvent(){
    auto char_avilable = Serial.available();

    for(auto i=0; i< char_avilable; i++){
        s0.push_back(Serial.read());
    }
}
#endif // USE_SERIAL0

#ifdef USE_SERIAL1
// Special function that will be called when serial data is recieved.
void serialEvent1(){ 
    auto char_avilable = Serial1.available();

    for(auto i=0; i< char_avilable; i++){
        s1.push_back(Serial1.read());
    }
}
#endif // USE_SERIAL1

#ifdef USE_TIMER_2SEC
void per_2seconds(){
    noInterrupts(); // Don't interrupt me during a timer interrupt.

    interrupts();
}
#endif // USE_TIMER_2SEC

// } TEMPLATE FUNCTIONS  -------------------------------------------------------