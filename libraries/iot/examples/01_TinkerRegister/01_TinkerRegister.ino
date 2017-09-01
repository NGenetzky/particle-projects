#include "iot.h"

////////////////////////////////////////////////////////////////////////////////
// DigitalPort
//
auto d7_out = iot::Pin{D7, OUTPUT};
auto led = iot::DigitalPin{d7_out};
auto dport = iot::DigitalPort{ std::vector<iot::DigitalPin>{
    led // 0
}
};

auto dport_reg = iot::RegisterFactory(dport);
auto dport_tinker = iot::TinkerDigitalFactory(dport);
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Time
//
auto millis_reg = iot::Register(
    []() { return millis(); }
    );
auto micros_reg = iot::Register(
    []() { return micros(); }
    );
    
auto millis_tinker = iot::TinkerAnalogFactory(millis_reg, iot::TinkerPin::a1);
auto micros_tinker = iot::TinkerAnalogFactory(micros_reg, iot::TinkerPin::a0);
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LEDStatus
//
auto status0 = LEDStatus{};

auto status0_color = iot::RegisterFactory(status0);
auto status0_r = iot::RegisterFactory(status0, iot::LEDStatusRegister::red);
auto status0_g = iot::RegisterFactory(status0, iot::LEDStatusRegister::green);
auto status0_b = iot::RegisterFactory(status0, iot::LEDStatusRegister::blue);

auto status0_r_tinker = iot::TinkerAnalogFactory(status0_r, iot::TinkerPin::a4);
auto status0_g_tinker = iot::TinkerAnalogFactory(status0_g, iot::TinkerPin::a5);
auto status0_b_tinker = iot::TinkerAnalogFactory(status0_b, iot::TinkerPin::a6);
auto status0_b_tinker2 = iot::TinkerAnalogFactory(status0_b, iot::TinkerPin::a7);
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// RegisterBank
//
auto rb = iot::RegisterBank{ std::vector<iot::Register>{
    micros_reg, // 0
    millis_reg, // 1
    dport_reg, // 2
    status0_color, // 3
    status0_r, // 4
    status0_g, // 5
    status0_b, // 6
}
};
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Tinker
//
auto tinker = iot::Tinker{ std::vector<iot::TinkerFunction>{
    // DR and DW
    dport_tinker,
    // AR
    millis_tinker,
    micros_tinker,
    // AR and AW
    status0_r_tinker,
    status0_g_tinker,
    status0_b_tinker,
    status0_b_tinker2
} };
//
////////////////////////////////////////////////////////////////////////////////

void setup() {
    dport.setup();
    status0.setActive();
    
    tinker.setup_PF_tinker();
}

void loop() {
};

