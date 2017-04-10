% Particle Demo at URSCAD
clear all
ACCESS_TOKEN = '';
echo on;

P = Particle(ACCESS_TOKEN);
L = P.Logan;

% L.reg.status0_color = Register(P.Logan, 6);
% c24b = L.reg.status0_color.get();
% c = [ ...
%     bi2de(bitget(c24b, 24:-1:17)), ...
%     bi2de(bitget(c24b, 16:-1:9)), ...
%     bi2de(bitget(c24b, 8:-1:1)) ...
%     ] / 255;
% 
% c1 = uisetcolor(c)
% c1_24b = intmax('uint32');
% bi2de(bitset(c1_24b, 24:-1:17, c1(1)*255));
% bi2de(bitset(c1_24b, 16:-1:9, c1(2)*255 ));
% bi2de(bitset(c1_24b, 8:-1:1, c1(3)*255 ));
% 
% L.reg.status0_color.set(c1);

%% Freenove
F = Freenove(L);
F.plot_joystick();

echo off;

