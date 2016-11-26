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

#define USE_AUTOMATIC
// #define USE_SEMI_AUTOMATIC
// #define USE_MANUAL
// #define USE_WIFI_IF
// #define USE_CLOUD_IF

#define USE_SERIAL0
#define USE_SERIAL1
#define USE_TIMER_2SEC
#define USE_LOGGER
// #define USE_CUSTOM_LOGGER

// #define USE_CUSTOM_LOGGER
// { User functions     -------------------------------------------------------

// int PF_function(String args);

// } User functions     -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------

// If SYSTEM_MODE == SEMI_AUTOMATIC
#ifdef USE_SEMI_AUTOMATIC
    SYSTEM_MODE(SEMI_AUTOMATIC); // Does not connect to cloud automatically.
#elif USE_MANUAL
    SYSTEM_MODE(MANUAL); // Default. Not needed, but be explicit. 
#else
    #define USE_AUTOMATIC
    SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 
#endif

#ifndef USE_AUTOMATIC
    // then we can conditionally disable wifi or cloud.
    #ifdef USE_WIFI_IFUSE_WIFI_IF
        #include "board.h"
        STARTUP(disable_wifi_ifD6()); // Connects to cloud if D6 is HIGH.
    #elif defined USE_CLOUD_IF
        #include "board.h"
        STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.
    #endif // USE_CLOUD_IF or USE_WIFI_IF
#endif // NOT USE_AUTOMATIC 

// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

char data[MAX_VARIABLE_LENGTH];

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

// } CLASS INSTANCES    -------------------------------------------------------

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
    // Many libraries expect the following functions to be defined:
        // error(int)
        // info(const char*,const char*)

    // Use logger to define these functions.
    #include "logger.h"
#elif defined USE_CUSTOM_LOGGER
    // Many libraries expect the following functions to be defined:
        // error(int)
        // info(const char*,const char*)

    // Could also define the functions yourself.
    void info(const char * name, const char * data);
    void error(int error_id);
#else
    #error "Must define either USE_LOGGER or USE_CUSTOM_LOGGER"
#endif // USE_LOGGER


// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    #ifndef USE_AUTOMATIC
        // SEMI_AUTOMATIC or MANUAL
        if(Particle.connected() == false){
            Particle.connect();
        }
    #endif
    
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    // pinMode(DAC, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

    #ifdef USE_SERIAL0
        Serial.begin(9600);
    #endif // USE_SERIAL0
    #ifdef USE_SERIAL1
        Serial1.begin(9600);
    #endif // USE_SERIAL1


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
    
    
    #ifdef USE_MANUAL
        Particle.process();
    #endif
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