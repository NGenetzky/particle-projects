#!/usr/bin/env bash
# type=${1?"Specify the device type as first arg."}
type="photon"
particle compile $type ./ --saveTo firmware.bin
