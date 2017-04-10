% Particle Demo at URSCAD
clear all
ACCESS_TOKEN = '';
echo on;

P = Particle(ACCESS_TOKEN);
L = P.Logan;
F = Freenove(L);

F.plot_joystick();

echo off;

