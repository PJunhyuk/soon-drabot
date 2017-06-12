clc
clear all

a = arduino('/dev/cu.usbmodem1421', 'Uno');

disp('START!');

configurePin(a, 'D5')

for time = 1:1:100
    writePWMVoltage(a, 'D5', 3);
end

disp('END!');

clear a;