#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int TRIG_PIN, int ECHO_PIN) {
    trig_pin = TRIG_PIN;
    echo_pin = ECHO_PIN;
    pinMode(trig_pin,OUTPUT);
    pinMode(echo_pin,INPUT);
    digitalWrite(trig_pin, LOW);
}

unsigned long Ultrasonic::getDistance() {
    unsigned long distance;
    unsigned long duration;

    //  send ultrasonic pulse
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    //  receive pulse
    duration = pulseIn(echo_pin, HIGH);
    distance = 0.034 * duration /2;

    //  reset echo pin if timeout
    if ( duration == 0 ) {
        pinMode(echo_pin,OUTPUT);
        digitalWrite(echo_pin,LOW);
        pinMode(echo_pin,INPUT);
    }

    return distance;
}
