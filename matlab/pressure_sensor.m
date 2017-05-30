clc
clear all

a = arduino('/dev/cu.usbmodem1411', 'Uno');

disp('START!');

for time = 1:1:10000
    pressure_input = readVoltage(a, 'A0');
    disp(pressure_input);
    
    pressure_list(time) = pressure_input;
    
    plot(pressure_list, '*');
    hold on
    drawnow;
end
