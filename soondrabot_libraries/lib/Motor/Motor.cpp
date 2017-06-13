#include "Motor.h"

Motor::Motor(int A1_PIN, int A2_PIN, int B1_PIN, int B2_PIN) {
    A1_pin = A1_PIN;
    A2_pin = A2_PIN;
    B1_pin = B1_PIN;
    B2_pin = B2_PIN;

    pinMode(A1_pin, OUTPUT);
    pinMode(A2_pin, OUTPUT);
    pinMode(B1_pin, OUTPUT);
    pinMode(B2_pin, OUTPUT);
}

void Motor::setMotor(int left, int right) {
    if (left >= 0) {
        analogWrite(A1_pin, left);
        analogWrite(A2_pin, 0);
    } else {
        analogWrite(A1_pin, 0);
        analogWrite(A2_pin, -left);
    }
    if (right >= 0) {
        analogWrite(B1_pin, right);
        analogWrite(B2_pin, 0);
    } else {
        analogWrite(B1_pin, 0);
        analogWrite(B2_pin, -right);
    }
}
