#include "wreg.h"
#include "application.h"

#include "global.h"

char wreg[MAX_VARIABLE_LENGTH +1];

void wreg_setup(){
    Particle.variable("wreg", wreg); 
    wreg[MAX_VARIABLE_LENGTH] = '\0'; // Overflow safeguard.
    strcpy(wreg, "default");
}

int wreg_set(const char* value){
    strcpy(wreg, value);
    return 0;
}

char *wreg_get(){
    return wreg;
}