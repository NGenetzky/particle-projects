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
#include "logger.h"

#include "can.h"

// } Personal Libraries -------------------------------------------------------

// { User functions     -------------------------------------------------------

void per_2seconds();// A timer is used to run this every 2 sec
void can_on_receive();

int PF_can(String args);
int PF_set_id(String args);
void can_transmit_test();

// } User functions     -------------------------------------------------------

// SYSTEM_SETUP {       -------------------------------------------------------
//SYSTEM_MODE(AUTOMATIC); // Default. Not needed, but be explicit. 

SYSTEM_MODE(SEMI_AUTOMATIC); // Does not connect to cloud automatically.
// STARTUP(disable_cloud_ifD6()); // Connects to cloud if D6 is HIGH.
// } SYSTEM_SETUP       -------------------------------------------------------

// { VARIABLES          -------------------------------------------------------

std::vector<char> s0;
std::vector<char> s1;
char PV_text[MAX_VARIABLE_LENGTH];
char PV_data[MAX_VARIABLE_LENGTH];

uint32_t can_id=256; // Default destination
char PV_id[10]="256";

// } VARIABLES          -------------------------------------------------------

// { CLASS INSTANCES    -------------------------------------------------------

Timer timer_2sec(2000, per_2seconds);
CANChannel can_bus(CAN_D1_D2, 32, 32); // (pins, rxQueueSize, txQueueSize);

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

    Particle.function("can", PF_can);
    Particle.function("set_id", PF_set_id);

    Particle.variable("text", PV_text);
    Particle.variable("data", PV_data);
    Particle.variable("id", PV_id);

    strcpy(PV_data, "01234567<<- Bytes received");
    timer_2sec.start();

    CAN_setup(&can_bus);
    // can_bus.begin(125000); // pick the baud rate for your network
    // accept one message. If no filter added by user then accept all messages
    // can_bus.addFilter(0x100, 0x7FF); // (id, mask);
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

    if(can_bus.available()) { // message received
        can_on_receive();
    } else {
        // can_transmit_test();
    }

    interrupts();
}

void can_on_receive(){
    info("debug", "can_on_receive()");
    CANMessage rx;
    if(can_bus.receive(rx)) {
        CAN_publish_msg_as_asci(rx);
        for( auto i = 0; i<8; i++){
            PV_data[i] = rx.data[i];
        }
    } else {
        error (6002);
    }
}

// PF Particle Functions
int PF_can(String args){
    if(args.equals("clearFilters()")){
        can_bus.clearFilters();
        return 1;
    } else if(args.equals("end()")) {
        can_bus.end();
        return 2;
    } else if(args.equals("check()")) {
        CAN_check_error_status();
        return 3;
    } else if(args.equals("test()")) {
        can_transmit_test();
        return 4;
    }

    unsigned char cbuff[MAX_ARG_LENGTH];
    args.getBytes(cbuff, MAX_ARG_LENGTH);
    CAN_send_data_as_asci(can_id, reinterpret_cast<char *>(cbuff));
    return 0;
}

int PF_set_id(String args){
    // Parse an int.
    auto temp = args.toInt();
    // Check that it is valid CAN id
    if( (0< temp) && (temp < 536870912)){ // valid 29 bit identifier
        can_id = temp;
        // set PV_id to the string representation.
        itoa(can_id, PV_id, 10);
        return can_id;
    }else {
        error(6001);
    }
    return -1;
}

void can_transmit_test(){
    CANMessage tx;
    tx.id = 101;
    tx.len = 8;
    tx.data[0] = 'C';
    tx.data[1] = 'a';
    tx.data[2] = 'n';
    tx.data[3] = 'W';
    tx.data[4] = 'o';
    tx.data[5] = 'r';
    tx.data[6] = 'k';
    tx.data[7] = 's';
    can_bus.transmit(tx);

    strcpy(PV_text, "CanWorks");
}
