% Matlab Serial communication
% Create class after motivation from:
% http://stackoverflow.com/questions/8847866/how-can-i-close-files-that-are-left-open-after-an-error
% Introduced on_receive event for async reads.
% http://www.mathworks.com/help/matlab/matlab_external/events-and-callbacks.html#bqgs5eb

home; clc; close all; clear;
instrreset

logan = SerialHandle('COM8', 'Logan');
%parker.fprintf('%s', 'Hello Parker');

%matt = SerialHandle('COM3', 'Matt');
%matt.fprintf('%s', 'Hello Matt');
