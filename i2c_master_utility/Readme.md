
# I2C Master Utility

Will run "I2C_scan()" every 2 seconds.

## I2C_scan()

Function from i2c_utility.h that prints all I2C slaves on bus.

Sample data sent to logs (`https://console.particle.io/logs`):
```
I2C.SCAN32,0,0,0,0,0,0,0,0,0November 1st at 2:30:24 pmParker
{"data":"32,0,0,0,0,0,0,0,0,0","ttl":"60","published_at":"2016-11-01T19:30:24.008Z","coreid":"45002e000747343232363230","name":"I2C.SCAN"}
I2C.setupreset;begin(Master)November 1st at 2:30:23 pmParker
{"data":"reset;begin(Master)","ttl":"60","published_at":"2016-11-01T19:30:23.960Z","coreid":"45002e000747343232363230","name":"I2C.setup"}
```
