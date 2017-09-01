#include "iot_Tinker.h"

bool d7_tinker(int p, int &v);
    
auto tinker = iot::Tinker{ std::vector<iot::TinkerFunction>{
        d7_tinker
} };

void setup() {
    pinMode(D7, OUTPUT);
    tinker.setup_PF_tinker();
}

void loop() {
}

bool d7_tinker(int p, int &v)
{
    switch ( v ) {
        case iot::Tinker::DR:
            v = digitalRead( D7 );
            return true; // Tinker request was handled.
            
        case iot::Tinker::DW0:
            digitalWrite(D7, LOW);
            v = iot::Tinker::SUCCESS; // Update the App display
            return true; // Tinker request was handled.
            
        case iot::Tinker::DW1:
            digitalWrite(D7, HIGH);
            v = iot::Tinker::SUCCESS; // Update the App display
            return true; // Tinker request was handled.
    
        default:
            return false; // Tinker request was not handled.
    }
};