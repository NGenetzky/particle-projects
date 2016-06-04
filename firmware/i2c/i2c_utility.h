#pragma once

// Setup
int I2C_setup_master();
int I2C_setup_slave(int my_address);
void I2C_on_receive_default(int bytesReceived);

// Utility
void I2C_end_transmission_debug(int ret_code);
int I2C_scan();