#include "logger.h"
#include "application.h"

void info(const char * name, const char * data){
    Serial.printf("%s:%s\n", name, data);
    Particle.publish(name, data);
}

void error(int error_id){
    Particle.publish("error", String(error_id));
}