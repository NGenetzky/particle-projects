#pragma once
#include "application.h" // Required for "String".

// Setup
int I2C_setup_master();
int I2C_setup_slave(int my_address);
void I2C_on_receive_default(int bytesReceived);

// Utility
void I2C_end_transmission_debug(int ret_code);
int PF_i2c_scan(String args);
int I2C_scan();
