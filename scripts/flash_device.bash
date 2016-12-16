#!/usr/bin/env bash
device=${1?"Specify the device as first arg."}

firmware_dir=./firmware
[ -d $firmware_dir ] || { echo "Can't find $firmware_dir"; exit 1; }

particle flash $device ./
