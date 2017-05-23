clc
clear all

a = arduino('/dev/cu.usbmodem1411', 'Uno', 'Libraries', 'JRodrigoTech/HCSR04');
sensor = addon(a, 'JRodrigoTech/HCSR04', 'D9', 'D8');

% ultrasonic_distance_list = zeros(1, 100); % Preallocation

for time = 1:1:10000
    ultrasonic_distance = 100 * readDistance(sensor); % Convert meter to centimeter

    if ultrasonic_distance == 51 % max == 51
        clear sensor
        sensor = addon(a, 'JRodrigoTech/HCSR04', 'D9', 'D8');
        ultrasonic_distance = 100;
    end
    
    ultrasonic_distance_list(time) = ultrasonic_distance;
    
    plot(ultrasonic_distance_list, '*');
    hold on
    drawnow;
end

clear sensor
clear a
