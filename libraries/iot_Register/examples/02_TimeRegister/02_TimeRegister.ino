#include "iot_Register.h"

auto millis_reg = iot::Register(
    []() { return millis(); }
    );
auto micros_reg = iot::Register(
    []() { return micros(); }
    );
    
auto rb = iot::RegisterBank{ std::vector<iot::Register>{
    millis_reg, // 0
    micros_reg, // 1
}
};

void setup() {
    rb.setup_PF_reg();
}

void loop() {
}
