
#include "application.h"

// SPI slave example
static uint8_t rx_buffer[64];
static uint8_t tx_buffer[64];
static uint32_t select_state = 0x00;
static uint32_t transfer_state = 0x00;

void onTransferFinished() {
    transfer_state = 1;
}

void onSelect(uint8_t state) {
    if (state)
        select_state = state;
}

/* executes once at startup */
void setup() {
    Serial.begin(9600);
    for (int i = 0; i < sizeof(tx_buffer); i++)
      tx_buffer[i] = (uint8_t)i;
    SPI.onSelect(onSelect);
    SPI.begin(SPI_MODE_SLAVE, A2);
}

/* executes continuously after setup() runs */
void loop() {
    while (1) {
        while(select_state == 0);
        select_state = 0;

        transfer_state = 0;
        SPI.transfer(tx_buffer, rx_buffer, sizeof(rx_buffer), onTransferFinished);
        while(transfer_state == 0);
        if (SPI.available() > 0) {
            Serial.printf("Received %d bytes", SPI.available());
            Serial.println();
            for (int i = 0; i < SPI.available(); i++) {
                Serial.printf("%02x ", rx_buffer[i]);
            }
            Serial.println();
        }
    }
}