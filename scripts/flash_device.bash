#!/usr/bin/env bash
device=${1?"Specify the device as first arg."}
cd ./firmware/
particle flash $device ./
