#!/usr/bin/env bash
type=${1?"Specify the device type as first arg."}

firmware_dir=./firmware
[ -d $firmware_dir ] || { echo "Can't find $firmware_dir"; exit 1; }
cd $firmware_dir

particle compile $type ./ --saveTo "../$type""_firmware.bin"
