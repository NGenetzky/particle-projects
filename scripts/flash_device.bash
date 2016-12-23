#!/usr/bin/env bash
device=${1?"Specify the device as first arg."}

firmware_dir=./firmware
if [ -d $firmware_dir ]; then
cd $firmware_dir
fi
#  [ -d $firmware_dir ] || { echo "Can't find $firmware_dir"; exit 1; }

particle flash $device ./
