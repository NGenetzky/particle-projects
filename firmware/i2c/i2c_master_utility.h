#pragma once
#include "application.h"
#include <vector>

namespace i2c_master {
    int setup();
    int open(uint8_t new_slave);
    int write(std::vector<uint8_t> d);
    std::vector<uint8_t> read(unsigned bytes_requested);
    void print_end_transmission_rv(int ret_code);
    int scan();
}
