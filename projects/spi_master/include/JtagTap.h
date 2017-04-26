
#pragma once
#include "BinaryLiteral.h"
#include "JtagTapState.h"
#include "jtag_tap_route.h"


struct JtagTap {
    const unsigned slave_select = A2;
    JtagTapState state = JtagTapState::TEST_LOGIC_RESET;
    SPISettings settings = SPISettings(15*MHZ, LSBFIRST, SPI_MODE0);
    
    JtagTap() = default;
    
    void setup(){
        SPI.begin(SPI_MODE_MASTER, this->slave_select);
        pinMode(this->slave_select, OUTPUT);
    }
    
    uint8_t transfer(uint8_t tx){
        digitalWrite(this->slave_select, HIGH);
        SPI.beginTransaction(this->settings);
        auto rx = SPI.transfer(tx);
        SPI.endTransaction();
        digitalWrite(this->slave_select, LOW);
        return rx;
    }
    
    bool goto_state(JtagTapState next_state){
        this->transfer(jtag_tms(this->state, next_state));
        this->state = next_state;
        return true; // TODO: check feedback
    }
};

