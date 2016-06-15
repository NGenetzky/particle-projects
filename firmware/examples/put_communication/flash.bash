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
files+=" put/put.* put/put_rgb.* put/put_serial* put/put_do*"
files+=" wreg/wreg.*"
files+=" node/node*"

# Example Files
files+=" examples/put_communication/put_communication.ino"
files+=" i2c/i2c_utility.* cmd/cmd_i2c*"
files+=" post/post.*"
################################################################################

particle flash $device $files
if [ $? -eq 1 ]; then # Check if compile failed
    exit 1
fi
################################################################################
# sleep 20s # 15s is enough to flash device
