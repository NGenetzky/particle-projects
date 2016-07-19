#ifndef PUBBUFF_H
#define PUBBUFF_H

#include "application.h"
#include "global.h"

extern void error(int error_id);

// I recommend using a timer to poll on the pubbuff.
// Example use
/*
Timer pubbuff_timer(5000, pubbuff_poll); //(period, callback, one_shot)

void setup(){
    pubbuff_timer.start();
}
void loop(){
    pubbuff("loop", "123");
    delay(500);
}
*/
int pubbuff_setup(int ms_between);
void pubbuff(const char * name, const char * data);
void pubbuff_poll();
char* get_pubbuffer();

#endif // PUBBUFF_H