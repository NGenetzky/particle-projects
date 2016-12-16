
// main.cpp // Template for main.cpp for Particle devices

// Set HELP at compile time with information useful for the end user.
const char * HELP = "template:" \
    " This is just a template";

// { Configuration  -----------------------------------------------------------
#define USE_SERIAL0
#define USE_SERIAL1
#define USE_TIMER_2SEC
#define USE_LCD
#define USE_TIMER_2SEC
#define USE_THINGSPEAK
#define USE_STDIN
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

#ifdef USE_THINGSPEAK
#include "thingspeak_publish.h"
#endif // USE_THINGSPEAK

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

// { User Datatypes     -------------------------------------------------------

union Int4Bytes {
    uint32_t i;
    struct {
        uint8_t b0;
        uint8_t b1;
        uint8_t b2;
        uint8_t b3;
    };
    uint8_t b[4];
};

// } User Datatypes     -------------------------------------------------------

// { User functions     -------------------------------------------------------

int PF_do(String args);
int PF_do_int(long int arg);
int PF_set(String args);
void PS_handler(const char *event, const char *data);

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

#ifdef USE_STDIN
int PF_stdin(String args);
#endif // USE_STDIN

#ifdef USE_THINGSPEAK
void thingspeak();
#endif // USE_THINGSPEAK

// } User functions     -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

char PV_a[MAX_VARIABLE_LENGTH];
char PV_b[MAX_VARIABLE_LENGTH];
char PV_c[MAX_VARIABLE_LENGTH];
std::vector<char> stdout_v; // Vector for data leaving device.

#ifdef USE_SERIAL0
std::vector<char> s0; // Vector to hold data collected from serial.
#endif // USE_SERIAL0

#ifdef USE_SERIAL1
std::vector<char> s1; // Vector to hold data collected from serial.
#endif // USE_SERIAL0

#ifdef USE_STDIN
std::vector<char> stdin_v; // Vector for data coming into device.
#endif // USE_SERIAL0

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

#ifdef USE_TIMER_2SEC
Timer timer_2sec(2000, per_2seconds); // 2000ms
#endif // USE_TIMER_2SEC

#ifdef USE_LCD
// Connects to 20x4 LCD at I2C address 62.
LiquidCrystal_I2C lcd(62, 20, 4);
#endif // USE_LCD

// } CLASS INSTANCES    -------------------------------------------------------

// { SPECIAL FUNCTIONS  -------------------------------------------------------
void setup(){
    // Required if SYSTEM_MODE = SEMI_AUTOMATIC or MANUAL
    // if(Particle.connected() == false){
    //     Particle.connect();
    // }
    
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    // pinMode(DAC, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    
    // pinMode( D6, INPUT );
    // attachInterrupt( D6, on_d6, CHANGE, 13);
    
    // Note: do not set the pinMode() with analogRead(). The pinMode() is
    // automatically set to AN_INPUT the first time analogRead() is called
    // src: https://docs.particle.io/reference/firmware/photon/#analogread-adc-
    // In other words, don't do: pinMode(analog_pin, INPUT);

    // { Declare Cloud Variables/Functions/Events  ----------------------------
    // Up to 20 Variables
    Particle.variable("help", HELP);
    Particle.variable("a", PV_a);
    Particle.variable("b", PV_a);
    Particle.variable("c", PV_a);
    
    // Up to 15 Functions. 
    Particle.function("do", PF_do);
    Particle.function("set", PF_set);
    
    #ifdef USE_STDIN
    Particle.function("stdin", PF_stdin);
    #endif // USE_STDIN
    
    // Up to 4 Event Subscriptions
    Particle.subscribe("all", PS_handler, MY_DEVICES);
    
    // For documentation specify what events you will publish:
    // Particle.publish("stdout", "...")
    // Particle.publish("stderr", "...")
    
    // } Declare Cloud Variables/Functions/Events  ----------------------------

    strcpy(PV_a, "Hello World");
    
    
    #ifdef USE_SERIAL0
    Serial.begin(9600);
    #endif // USE_SERIAL0
    #ifdef USE_SERIAL1
    Serial1.begin(9600);
    #endif // USE_SERIAL1

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

int PF_set(String args){
    auto sep = args.indexOf("=");
    if(sep == -1){ error(-1000); return -1000;}
    auto k = args.substring(0,sep);
    auto v = args.substring(sep+1);
    
    char *dest = PV_a;
    switch(k.charAt(0)){
        case 'a':
            dest = PV_a;
            break;
        case 'b':
            dest = PV_b;
            break;
        case 'c':
            dest = PV_c;
            break;
        default:
            return -1;
    }
    
    v.toCharArray(dest, MAX_ARG_LENGTH);
    return v.length();
}

void PS_handler(const char *event, const char *data){
    
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
    
    bool done = false; // Only do 1 thing per 2 seconds.
    done = (digitalRead(D2) == HIGH); // Disable if D2 is LOW
    
    #ifdef USE_STDIN
    if(( ! done ) && (stdin_v.size()!=0)){
        // copy to stdout.
        stdout_v.insert(std::end(stdout_v),
            std::begin(stdin_v), std::end(stdin_v));
        stdin_v.clear();
        done = true;
    }
    #endif // USE_STDIN
    
    if(( ! done ) && (stdout_v.size()!=0)){
        Particle.publish("stdout", stdout_v.data());
        stdout_v.clear();
        done = true;
    }

    #ifdef USE_THINGSPEAK
    if( ! done ){
        thingspeak();
    }
    #endif // USE_THINGSPEAK
    
    interrupts();
}
#endif // USE_TIMER_2SEC

#ifdef USE_STDIN
int PF_stdin(String args){ 
    auto char_avilable = args.length(); 
    for(int i=0; i< char_avilable; i++){
        stdin_v.push_back(args.charAt(i));
    }
    return stdin_v.size();
}
#endif // USE_STDIN

#ifdef USE_THINGSPEAK
void thingspeak(){
    thingspeak_publish(
        millis(), 
        analogRead(A0),
        analogRead(A1),
        analogRead(A2),
        analogRead(A3)
        );
}
#endif // USE_THINGSPEAK