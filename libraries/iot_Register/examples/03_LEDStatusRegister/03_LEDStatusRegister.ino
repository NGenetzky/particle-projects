#include "iot_Register.h"

auto status0 = LEDStatus{};
auto status0_color = iot::RegisterFactory(status0);
auto status0_r = iot::RegisterFactory(status0, iot::LEDStatusRegister::red);
auto status0_g = iot::RegisterFactory(status0, iot::LEDStatusRegister::green);
auto status0_b = iot::RegisterFactory(status0, iot::LEDStatusRegister::blue);
    
auto rb = iot::RegisterBank{ std::vector<iot::Register>{
    status0_color, // 0
    status0_r, // 1
    status0_g, // 2
    status0_b, // 3
}
};

void setup() {
    status0.setActive();
    rb.setup_PF_reg();
}

void loop() {
}
