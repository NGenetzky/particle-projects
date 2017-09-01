#include "iot_Register.h"

auto d7_out = iot::Pin{D7, OUTPUT};
auto led = iot::DigitalPin{d7_out};

auto led_port = iot::DigitalPort{ std::vector<iot::DigitalPin>{
    led // 0
}
};

void loop_led_flashing();
int PF_not_implemented( String args );

void setup() {
    led_port.add( iot::Pin{D7, OUTPUT} ); // 1
    
    led_port.setup();
    
    led_port.setup_PF_dport();
    led_port.setup_PF_set();
    led_port.setup_PF_get();
    led_port.setup_PF_digitalread();
    led_port.setup_PF_digitalwrite();
    
    Particle.function("analogread", PF_not_implemented);
    Particle.function("analogwrite", PF_not_implemented);
}

void loop() {
};

void loop_led_flashing()
{
    led_port.digitalWrite(0, HIGH); // digitalWrite(ledPin, HIGH); // sets the LED on
    delay(1000);                // waits for a second
    led_port.digitalWrite(0, LOW); // digitalWrite(ledPin, LOW);  // sets the LED off
    delay(1000);                // waits for a second
}

int PF_not_implemented( String args )
{
    Particle.publish("NotImplemented", args);
    return -1;
}
