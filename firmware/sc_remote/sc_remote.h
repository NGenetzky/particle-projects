#pragma once

namespace SCR {

// Separated out to separate functions so they can be used as command.
void led1_on();
void led2_on();
void led3_on();

void led1_off();
void led2_off();
void led3_off();

void thingspeak_analog();
void update();
void read_analog();

void variable_sc_remote();
void setup();
void loop();

} // SCR
