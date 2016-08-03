% Particle Demo
echo on
ACCESS_TOKEN = '';

% Pressing 'y' will reload the struct of data.
if exist('P', 'var')
    a = input('Fetch from Cloud? (y/n)', 's');
    if strcmpi(a,'y')
        P = Particle(ACCESS_TOKEN);
    end
else
    P = Particle(ACCESS_TOKEN);
end
clear a;

Device = P.Logan % Logan is the name of one of my devices.

% The RGB led can be controlled
Device.do.red();
pause(1);
Device.do.yellow();
pause(1);
Device.do.green();
pause(1);

% A digital input can be controlled (also connected to led)
Device.do.led_on();

% A list of all the commands this device understands.
rv_get_cmds = Device.get_cmds();
cmds = rv_get_cmds.result;

% A struct which allows functions to easily be called.
do = P.Logan.do

% A string of csv data. Contains timestamp, analog values, and digital
% values.
rv_get_sc_remote = Device.get_sc_remote();
sc_remote = rv_get_sc_remote.result

Device.do.led_off();


% Done
Device.do.release(); % release rgb
pause(1);


echo off
