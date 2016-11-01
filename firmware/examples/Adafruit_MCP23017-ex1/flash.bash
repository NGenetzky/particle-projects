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

# Libraries
files+=" lib/Adafruit_MCP23017/*"

# Example Files
files+=" examples/Adafruit_MCP23017-ex1/toggle.ino"
################################################################################

particle flash $device $files
if [ $? -eq 1 ]; then # Check if compile failed
    exit 1
fi
################################################################################
# sleep 20s # 15s is enough to flash device
