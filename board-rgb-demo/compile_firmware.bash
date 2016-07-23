#!/usr/bin/env bash
type=${1?"Specify the device type as first arg."}
particle compile $type ./firmware --saveTo "$type""_firmware.bin"
