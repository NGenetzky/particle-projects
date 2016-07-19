
#include "i2c_io.h"
#include "application.h"

#include "Adafruit_MCP23017.h"
// 32 = 0x20 = (A2=A1=A0=0)

// {{ Declare a timer
#if defined (STM32F10X_MD) // Core hardware specific code.
// Particle Core does not support any code utilizing Software Timers.
#include "SparkIntervalTimer.h"
IntervalTimer io_timer;
#endif

#if defined (STM32F2XX) // Photon hardware specific code.
Timer io_timer(500, io_poll); //(period, callback, one_shot)
#endif
// Declare a timer }}


Adafruit_MCP23017 ioA; 
    // LCD Address is d0x20 + [A2:A0]. Begin only considers [A2:A0]
    
uint16_t gpio_v =0x5555;

void io_setup(){
    ioA.begin(0); // [A2:A0]=000=Address used by library, but i2c@32.
    
    // Set all to output
    for(int i=0; i<16; ++i){
        ioA.pinMode(i, OUTPUT);
    }
    
    ioA.writeGPIOAB(gpio_v);
    
    // {{ Start the timer
    #if defined (STM32F10X_MD) // Core hardware specific code.
    // Particle Core does not support any code utilizing Software Timers.
    io_timer.begin(io_poll, 2*500, hmSec); // hmSec= Half Milisecond
    #endif
    
    #if defined (STM32F2XX) // Photon hardware specific code.
    io_timer.start();
    #endif
    // Start the timer }}
}

void io_poll(){
    gpio_v+=100;
    ioA.writeGPIOAB(gpio_v);
}