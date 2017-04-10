% Particle Demo at URSCAD
clear all
ACCESS_TOKEN = '';
echo on;

P = Particle(ACCESS_TOKEN);
L = P.Logan;

L.reg.pot1 = Register(L, 2);
L.reg.pot2 = Register(L, 3);
L.reg.joyx = Register(L, 4);
L.reg.joyy = Register(L, 5);

Analog12bit = @(a12) (a12/(2.^12));

figure;
hold on;
freenove.plot = plot(0,0);
title('Joystick on Freenove board');
xlim([-0.5 0.5]);
ylim([-0.5 0.5]);

% Keep running until plot is closed.
while( isvalid(freenove.plot) )
    freenove.x = [0, Analog12bit( L.reg.joyx.get() )-0.5 ];
    freenove.y = [0, Analog12bit( L.reg.joyy.get() )-0.5 ];
    set(freenove.plot,'XData',freenove.x,'YData',freenove.y);
    drawnow
end

echo off;

