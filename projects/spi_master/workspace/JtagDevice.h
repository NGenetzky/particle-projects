
#pragma once
#include "stdint.h"
#include "ParticleSpi.h"

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
    
    void beginTransaction(bool dr=true)
    {
        if(dr){
            this->tap.goto_state(JtagTapState::SHIFT_DR);
        } else {
            this->tap.goto_state(JtagTapState::SHIFT_IR);
        }
        digitalWrite(this->cs_jtag, HIGH);
        SPI.beginTransaction(this->settings);
    }
    
    void endTransaction(bool goto_rti=true)
    {
        SPI.endTransaction();
        digitalWrite(this->cs_jtag, LOW);
        this->tap.goto_state(JtagTapState::RUN_TEST_IDLE);
    }
    
    uint8_t transfer(uint8_t tx){
        digitalWrite(this->cs_jtag, HIGH);
        SPI.beginTransaction(this->settings);
        auto rx = SPI.transfer(tx);
        SPI.endTransaction();
        digitalWrite(this->cs_jtag, LOW);
        return rx;
    }
    
    // uint8_t
    uint8_t ir_shift(uint8_t value)
    {
        this->beginTransaction(false);
        auto rv = this->transfer(value);
        this->endTransaction(true);
        return rv;
    }
    
    uint8_t dr_shift(uint8_t value)
    {
        this->beginTransaction(true);
        auto rv = SPI.transfer(value);
        this->endTransaction(true);
        return rv;
    }
    
    // void dr_shift(
    //     uint32_t write_length, const uint8_t * write_data,
    //     uint32_t read_length, uint8_t * read_data,
    //     )
    // { }
    
    // uint32_t ir_shift( uint32_t new_ir ){ }
    
    std::vector<uint8_t> ir_shift(std::vector<uint8_t> tx_buffer)
    {
        this->beginTransaction(false);
        auto rx_buffer = spi_transfer(tx_buffer);
        this->endTransaction(true);
        return rx_buffer;
    }
    
    std::vector<uint8_t> dr_shift(std::vector<uint8_t> tx_buffer)
    {
        this->beginTransaction(true);
        auto rx_buffer = spi_transfer(tx_buffer);
        this->endTransaction(true);
        return rx_buffer;
    }

    
};