clc
clear all

a = arduino('/dev/cu.usbmodem1411', 'Uno');

disp('START!');

for time = 1:1:10000
%     ir_receive = readDigitalPin(a, 'A0');
    ir_receive = readVoltage(a, 'A0');
    
    ir_receive = 5 - ir_receive;
    
    disp(ir_receive);
    
%     if ir_receive == 0
%         disp('DETECTED!');
%     else
%         disp('NONE');
%     end
    
    ir_receive_list(time) = ir_receive;
    
    plot(ir_receive_list, '*');
    hold on
    drawnow;
end
