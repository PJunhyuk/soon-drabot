#include <Arduino.h>

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

class Ultrasonic {
	int trig_pin;
	int echo_pin;
	public:
		Ultrasonic(int TRIG_PIN, int ECHO_PIN);
        unsigned long getDistance();
};

#endif
