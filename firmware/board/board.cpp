
#include "board.h"
#include "application.h"
#include "global.h"

int led_on(){
    digitalWrite(BOARD_LED, HIGH);
    return 0;
}

int led_off(){
    digitalWrite(BOARD_LED, LOW);
    return 0;
}

int reset_board(){
    System.reset();
    return 0;
}

void disable_cloud_ifD6() {
    pinMode(D6, INPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    if(digitalRead(D6)){  // Indicated whether cloud should be disabled.
        if(Particle.connected() == true){
            Particle.disconnect();
        }
    } else {
        if(Particle.connected() == false){
            Particle.connect();
        }
    }
}

void disable_wifi_ifD6() {
    pinMode(D6, INPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    if(digitalRead(D6)){  // Indicated whether cloud should be disabled.
        if(WiFi.ready() == true){
            WiFi.off();
            Particle.disconnect();
        }
    } else {
        if(WiFi.ready() == false){
            WiFi.on();
            Particle.connect();
        }
    }
}
