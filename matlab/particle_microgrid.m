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

Device = P.Parker % Logan is the name of one of my devices.

% A digital input can be controlled (also connected to led)
Device.do.led_on();


% A list of all the commands this device understands.
rv_get_cmds = Device.get_cmds();
cmds = rv_get_cmds.result

rv_get_soc = Device.get_soc();
soc = rv_get_soc.result

rv_get_battery_bank = Device.get_battery_bank();
battery_bank = rv_get_battery_bank.result

rv_get_gen_schedule = Device.get_gen_schedule();
gen_schedule = rv_get_gen_schedule.result

rv_get_inv_schedule = Device.get_inv_schedule();
inv_schedule = rv_get_inv_schedule.result

% A struct which allows functions to easily be called.
do = Device.do


Device.do.led_off();

echo off
