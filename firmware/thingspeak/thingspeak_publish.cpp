#include "application.h" // Particle.publish
#include "thingspeak_publish.h"



void thingspeak_publish(unsigned a1, unsigned a2, unsigned a3, unsigned a4, unsigned a5){
    // TODO: Implement without String
    String json = String(
          "{\"1\":\"" + String(a1)
        + "\",\"2\":\"" + String(a2)
        + "\",\"3\":\"" + String(a3)
        + "\",\"4\":\"" + String(a4)
        + "\",\"5\":\"" + String(a5)
        + "\"}");
    Particle.publish("thingspeak", json, 60, PRIVATE);
}