
// *****************************************************************************
// Includes (Ordered close to far, aka stl includes are last)
// *****************************************************************************
#include "SpiMaster.h"
#include "JtagTapState.h"
#include "BinaryLiteral.h"
#include "spi_jtag.h"
#include "application.h" // Required for Particle.

// *****************************************************************************
// Declare Functions
// *****************************************************************************
void setup();
void loop();
uint8_t jtag_tms(JtagTapState a, JtagTapState b);
int PF_jtag( String args );

// *****************************************************************************
// Global Variables
// *****************************************************************************
auto spi = SpiMaster{};

// *****************************************************************************
// Global Variables - Particle Cloud
// *****************************************************************************
const char* PV_rx = spi.PV_rx();
const char* PV_tx = spi.PV_tx();
auto PF_tx_set = std::bind( &SpiMaster::PF_tx_set, &spi, std::placeholders::_1);
auto PF_tx_set_dec = std::bind( &SpiMaster::PF_tx_set_dec, &spi, std::placeholders::_1);

// *****************************************************************************
// Special Functions
// *****************************************************************************
void setup(){
    Particle.publish("spi_master", "setup");
    
    spi.setup();
    
    // *****************************************************************************
    // Setup - Particle Cloud
    // *****************************************************************************
    Particle.variable( "rx", PV_rx );
    Particle.variable( "tx", PV_tx );
    Particle.function( "spi_tx", PF_tx_set );
    Particle.function( "spi_tx_dec", PF_tx_set_dec );
    Particle.function( "jtag", PF_jtag );
}

void loop(){
    spi.flush();
}

// *****************************************************************************
// User Functions
// *****************************************************************************

int PF_jtag( String args ){
    auto iarg = args.toInt();
    spi.tx_set(jtag_tms(JtagTapState::TEST_LOGIC_RESET,
                        JtagTapState(iarg)));
}
