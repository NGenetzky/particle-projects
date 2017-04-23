
#include "application.h"

// #define SERIAL_EN
#define PUBLISH_EN

enum class SlaveState{
    SELECTED,
    TRANSFERING,
    POST_TRANSFER,
    RESET
};
SlaveState state = SlaveState::RESET;

// SPI slave example
static uint8_t rx_buffer[64];
static uint8_t tx_buffer[64];

void onTransferFinished() {
    state = SlaveState::POST_TRANSFER;
}

void onSelect(uint8_t is_selected) {
    if( SlaveState::TRANSFERING == state ){
        if( ! is_selected ){
            // TODO: Inform user.
            SPI.transferCancel();
            state = SlaveState::POST_TRANSFER; // If Master pulls SS down then reset.
            return;
        }
    }
    
    if (is_selected) {
        state = SlaveState::SELECTED;
    } else {
        state = SlaveState::RESET; // If Master pulls SS down then reset.
    }
}

void rx_buffer_to_serial(){
    Serial.printf("Received %d bytes", SPI.available());
    Serial.println();
    for (int i = 0; i < SPI.available(); i++) {
        Serial.printf("%02x ", rx_buffer[i]);
    }
    Serial.println();
}

void rx_buffer_to_publish(){
    Particle.publish("spi_rx_len",
        String::format("Received %d bytes", SPI.available())
        );
    String received;
    received.reserve(64+1);
    for (int i = 0; i < SPI.available(); i++) {
        received += char(rx_buffer[i]);
        // received += String::format("%02x ", rx_buffer[i]);
    }
    Particle.publish("spi_rx_asci", received);
    // Particle.publish("spi_rx_data", received);
}

/* executes once at startup */
void setup() {
#ifdef SERIAL_EN
    Serial.begin(9600);
#endif
    for (unsigned i = 0; i < sizeof(tx_buffer); i++){
        tx_buffer[i] = (uint8_t)i;
    }
    SPI.onSelect(onSelect);
    SPI.begin(SPI_MODE_SLAVE, A2);
    pinMode(D7, OUTPUT);
}

/* executes continuously after setup() runs */
void loop() {
    switch(state) {
        default:
        case SlaveState::RESET:
        case SlaveState::TRANSFERING:
            return;

        case SlaveState::SELECTED:
            digitalWrite(D7, 1);
            SPI.transfer(tx_buffer, rx_buffer, sizeof(rx_buffer), onTransferFinished);
            state = SlaveState::TRANSFERING;
            break;
            
        case SlaveState::POST_TRANSFER:
            if (SPI.available() > 0) {
#ifdef PUBLISH_EN
                rx_buffer_to_publish();
#endif
#ifdef SERIAL_EN
                rx_buffer_to_serial();
#endif
            break;
            }
            
            state = SlaveState::RESET;
            digitalWrite(D7, 0);
    }
}