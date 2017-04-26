
// *****************************************************************************
// Includes (Ordered close to far, aka stl includes are last)
// *****************************************************************************
#include "SpiMaster.h"
#include "JtagTapState.h"
#include "JtagTap.h"
#include "JtagDevice.h"
#include "BinaryLiteral.h"
#include "application.h" // Required for Particle.

// *****************************************************************************
// Declare Functions
// *****************************************************************************
void setup();
void loop();
int PF_jtag_ir( String args );
int PF_jtag_dr( String args );
int PF_jtag_tap( String args );

// *****************************************************************************
// Global Variables
// *****************************************************************************
auto spi = SpiMaster{A1};
auto jtag_tap = JtagTap(); // A2
auto jd = JtagDevice(); // A3

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
    jtag_tap.setup();
    
    // *****************************************************************************
    // Setup - Particle Cloud
    // *****************************************************************************
    Particle.variable( "rx", PV_rx );
    Particle.variable( "tx", PV_tx );
    Particle.function( "spi_tx", PF_tx_set );
    Particle.function( "spi_tx_dec", PF_tx_set_dec );
    Particle.function( "jtag_ir", PF_jtag_ir );
    Particle.function( "jtag_dr", PF_jtag_dr );
    Particle.function( "jtag_tap", PF_jtag_tap );
}

void loop(){
    spi.flush();
}

// *****************************************************************************
// User Functions
// *****************************************************************************

int PF_jtag_ir( String args ){
    auto iarg = args.toInt();
    return jd.ir_shift(iarg);
}

int PF_jtag_dr( String args ){
    auto iarg = args.toInt();
    return jd.ir_shift(iarg);
}

int PF_jtag_tap( String args ){
    auto iarg = args.toInt();
    return jtag_tap.goto_state(JtagTapState(iarg));
}