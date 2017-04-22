
// *****************************************************************************
// Includes (Ordered close to far, aka stl includes are last)
// *****************************************************************************
#include "Pin.h" // iot::Pin
#include "File.h"
#include "ParticleSPI.h"
#include "application.h"

// *****************************************************************************
// Declare Functions
// *****************************************************************************
void setup();
void loop();

// *****************************************************************************
// Global Variables
// *****************************************************************************
auto in_file = iot::File();
auto out_file = iot::File();
auto ss_pin = iot::Pin(SS, OUTPUT);
auto spi = iot::SpiMaster { &in_file, &out_file};

// *****************************************************************************
// Global Variables - Particle Cloud
// *****************************************************************************
const char* PV_in = nullptr;
const char* PV_out = nullptr;
auto PF_write = std::bind( &iot::File::PF_in, &in_file, std::placeholders::_1);

void setup(){
    Particle.publish("spi_master", "setup");
    
    in_file.setup();
    out_file.setup();
    ss_pin.setup();
    
    spi.setup();
    PV_in = spi.in->PV_data();
    PV_out = spi.out->PV_data();
    
    // *****************************************************************************
    // Setup - Particle Cloud
    // *****************************************************************************
    Particle.variable( "in", PV_in );
    Particle.variable( "out", PV_out );
    Particle.function( "write", PF_write );
    
    in_file.write(String("Hello World"));
}

void loop(){
    spi.loop();
}