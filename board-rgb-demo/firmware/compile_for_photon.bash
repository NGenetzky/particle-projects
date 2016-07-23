#!/usr/bin/env bash
type=${1?"Specify the device type as first arg."}
particle compile $type ./ --saveTo firmware.bin
