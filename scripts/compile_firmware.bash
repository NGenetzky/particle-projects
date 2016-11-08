#!/usr/bin/env bash
type=${1?"Specify the device type as first arg."}
cd ./firmware/
particle compile $type ./ --saveTo "../$type""_firmware.bin"
