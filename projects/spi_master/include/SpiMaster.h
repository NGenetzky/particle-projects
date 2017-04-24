
#pragma once
#include "application.h" // Required for Particle.

// The hardware SPI pin functions, which can be used via the SPI object, are mapped as follows:
// SS => A2 (default)
// SCK => A3
// MISO => A4
// MOSI => A5
// SPISettings{ 4*MHZ, MSBFIRST, SPI_MODE0 };

String uint8_array_to_string_asci( uint8_t *data, unsigned len){
    String received;
    received.reserve(len+1);
    for (unsigned i = 0; i < len; i++) {
        received += char(data[i]);
    }
    return received;
}

String uint8_array_to_string_hex( uint8_t *data, unsigned len){
    String received;
    received.reserve( 3*(len+1) );
    for (unsigned i = 0; i < len; i++) {
        received += String::format("%02x ", data[i]);
    }
    return received;
}

struct SpiMaster{
    // SPI Configuration:
    unsigned slave_select = SS;
    SPISettings settings = SPISettings(15*MHZ, LSBFIRST, SPI_MODE0);
    // SPI Data:
    // +1 so data is always null terminated.
    static constexpr unsigned SPI_BUFFER_SIZE = 64;
    uint8_t rx_buffer[SPI_BUFFER_SIZE+1] = {0};
    uint8_t tx_buffer[SPI_BUFFER_SIZE+1] = {0};
    unsigned tx_available = 0;
    unsigned rx_available = 0;
    
    SpiMaster() = default;
    SpiMaster(unsigned slave_select)
        : slave_select(slave_select)
    { }
    SpiMaster(unsigned slave_select, SPISettings settings)
        : slave_select(slave_select)
        , settings(settings)
    { }
    
    void transfer(){
        this->PUB_spi_tx_hex();
        
        digitalWrite(this->slave_select, HIGH);
        SPI.beginTransaction(this->settings);
        SPI.transfer(this->tx_buffer, this->rx_buffer,
                    this->tx_available, NULL);
        SPI.endTransaction();
        digitalWrite(this->slave_select, LOW);
        
        this->rx_available = tx_available;
        this->tx_available = 0;
        this->PUB_spi_rx_hex();
    }
    
    
    void flush() {
        if(this->tx_available){
            this->transfer();
        }
    }
    // void transfer_done(){ } // TOOD
    
    void setup(){
        SPI.begin(SPI_MODE_MASTER, this->slave_select);
    }
    
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
    
    void PUB_spi_rx_asci(){
        auto s = uint8_array_to_string_asci(this->rx_buffer, this->rx_available);
        Particle.publish("spi_rx_asci", s);
    }
    
    void PUB_spi_rx_hex(){
        auto s = uint8_array_to_string_hex(this->rx_buffer, this->rx_available);
        Particle.publish("spi_rx_hex", s);
    }
    
    void PUB_spi_tx_hex(){
        auto s = uint8_array_to_string_hex(this->tx_buffer, this->tx_available);
        Particle.publish("spi_tx_hex", s);
    }
    
    
};