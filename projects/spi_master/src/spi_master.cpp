
// *****************************************************************************
// Includes (Ordered close to far, aka stl includes are last)
// *****************************************************************************
#include "SpiMaster.h"
#include "JtagTapState.h"
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
    if(JtagTapState::TEST_LOGIC_RESET != a){
        return 0xFF;
    }
    switch(b){
        //case(CURRENT_STATE): return TXTX;  //1
        case(JtagTapState::TEST_LOGIC_RESET):   return 0xFF; //1
        case(JtagTapState::RUN_TEST_IDLE):      return 0x7F; //0
        
        case(JtagTapState::SELECT_DR):          return 0xBF; //10
        case(JtagTapState::SELECT_IR):          return 0xDF; //110
        
        // case(JtagTapState::CAPTURE_DR):          return 0xBF; //10
        // case(JtagTapState::CAPTURE_IR):          return 0xDF; //110
        
        case(JtagTapState::SHIFT_DR):           return 0x2F; //0010
        case(JtagTapState::SHIFT_IR):           return 0x2F; //0010
        default:                                return 0xFF;
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