#include "pubbuff.h"


const int PUBBUFF_SIZE = 1024;
char pub_name[12]={'\0'}; // Max size of event name is 12.
char pubbuffer[PUBBUFF_SIZE]={'\0'};


// {{ Declare a timer
#if defined (STM32F10X_MD) // Core hardware specific code.
// Particle Core does not support any code utilizing Software Timers.
#include "SparkIntervalTimer.h"
IntervalTimer pubbuff_timer;
#endif

#if defined (STM32F2XX) // Photon hardware specific code.
Timer pubbuff_timer(5000, pubbuff_poll); //(period, callback, one_shot)
#endif
// Declare a timer }}


int pubbuff_setup(int ms_between){
    
    // {{ Start the timer
    #if defined (STM32F10X_MD) // Core hardware specific code.
    // Particle Core does not support any code utilizing Software Timers.
    pubbuff_timer.begin(pubbuff_poll, 2*ms_between, hmSec); // hmSec= Half Milisecond
    #endif
    
    #if defined (STM32F2XX) // Photon hardware specific code.
    pubbuff_timer.changePeriod(ms_between);
    pubbuff_timer.start();
    #endif
    // Start the timer }}
    
    return 0;
}

void pubbuff(const char * name, const char * data){
    if(strcmp(name, pub_name)==0){
        int new_len = strlen(pubbuffer) + strlen(data) + sizeof(char);
        if (new_len < PUBBUFF_SIZE){
            strcat(pubbuffer, data);
        } else {
            error(19);
        }
    } else{
        strcpy(pub_name, name);
        strcpy(pubbuffer, data);
    }
}

void pubbuff_poll(){
    if(0 < strlen(pubbuffer)){
        Particle.publish(pub_name, pubbuffer);
        strcpy(pubbuffer, ""); // Clear the C string without zeroing the buffer.
    }
}

char* get_pubbuffer(){
    return pubbuffer;
}
