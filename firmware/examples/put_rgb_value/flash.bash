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

# Example Files
files+=" examples/put_rgb_value/put_rgb_value.ino"
files+=" put/put.* put/put_rgb.*"
files+=" wreg/wreg.*"
files+=" node/node.*"
################################################################################

particle flash $device $files
if [ $? -eq 1 ]; then # Check if compile failed
    exit 1
fi
################################################################################
# sleep 20s # 15s is enough to flash device
