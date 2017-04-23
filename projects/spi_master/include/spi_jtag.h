
#pragma once
#include "BinaryLiteral.h"

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
                default:                               return  B(11111111);
            }
        default: return B(11111111);
    }
}