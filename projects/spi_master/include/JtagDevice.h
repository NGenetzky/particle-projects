
#pragma once
#include "stdint.h"

struct JtagDevice {
    const unsigned cs_jtag = A3;
    JtagTap tap;
    SPISettings settings = SPISettings(15*MHZ, LSBFIRST, SPI_MODE0);
    
    JtagDevice() = default;
    
    void setup(){
        this->tap.setup();
        SPI.begin(SPI_MODE_MASTER, this->cs_jtag);
        pinMode(this->cs_jtag, OUTPUT);
    }
    
    uint8_t transfer(uint8_t tx){
        digitalWrite(this->cs_jtag, HIGH);
        SPI.beginTransaction(this->settings);
        auto rx = SPI.transfer(tx);
        SPI.endTransaction();
        digitalWrite(this->cs_jtag, LOW);
        return rx;
    }
    
    uint8_t ir_shift(uint8_t value){
        this->tap.goto_state(JtagTapState::SHIFT_IR);
        auto rv = this->transfer(value);
        this->tap.goto_state(JtagTapState::RUN_TEST_IDLE);
        return rv;
    }
    
    uint8_t dr_shift(uint8_t value){
        this->tap.goto_state(JtagTapState::SHIFT_DR);
        auto rv = this->transfer(value);
        this->tap.goto_state(JtagTapState::RUN_TEST_IDLE);
        return rv;
    }
    
    // void dr_shift(
    //     uint32_t write_length, const uint8_t * write_data,
    //     uint32_t read_length, uint8_t * read_data,
    //     )
    // { }
    
    // uint32_t ir_shift( uint32_t new_ir ){ }

    
};