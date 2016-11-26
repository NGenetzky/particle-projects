// STL includes
// { Standard Includes  -------------------------------------------------------
#include <vector>

// } STL  ---------------------------------------------------------------------

// { Public Library includes

#include "application.h" // Required for Particle.

// #include "Base64.h" // Decodes and encodes base64 strings

// Access to MCP23017 I2C IO Exapander
#include "Adafruit_MCP23017.h"

// } Public Library includes

// { Personal Libraries -------------------------------------------------------
#include "global.h"

// Provides functions that inform the user. Such as:
    // error(int)
    // info(const char*,const char*)
#include "logger.h"

// Provides access to functionality that is built into the board.
// #include "board.h"

// Provide functions to set the color of the RGB on the photon and core.
// #include "rgb.h"

// Functions to use I2C utility functions.
// #include "i2c_utility.h"

// } Personal Libraries -------------------------------------------------------

// { User functions     -------------------------------------------------------

// void info(const char * name, const char * data);
// void error(int error_id);
// Expect another file to provide these two methods:
extern void info(const char * name, const char * data);
extern void error(int error_id);

void per_2seconds();// A timer is used to run this every 2 sec

void mirror_on_D7_setup(unsigned pin_num);
void mirror_on_D7_loop();

// int PF_function(String args);
int PF_mcp_read(String args);
int PF_mcp_write(String args);
int PF_mirror_on_D7(String args);

// } User functions     -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------
//SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 

SYSTEM_MODE(SEMI_AUTOMATIC); // Does not connect to cloud automatically.
// STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.
// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

uint8_t mirror_on_D7_pin = 255; // 255 is too large to be valid pin.
// std::vector<char> s0;
// std::vector<char> s1;
char data[MAX_VARIABLE_LENGTH];
unsigned counter = 0;

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

Timer timer_2sec(2000, per_2seconds);
Adafruit_MCP23017 mcp;

// } CLASS INSTANCES    -------------------------------------------------------

// { SPECIAL FUNCTIONS  -------------------------------------------------------
// Describe these two functions here or declare extern.

void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    // pinMode(DAC, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT

    Serial.begin(9600);
    Serial1.begin(9600);

    // SEMI_AUTOMATIC
    if(Particle.connected() == false){
        Particle.connect();
    }

    mcp.begin(1);
    for (unsigned i = 0;  i<=13; i++){
        mcp.pinMode(i, OUTPUT);
    }

    // Provide functions and variables to end user.
    Particle.function("mcp_read", PF_mcp_read);
    Particle.function("mcp_write", PF_mcp_write);
    Particle.function("mirror", PF_mirror_on_D7);
    Particle.variable("data", data);

    strcpy(data, "Hello World");
    timer_2sec.start();
}

// This routine gets called repeatedly, like once every 5-15 milliseconds.
// Spark firmware interleaves background CPU activity associated with WiFi + Cloud activity with your code. 
// Make sure none of your code delays or blocks for too long (like more than 5 seconds), or weird things can happen.
void loop(){

    for (unsigned i = 0;  i<=65536-1; i++){
        mcp.writeGPIOAB(i);
        delay(500);
    }
}

// Special function that will be called when serial data is recieved.
void serialEvent(){
    // auto char_avilable = Serial.available();

    // for(auto i=0; i< char_avilable; i++){
    //     s0.push_back(Serial.read());
    // }
}

// Special function that will be called when serial data is recieved.
void serialEvent1(){ 
    // auto char_avilable = Serial1.available();

    // for(auto i=0; i< char_avilable; i++){
    //     s1.push_back(Serial1.read());
    // }
}
// } SPECIAL FUNCTIONS  -------------------------------------------------------

void per_2seconds(){
    noInterrupts(); // Don't interrupt me during a timer interrupt.

    interrupts();
}

int PF_mcp_read(String args){
    auto i_address = args.indexOf("@");
    if(i_address == -1){
        return mcp.readGPIOAB();
    } else {
        auto addr = args.substring(i_address+1).toInt();
        return mcp.readRegister(addr);
    }
};

int PF_mcp_write(String args){
    auto i_address = args.indexOf("@");
    auto i_value = args.indexOf("=");
    if(i_value == -1){
        error(158);
    }
    auto value = args.substring(i_value+1).toInt();
    if(i_address == -1){
        mcp.writeGPIOAB(value);
    } else {
        auto addr = args.substring(i_address+1).toInt();
        mcp.writeRegister(addr, value);
    }
    return 0;
};

int PF_mirror_on_D7(String args){
    // Ensure conversion worked.
    uint8_t pin_num = args.toInt();
    if(pin_num == 0){
        if(!args.startsWith("0")){
            error(193);
        }
    }
    mirror_on_D7_setup(pin_num);
    return 0;
}

void mirror_on_D7_setup(unsigned pin_num){
    // Ensure its a valid pin.
    mirror_on_D7_pin = pin_num;
    mcp.pinMode(mirror_on_D7_pin, INPUT);
    mcp.pullUp(mirror_on_D7_pin, HIGH);  // turn on a 100K pullup internally
}

void mirror_on_D7_loop(){
    if(mirror_on_D7_pin != 255){
        digitalWrite(BOARD_LED, mcp.digitalRead(mirror_on_D7_pin));
    }
}



// PF Particle Functions
// int PF_function(String args){
//     if(args.equals("led_on")){
//         return led_on();
//     } else if(args.equals("led_off")) {
//         return led_off();
//     }
// }

