
// Started from:
// https://community.particle.io/t/photon-can-bus-completed/12634/113

#include "application.h"

CANChannel can(CAN_D1_D2);

void setup() {
    pinMode(D7, OUTPUT);
    digitalWrite(D7, LOW);

    can.begin(125000); // pick the baud rate for your network
    // accept one message. If no filter added by user then accept all messages
    // can.addFilter(0x100, 0x7FF);
}

void loop() {
    CANMessage Message;

    Message.id = 0x100;
    if(can.transmit(Message)){
        Particle.publish("can!", "failed to send");
        delay(2000);
    }

    delay(10);

    if(can.receive(Message)) {
        digitalWrite(D7, HIGH);
        Particle.publish("can!", "received");
    }
}
