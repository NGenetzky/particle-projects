
// *****************************************************************************
// Includes (Ordered close to far, aka stl includes are last)
// *****************************************************************************
#include "Pin.h" // iot::Pin
#include "File.h"
#include "SpiMaster.h"
#include "application.h" // Required for Particle.

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
auto spi = SpiMaster{};

// *****************************************************************************
// Global Variables - Particle Cloud
// *****************************************************************************
const char* PV_in = nullptr;
const char* PV_out = nullptr;
const char* PV_rx = spi.PV_rx();
const char* PV_tx = spi.PV_tx();
auto PF_write = std::bind( &iot::File::PF_in, &in_file, std::placeholders::_1);

// *****************************************************************************
// Special Functions
// *****************************************************************************
void setup(){
    Particle.publish("spi_master", "setup");
    
    in_file.setup();
    PV_in = in_file.PV_data();
    
    out_file.setup();
    PV_out = out_file.PV_data();
    
    ss_pin.setup();
    spi.setup();
    
    // *****************************************************************************
    // Setup - Particle Cloud
    // *****************************************************************************
    Particle.variable( "in", PV_in );
    Particle.variable( "out", PV_out );
    Particle.variable( "rx", PV_rx );
    Particle.variable( "tx", PV_tx );
    Particle.function( "write", PF_write );
    
    in_file.write(String("Hello World"));
    
    auto hello_str = String("Hello World");
    hello_str.getBytes(spi.tx_buffer, 64);
    spi.tx_available = hello_str.length();
    spi.transfer();
}

void loop(){
    // spi.transfer();
}