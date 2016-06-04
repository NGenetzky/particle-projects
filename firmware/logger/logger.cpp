#include "logger.h"
#include "application.h"

// extern void info(const char * name, const char * data);
void info(const char * name, const char * data){
    Serial.printf("%s:%s\n", name, data);
    Particle.publish(name, data);
}

// extern void error(int error_id);
void error(int error_id){
    Particle.publish("error", String(error_id));
}