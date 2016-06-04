#!/usr/bin/env bash

trap 'echo ">> $BASH_COMMAND"' DEBUG
if [ "$1" ]; then
    device=$1 # First argument should be nice to flash.
else
    exit 1;
fi

# The do function can be called with the uid of the command or the name of the command.
particle call $device "do" "red"
sleep 2s

particle call $device "do" "yellow"
sleep 2s

particle call $device "do" "green"
sleep 2s

particle call $device "do" "white" # white
sleep 2s

particle call $device "do" "red" # red
sleep 2s

particle call $device "do" "yellow" # yellow
sleep 2s

particle call $device "do" "lime" # lime
sleep 2s

particle call $device "do" "aqua" # aqua
sleep 2s

particle call $device "do" "blue" # blue
sleep 2s

particle call $device "do" "fuchsia" # fuchsia
sleep 2s

particle call $device "do" "release" # release
sleep 2s