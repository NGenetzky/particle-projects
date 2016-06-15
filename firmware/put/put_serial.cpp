#include "put_serial.h"

#include "node.h"
#include "put.h"

extern void info(const char * name, const char * data);

int put_serial_setup(unsigned int start){
    auto i = start;
    
    node_set(i, "s0");
    add_put(i, put_serial0);
    
    node_set(++i, "s1");
    add_put(i, put_serial1);
    
    return ++i-start;
}

int put_serial0(const char *s){
    Serial.print(s);
    return 0;
}

int put_serial1(const char *s){
    Serial1.print(s);
    return 0;
}