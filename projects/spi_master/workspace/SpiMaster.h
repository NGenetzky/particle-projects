
#pragma once
#include "application.h" // Required for Particle.

// The hardware SPI pin functions, which can be used via the SPI object, are mapped as follows:
// SS => A2 (default)
// SCK => A3
// MISO => A4
// MOSI => A5
// SPISettings{ 4*MHZ, MSBFIRST, SPI_MODE0 };

#define SPI_BUFFER_SIZE 64

struct SpiMaster{
    // +1 so data is always null terminated.
    uint8_t rx_buffer[SPI_BUFFER_SIZE+1] = {0};
    uint8_t tx_buffer[SPI_BUFFER_SIZE+1] = {0};
    unsigned slave_select = SS;
    unsigned tx_available = 0;
    unsigned rx_available = 0;
    
    SpiMaster() = default;
    
    const char* PV_rx(){return (char*) rx_buffer;};
    const char* PV_tx(){return (char*) tx_buffer;};
    // void transfer_done(){ } // TOOD
    
    void setup(){
        SPI.setClockSpeed(15, MHZ);
        SPI.setBitOrder(LSBFIRST);
        SPI.setDataMode(SPI_MODE0);
        SPI.begin(SPI_MODE_MASTER, this->slave_select);
    }
    
    void transfer(){
        digitalWrite(this->slave_select, HIGH);
        
        SPI.transfer(this->tx_buffer, this->rx_buffer,
                    this->tx_available, NULL);
        
        digitalWrite(this->slave_select, LOW);
        this->rx_available = tx_available;
        this->tx_available = 0;
    }
    
};