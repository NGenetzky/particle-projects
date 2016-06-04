
#include "cmd.h"
#include "cmd_i2c.h"
#include "i2c_utility.h"

const int CMD_I2C_START = 750;

static int i2c_slave2(){
    return I2C_setup_slave(2);
}

static int i2c_slave4(){
    return I2C_setup_slave(4);
}

static int i2c_slave6(){
    return I2C_setup_slave(6);
}

int cmd_i2c_setup(){
    int i=CMD_I2C_START;
    cmd_set(i++, "i2c_master", I2C_setup_master);
    cmd_set(i++, "i2c_scan", I2C_scan);
    cmd_set(i++, "i2c_slave2", i2c_slave2);
    cmd_set(i++, "i2c_slave4", i2c_slave4);
    cmd_set(i++, "i2c_slave6", i2c_slave6);
    return i-CMD_I2C_START;
}
