
// *****************************************************************************
// Includes (Ordered close to far, aka stl includes are last)
// *****************************************************************************
#include "SpiMaster.h"
#include "JtagTapState.h"
#include "BinaryLiteral.h"
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
uint8_t jtag_tms(JtagTapState a, JtagTapState b){
    switch(a){
        case(JtagTapState::TEST_LOGIC_RESET):
            switch(b){
                //case(CURRENT_STATE):                 return  B(76543210);  //last_first
                case(JtagTapState::TEST_LOGIC_RESET):  return  B(11111111);  //1
                case(JtagTapState::RUN_TEST_IDLE):     return  B(01111111);  //0
                case(JtagTapState::SHIFT_DR):          return  B(00101111);  //0010
                case(JtagTapState::SHIFT_IR):          return  B(00110111);  //00110
                case(JtagTapState::PAUSE_DR):          return  B(01010111);  //01010
                case(JtagTapState::PAUSE_IR):          return  B(01011011);  //010110
                default:                                return 0xFF;
            }
        default: return 0xFF;
    }
}

int PF_jtag( String args ){
    auto iarg = args.toInt();
    spi.tx_set(jtag_tms(JtagTapState::TEST_LOGIC_RESET,
                        JtagTapState(iarg)));
    
    // switch(iarg){
    //     case(0):
    //         spi.tx_set(jtag_tms(JtagTapState::TEST_LOGIC_RESET,
    //                             JtagTapState::RUN_TEST_IDLE));
    //         break;
    //     case(1):
    //         spi.tx_set(jtag_tms(JtagTapState::TEST_LOGIC_RESET,
    //                             JtagTapState::SHIFT_DR));
    //         break;
    //     default:
    //         Particle.publish("jtag_unknown", args);
    // }
}
