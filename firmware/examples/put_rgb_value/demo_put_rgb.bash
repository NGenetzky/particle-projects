#!/usr/bin/env bash

trap 'echo ">> $BASH_COMMAND"' DEBUG
if [ "$1" ]; then
    device=$1 # First argument should be nice to flash.
else
    exit 1;
fi
