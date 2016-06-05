% Particle Demo
echo on
ACCESS_TOKEN = '';

P = Particle(ACCESS_TOKEN);

P.Matt.do.red()
pause(1);
P.Matt.do.yellow()
pause(1);
P.Matt.do.green()
pause(1);
P.Matt.do.release()
pause(1);

P.Matt.do.led_on()

pause(3);

P.Matt.do.led_off()

echo off