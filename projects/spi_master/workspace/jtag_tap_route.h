#pragma once
#include "JtagTapState.h"
#include "BinaryLiteral.h"

// uint8_t jtag_tms(JtagTapState a, JtagTapState b);
inline uint8_t jtag_tms(JtagTapState a, JtagTapState b){
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
                
                case(JtagTapState::SELECT_DR):         return  B(10111111);  //10
                case(JtagTapState::CAPTURE_DR):        return  B(01011111);  //010
                case(JtagTapState::EXIT1_DR):          return  B(10101111);  //1010
                case(JtagTapState::EXIT2_DR):          return  B(10101011);  //101010
                case(JtagTapState::UPDATE_DR):         return  B(11010111);  //11010
                
                case(JtagTapState::SELECT_IR):         return  B(11011111);  //110
                case(JtagTapState::CAPTURE_IR):        return  B(01101111);  //0110
                case(JtagTapState::EXIT1_IR):          return  B(10110111);  //10110
                case(JtagTapState::EXIT2_IR):          return  B(10101101);  //1010110
                case(JtagTapState::UPDATE_IR):         return  B(11011011);  //110110
                default:                               return  B(11111111);
            }
            
        case(JtagTapState::RUN_TEST_IDLE):
            switch(b){
                case(JtagTapState::TEST_LOGIC_RESET):  return  B(11100000);  //111
                case(JtagTapState::RUN_TEST_IDLE):     return  B(00000000);  //
                case(JtagTapState::SHIFT_DR):          return  B(00100000);  //001
                case(JtagTapState::SHIFT_IR):          return  B(00110000);  //0011
                case(JtagTapState::PAUSE_DR):          return  B(01010000);  //0101
                case(JtagTapState::PAUSE_IR):          return  B(01011000);  //01011
                default:                               return  B(11111111);
            }
        default: return B(11111111);
    }
}