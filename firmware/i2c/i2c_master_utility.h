#pragma once

namespace i2c_master {
    int setup();
    void print_end_transmission_rv(int ret_code);
    int scan();
}
