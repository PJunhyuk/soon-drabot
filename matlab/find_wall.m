clc
clear all

a = arduino('/dev/cu.usbmodem1421', 'Uno', 'Libraries', 'JRodrigoTech/HCSR04');
sensor = addon(a, 'JRodrigoTech/HCSR04', 'D8', 'D9');
% trig, echo

for time = 1:1:10000
    if mod(time, 4) < 2
        writePWMVoltage(a, 'D6', 5); % right - front
        writePWMVoltage(a, 'D11', 5); % left - back
        disp('front');
    else
        writePWMVoltage(a, 'D6', 0); % right - front
        writePWMVoltage(a, 'D11', 0); % left - back
%         writePWMVoltage(a, 'D10', 5); % left - front
%         writePWMVoltage(a, 'D5', 5); % right - back
        disp('back');
    end

    ultrasonic_distance = 100 * readDistance(sensor); % Convert meter to centimeter

    if ultrasonic_distance == 51 % max == 51
        clear sensor
        sensor = addon(a, 'JRodrigoTech/HCSR04', 'D8', 'D9');
        ultrasonic_distance = 100;
    end
    
    ultrasonic_distance_list(time) = ultrasonic_distance;
    
    plot(ultrasonic_distance_list, '*');
    hold on
    drawnow;
end

clear sensor
clear a
