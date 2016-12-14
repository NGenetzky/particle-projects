
// main.cpp // Template for main.cpp for Particle devices

// Set HELP at compile time with information useful for the end user.
const char * HELP = "template:" \
    " This is just a template";

// { Configuration  -----------------------------------------------------------
#define USE_SERIAL0
#define USE_SERIAL1
// #define USE_LCD
#define USE_TIMER_2SEC
// } Configuration  -----------------------------------------------------------

// { Standard Includes  -------------------------------------------------------
#include "application.h" // Required for Particle.
#include <vector>
// } Standard Includes  -------------------------------------------------------

// { Public Library includes
// #include "Base64.h" // Decodes and encodes base64 strings
// } Public Library includes

// { Personal Libraries -------------------------------------------------------

// Defines constants for Particle Ecosystem.
#include "global.h"

// Provides access to functionality that is built into the board.
#include "board.h"

// Provide functions to set the color of the RGB on the photon and core.
// #include "rgb.h"

// Functions to use I2C utility functions.
// #include "i2c_utility.h"

// Many libraries expect the following functions to be defined:
    // error(int)
    // info(const char*,const char*)
// Use logger to define these functions.
#include "logger.h"

#ifdef USE_LCD
#include "LiquidCrystal_I2C_Spark.h"
#endif // USE_LCD

// } Personal Libraries -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------

SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 
// SYSTEM_MODE(SEMI_AUTOMATIC); // Requires manual "connect()"
// SYSTEM_MODE(MANUAL); // Requires

// then we can conditionally disable wifi or cloud.
// Functions are defined in "board.h"
// STARTUP(disable_wifi_ifD6()); // Connects to cloud if D6 is HIGH.
// STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.

// } SYSTEM_SETUP       -------------------------------------------------------

// { User functions     -------------------------------------------------------

int PF_do(String args);
int PF_do_int(long int arg);


#ifdef USE_SERIAL0
// Special function in Particle. Called when data is recieved on Serial0.
void serialEvent();
#endif // USE_SERIAL0

#ifdef USE_SERIAL1
// Special function in Particle. Called when data is recieved on Serial1.
void serialEvent1();
#endif // USE_SERIAL0

#ifdef USE_TIMER_2SEC
void per_2seconds();// A timer is used to run this every 2 sec
#endif // USE_TIMER_2SEC

// } User functions     -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

char PV_a[MAX_VARIABLE_LENGTH];






#ifdef USE_SERIAL0
std::vector<char> s0; // Vector to hold data collected from serial.
#endif // USE_SERIAL0

#ifdef USE_SERIAL1
std::vector<char> s1; // Vector to hold data collected from serial.
#endif // USE_SERIAL0

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

#ifdef USE_LCD
// Connects to 20x4 LCD at I2C address 62.
LiquidCrystal_I2C lcd(62, 20, 4);
#endif // USE_LCD

#ifdef USE_TIMER_2SEC
Timer timer_2sec(2000, per_2seconds); // 2000ms
#endif // USE_TIMER_2SEC

// } CLASS INSTANCES    -------------------------------------------------------

// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    // Required if SYSTEM_MODE = SEMI_AUTOMATIC or MANUAL
    // if(Particle.connected() == false){
    //     Particle.connect();
    // }
    
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    // pinMode(DAC, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

    #ifdef USE_SERIAL0
    Serial.begin(9600);
    #endif // USE_SERIAL0
    #ifdef USE_SERIAL1
    Serial1.begin(9600);
    #endif // USE_SERIAL1

    // Up to 20 Variables
    Particle.variable("help", HELP);
    Particle.variable("a", PV_a);
    
    // Up to 15 Functions. 
    Particle.function("do", PF_do);
    

    strcpy(PV_a, "Hello World");
    
    
    #ifdef USE_TIMER_2SEC
    timer_2sec.start();
    #endif // USE_TIMER_2SEC
}

// This routine gets called repeatedly, like once every 5-15 milliseconds.
// Spark firmware interleaves background CPU activity associated with WiFi + Cloud activity with your code. 
// Make sure none of your code delays or blocks for too long (like more than 5 seconds), or weird things can happen.
void loop(){
    
    
    // Required if SYSTEM_MODE = MANUAL
    // Particle.process();
}

// } SPECIAL FUNCTIONS  -------------------------------------------------------

int PF_do(String args){
    auto intarg = args.toInt();
    if(intarg!=0){
        return PF_do_int(intarg);
    }
    
    if(args.equals("led_on")){
        return led_on();
    } else if(args.equals("led_off")) {
        return led_off();
    } else {
        // Did not match any known instructions
        return -1; // Return a error.
    }
}

int PF_do_int(long int arg){
    switch(arg){
        case 0:
            return led_off();
            break;
        case 1:
            return led_on();
            break;
        default:
            return -1;
    }
}

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