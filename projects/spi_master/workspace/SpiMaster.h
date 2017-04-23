
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
    
    void transfer(){
        digitalWrite(this->slave_select, HIGH);
        
        SPI.transfer(this->tx_buffer, this->rx_buffer,
                    this->tx_available, NULL);
        this->rx_available = tx_available;
        this->tx_available = 0;
        
        digitalWrite(this->slave_select, LOW);
    }
    
    void flush() {
        if(this->tx_available){
            this->transfer();
        }
    }
    // void transfer_done(){ } // TOOD
    
    const char* PV_rx(){return (char*) rx_buffer;};
    const char* PV_tx(){return (char*) tx_buffer;};
    
    int PF_tx_set( String str ){
        if( SPI_BUFFER_SIZE < str.length() ){
            return 0 - str.length();
        }
        str.getBytes(this->tx_buffer, 64);
        this->tx_available = str.length();
        return this->tx_available;
    }
    
    int tx_set( int v ){
        tx_buffer[0] = (v & 0xFF); // TODO
        this->tx_available = 1;
        return this->tx_available;
    }
    int PF_tx_set_dec( String str ){
        auto i = str.toInt(); // TODO handle str=='0'
        return this->tx_set(i);
    }
    
    int PF_transfer( String str ){
        auto rv = this->PF_tx_set(str);
        if( 0< rv){
            this->flush();
        }
        return rv;
    }
    
    void setup(){
        SPI.setClockSpeed(15, MHZ);
        SPI.setBitOrder(LSBFIRST);
        SPI.setDataMode(SPI_MODE0);
        SPI.begin(SPI_MODE_MASTER, this->slave_select);
    }
    
};