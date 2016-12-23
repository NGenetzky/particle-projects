#!/usr/bin/env bash
type=${1?"Specify the device type as first arg."}

firmware_dir=./firmware
if [ -d $firmware_dir ]; then
cd $firmware_dir
fi
# { echo "Can't find $firmware_dir"; exit 1; }


particle compile $type ./ --saveTo "../$type""_firmware.bin"
