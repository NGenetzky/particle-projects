#include "sc_remote.h"
#include <limits>
#include "application.h"

#include "cmd.h"
#include "global.h"

#include "rgb.h"
#include "cmd_rgb.h"

extern void info(const char * name, const char * data);

namespace SCR {

// Structs for data
struct AnalogIn {
    unsigned pot1;
    unsigned pot2;
    unsigned joyx;
    unsigned joyy;
};

struct DigitalIn {
    unsigned sw1;
    unsigned sw2;
    unsigned sw3;
    unsigned sw4;
};

struct DigitalOut {
    unsigned led0;
    unsigned led1;
    unsigned led2;
};

struct Timing {
    unsigned long sw1_rise;
    unsigned long sw1_fall;
    unsigned long sw2_rise;
    unsigned long sw2_fall;
    unsigned long sw3_rise;
    unsigned long sw3_fall;
    unsigned long sw4_rise;
    unsigned long sw4_fall;
};

// VARAIBLES {

// Config
const unsigned long SW_INTERVAL = 250 ; // unit: microseconds // 10ms

// PIN mappings
const int POT1 = A0;  // POT1
const int POT2 = A1;  // POT2
const int LED1 = A5;  // pin for LED1 which is close to POT1 and used to indicate the state of POT1
const int LED2 = A4;  // pin for LED2 which is close to POT2 and used to indicate the state of POT2
const int LED3 = D5;  // pin for LED3 which is close to NRF24L01 and used to indicate the state of NRF24L01
const int SW1 = D4;   // pin for S1
const int SW2 = D3;   // pin for S2
const int SW3 = D2;   // pin for S3
const int SW4 = D7;   // pin for clicking the joystick
const int JOYX = A2;  // pin for direction X of joystick
const int JOYY = A3;  // pin for direction Y of joystick

AnalogIn a_in;
DigitalIn d_in;
DigitalOut d_out;
Timing timing;

char data_string[MAX_PUBLISH_LENGTH];

// } VARAIBLES

// ISR from button press
static void on_sw1(){
    noInterrupts();
    auto state = digitalRead( SW1 );
    if(state == HIGH){
        timing.sw1_rise = millis();
        d_in.sw1 = timing.sw1_rise - timing.sw1_fall;
    } else {
        timing.sw1_fall = millis();
    }
    interrupts();
}

static void on_sw2(){
    noInterrupts();
    auto state = digitalRead( SW2 );
    if(state == HIGH){
        timing.sw2_rise = millis();
        d_in.sw2 = timing.sw2_rise - timing.sw2_fall;
    } else {
        timing.sw2_fall = millis();
    }
    interrupts();
}

static void on_sw3(){
    noInterrupts();
    auto state = digitalRead( SW3 );
    if(state == HIGH){
        timing.sw3_rise = millis();
        d_in.sw3 = timing.sw3_rise - timing.sw3_fall;
    } else {
        timing.sw3_fall = millis();
    }
    interrupts();
}

static void on_sw4(){
    noInterrupts();
    auto state = digitalRead( SW4 );
    if(state == HIGH){
        timing.sw4_rise = millis();
        d_in.sw4 = timing.sw4_rise - timing.sw4_fall;
    } else {
        timing.sw4_fall = millis();
    }
    interrupts();
}

void led1_on(){
    digitalWrite(LED1, HIGH);
}
void led2_on(){
    digitalWrite(LED2, HIGH);
}
void led3_on(){
    digitalWrite(LED3, HIGH);
}

void led1_off(){
    digitalWrite(LED1, LOW);
}
void led2_off(){
    digitalWrite(LED2, LOW);
}
void led3_off(){
    digitalWrite(LED3, LOW);
}

void read_analog(){
    a_in.pot1 = analogRead( POT1 );
    a_in.pot2 = analogRead( POT2 );
    a_in.joyx = analogRead( JOYX );
    a_in.joyy = analogRead( JOYY );
}
void thingspeak_analog(){
    // TODO: Implement without String
    String json = String(
          "{\"1\":\"" + String(millis())
        + "\",\"2\":\"" + String(a_in.pot1)
        + "\",\"3\":\"" + String(a_in.pot2)
        + "\",\"4\":\"" + String(a_in.joyx)
        + "\",\"5\":\"" + String(a_in.joyy)
        + "\"}");
    Particle.publish("thingspeak", json, 60, PRIVATE);
}

void variable_sc_remote(){
    Particle.variable("sc_remote", data_string);
}
void update(){
    sprintf(data_string, "%u,%u,%u,%u,%u,%u,%u,%u", millis(),
            a_in.pot1, a_in.pot2, a_in.joyx, a_in.joyy,
            d_in.sw1, d_in.sw2, d_in.sw3);
}

//const unsigned long SW_INTERVAL = 250 ; // unit: microseconds // 10ms
static void
on_sw1_for_x_intervals(unsigned i){
    const int CMD_RGB_START = 550;
    switch(i){
        case 0:
        case 1:
            led1_on();
            led2_off();
            led3_off();
            rgb_color(COLOR_GREEN);
            break;

        case 2:
        case 3:
        case 4: // 100ms = 4* 250ms
            led1_on();
            led2_on();
            led3_off();
            rgb_color(COLOR_YELLOW);
            break;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            led1_on();
            led2_on();
            led3_on();
            rgb_color(COLOR_RED);
            break;

        case 11:
        case 12:
        case 13:
        case 14:


        default:
            execute(550); // Release the RGB
            Particle.publish("scr::sw1", String(i), 60, PRIVATE);
    }
}

static void
on_sw2_for_x_intervals(unsigned i){
    const int CMD_RGB_START = 550;
    switch(i){
        case 0:
        case 1:
            led1_on();
            led2_off();
            led3_off();
            // Modify GREEN BLUE
            rgb_color(0, a_in.pot1, a_in.pot2);
            break;

        case 2:
        case 3:
        case 4: // 100ms = 4* 250ms
            led1_off();
            led2_on();
            led3_off();
            // Modify RED and BLUE
            rgb_color(a_in.pot1, 0, a_in.pot2);
            break;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            led1_off();
            led2_off();
            led3_on();
            // Modify RED and GREEN
            rgb_color(a_in.pot1, a_in.pot2, 0);
            execute(1); // Publish cmds
            break;

        case 11:
        case 12:
        case 13:
        case 14:

        default:
            led1_off();
            led2_off();
            led3_off();
            execute(550); // Release the RGB
            Particle.publish("scr::sw2", String(i), 60, PRIVATE);
    }
}


//const unsigned long SW_INTERVAL = 250 ; // unit: microseconds // 10ms
static void
on_sw3_for_x_intervals(unsigned i){
    const int CMD_RGB_START = 550;
    switch(i){
        case 0:
        case 1:
            led1_off();
            led2_off();
            led3_off();

            thingspeak_analog();
            break;

        case 2:
        case 3:
        case 4: // 100ms = 4* 250ms
            led1_on();
            led2_on();
            led3_off();
            rgb_color(COLOR_YELLOW);
            break;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            led1_on();
            led2_on();
            led3_on();
            rgb_color(COLOR_RED);
            break;

        case 11:
        case 12:
        case 13:
        case 14:


        default:
            execute(550); // Release the RGB
            Particle.publish("scr::sw3", String(i), 60, PRIVATE);
    }
}


void poll_sw1(){
    const int CMD_RGB_START = 550;


    if( d_in.sw1 ){
        unsigned x = (d_in.sw1 / SW_INTERVAL);
        on_sw1_for_x_intervals(x);

        Particle.publish("scr::sw1", String(d_in.sw1), 60, PRIVATE);
        d_in.sw1 = 0; // Zero the duration.
    }
}

static void
poll_sw2(){
    if( d_in.sw2 ){

        unsigned x = (d_in.sw2 / SW_INTERVAL);
        on_sw2_for_x_intervals(x);

        Particle.publish("scr::sw2", String(d_in.sw2), 60, PRIVATE);
        d_in.sw2 = 0;// Zero the duration.
    }
}

static void
poll_sw3(){
    if( d_in.sw3 ){

        unsigned x = (d_in.sw3 / SW_INTERVAL);
        on_sw3_for_x_intervals(x);

        Particle.publish("scr::sw3", String(d_in.sw3), 60, PRIVATE);
        d_in.sw3 = 0;// Zero the duration.
    }
}

static void
poll_sw4(){
    if( d_in.sw4 ){
        led1_on();
        led2_on();
        led3_on();

        Particle.publish("scr::sw4", String(d_in.sw4), 60, PRIVATE);
        d_in.sw4 = 0;// Zero the duration.
    }
}

// Timer thingspeak_tmr()
Timer thingspeak_tmr(5000, thingspeak_analog);
void setup(){
    pinMode( LED1, OUTPUT );
    pinMode( LED2, OUTPUT );
    pinMode( LED3, OUTPUT );

    pinMode( SW1, INPUT );
    attachInterrupt( SW1, on_sw1, CHANGE, 13);

    pinMode( SW2, INPUT );
    attachInterrupt( SW2, on_sw2, CHANGE, 13);

    pinMode( SW3, INPUT );
    attachInterrupt( SW3, on_sw3, CHANGE, 13);

    pinMode( SW4, INPUT );
    attachInterrupt( SW4, on_sw4, CHANGE, 13);

    // Note: do not set the pinMode() with analogRead(). The pinMode() is
    // automatically set to AN_INPUT the first time analogRead() is called
    // src: https://docs.particle.io/reference/firmware/photon/#analogread-adc-
    // A0 // POT1
    // A1 // POT2
    // A2 // pin for direction X of joystick
    // A3 // pin for direction Y of joystick


    thingspeak_tmr.start();
}

void loop(){
    // digital values are updated automatically
    read_analog(); // Read analog values

    // Updates the data string that is exposed via the cloud.
    update();

    poll_sw1();
    poll_sw2();
    poll_sw3();
    poll_sw4();
}

} // end SCR
