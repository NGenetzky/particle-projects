/*
  Project: serial_pub_sub
  Description: Demonstrate publish/subscribe with serial.
  Author: ngenetzky
  Date: 2017-09-19
*/

#include "application.h"
#include <vector>
#include "iot/Serial_S1.h"
#include "iot/RateLimit.h"

iot::RateLimit s1_rl(1, 5000);

iot::Serial_S1 s1;
std::vector<char> s0i;

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
    Serial.begin();
    
    s1.setup(9600);
    iot::setup_PF_s1_write("s1");
    iot::setup_PS_s1_write("ttyS0");
    s1_rl.setup();
    
    Particle.publish("setup()", "completed");
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}

void s0_publish()
{
    s0i.push_back('\0');
    Particle.publish("s0i", s0i.data());
    s0i.clear();
}

void s1_maybe_publish()
{
    if(s1_rl.get()) {
        s1.publish_buffer();
    }
}

////////////////////////////////////////////////////////////////////////////////
// serialEvent()
// A family of application-defined functions that are called whenever there is data to be read from a serial peripheral.
// serialEvent: called when there is data available from Serial
// usbSerialEvent1: called when there is data available from USBSerial1
// serialEvent1: called when there is data available from Serial1
// serialEvent2: called when there is data available from Serial2
// The serialEvent functions are called in between calls to the application
// loop(). This means that if loop() runs for a long time due to delay() calls or
// other blocking calls the serial buffer might become full between subsequent
// calls to serialEvent and serial characters might be lost. Avoid long delay()
// calls in your application if using serialEvent.Since serialEvent functions
// are an extension of the application loop, it is ok to call any functions
// that you would also call from loop().
void serialEvent(){ 
    delay(100);
    auto char_available = Serial.available();
    if(char_available==0){
        return;
    }
    for(auto i=0; i< char_available; i++){
        s0i.push_back(Serial.read());
    }
    s0_publish();
}
void serialEvent1(){ 
    s1.on_serial_event();
    s1_maybe_publish();
}
////////////////////////////////////////////////////////////////////////////////
