#!/usr/bin/env bash
device=${1?"Specify the device as first arg."}
particle flash $device .
