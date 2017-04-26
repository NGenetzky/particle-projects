
#pragma once

struct JtagTdr {
    const unsigned slave_select = A2;
    std::vector<uint8_t> tx;
    std::vector<uint8_t> rx;
    SPISettings settings = SPISettings(15*MHZ, LSBFIRST, SPI_MODE0);
    
    JtagTdr() = default;
    
    void setup(){
        SPI.begin(SPI_MODE_MASTER, this->slave_select);
        pinMode(this->slave_select, OUTPUT);
    }
    
    void transfer(){
        this->rx.resize(this->tx.size());
        
        digitalWrite(this->slave_select, HIGH);
        SPI.beginTransaction(this->settings);
        SPI.transfer(this->tx.data(), this->rx.data(),
                    this->tx.size(), NULL);
        SPI.endTransaction();
        digitalWrite(this->slave_select, LOW);
    }
};