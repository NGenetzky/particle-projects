#include "iot_Register.h"

auto d7_out = iot::Pin{D7, OUTPUT};
auto led = iot::DigitalPin{d7_out};

void setup() {
    led.setup();
}

void loop() {
    led.on(); // digitalWrite(ledPin, HIGH); // sets the LED on
    delay(1000);                // waits for a second
    led.off(); // digitalWrite(ledPin, LOW);  // sets the LED off
    delay(1000);                // waits for a second
}
