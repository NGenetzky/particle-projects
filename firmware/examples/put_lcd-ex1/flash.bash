#!/usr/bin/env bash

trap 'echo ">> $BASH_COMMAND"' DEBUG
cd $(git rev-parse --show-cdup) # Always reference start in git root directory.
files=""
if [ "$1" ]; then
    device=$1 # First argument should be nice to flash.
else
    exit 1;
fi


# Common Base Files
cd firmware
files+=" cmd/cmd.*"
files+=" global/global.*"
files+=" board/* cmd/cmd_board.*"
files+=" rgb/* cmd/cmd_rgb.*"
files+=" logger/logger.*"
files+=" put/put.* put/put_rgb.* put/put_do*"
files+=" node/node.*"
files+=" node/node_var.*"
files+=" put/put_lcd.*"

# Libraries
files+=" lib/LiquidCrystal_I2C_Spark/*.h"
files+=" lib/LiquidCrystal_I2C_Spark/*.cpp"

# Example Files
files+=" examples/put_lcd-ex1/*.ino"
################################################################################

particle flash $device $files
if [ $? -eq 1 ]; then # Check if compile failed
    exit 1
fi
################################################################################
# sleep 20s # 15s is enough to flash device
