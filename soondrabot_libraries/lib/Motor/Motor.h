#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
    int A1_pin;
    int A2_pin;
    int B1_pin;
    int B2_pin;
public:
    Motor(int A1_PIN, int A2_PIN, int B1_PIN, int B2_PIN);
    void setMotor(int left, int right);
};

#endif
