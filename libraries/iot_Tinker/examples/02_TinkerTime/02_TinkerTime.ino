#include "iot_Tinker.h"

bool millis_tinker(int p, int &v);
bool micros_tinker(int p, int &v);
    
// NOTE conflict: Both millis_tinker and micros_tinker try to handle the request to
// analog read a5. Since micros is defined first, then it will handle the request.
auto tinker = iot::Tinker{ std::vector<iot::TinkerFunction>{
    micros_tinker,
    millis_tinker,
} };

void setup() {
    tinker.setup_PF_tinker();
}

void loop() {
}

bool micros_tinker(int p, int &v)
{
    if( iot::Tinker::AR != v ){
        return false; // Ignore requests but AnalogReads.
    }
    
    auto tinker_pin = static_cast<iot::TinkerPin>(p);
    switch ( tinker_pin ) {
        case iot::TinkerPin::a5:
        case iot::TinkerPin::a6: // DAC
        case iot::TinkerPin::a7: // WKP
            v = micros();
            return true; // Tinker request was handled.
    
        default:
            return false; // Tinker request was not handled.
    }
};

bool millis_tinker(int p, int &v)
{
    if( iot::Tinker::AR != v ){
        return false; // Ignore requests but AnalogReads.
    }
    
    auto tinker_pin = static_cast<iot::TinkerPin>(p);
    switch ( tinker_pin ) {
        case iot::TinkerPin::a0:
        case iot::TinkerPin::a1:
        case iot::TinkerPin::a2:
        case iot::TinkerPin::a3:
        case iot::TinkerPin::a4:
        case iot::TinkerPin::a5:
            v = millis();
            return true; // Tinker request was handled.
    
        default:
            return false; // Tinker request was not handled.
    }
};