#include <Arduino.h>
#include "Ultrasonic.h"
#include "IRController.h"
#include "Motor.h"
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include "Ultrasonic.h"
//#include "IRController.h"
//#include "Motor.h"

//  PINS
int TRIG_PIN = 8; // ultrasonic
int ECHO_PIN = 9; // ultrasonic

int RECV1_PIN = A0; // IR
int RECV2_PIN = A1; // IR
int RECV3_PIN = A2; // IR
int RECV4_PIN = A3; // IR
int RECV5_PIN = A4; // IR

int A1_PIN = 10; // motor
int A2_PIN = 11; // motor
int B1_PIN = 6;  // motor
int B2_PIN = 5;  // motor

// CONSTANTS
int WALL_THRESHOLD = 25;
int WALL_NEAR_THRESHOLD = 9;
int way_count = 0;

//  Set receiver
Ultrasonic sonic(TRIG_PIN,ECHO_PIN);
IRController ircon(RECV1_PIN,RECV2_PIN,RECV3_PIN,RECV4_PIN,RECV5_PIN);
Motor motor(A1_PIN,A2_PIN,B1_PIN,B2_PIN);

unsigned long sonic_distance;
unsigned long time;
int stage = 0;
int ref_time = 0;
bool switchMotors = 1;
int fastMotor = 1;

void setup() {
    Serial.begin(9600);
}

void loop() {
    time = millis();
    sonic_distance = sonic.getDistance();

    switch (stage) {
        case 0:
            if (time % 200 > 100) {
                motor.setMotor(100,-100);
            } else {
                motor.setMotor(50,-50);
            }
            if (sonic_distance <= WALL_THRESHOLD && sonic_distance > 0) {
                stage++;
            } 
            break;
        case 1:
            motor.setMotor(100,100);
            if (sonic_distance <= WALL_NEAR_THRESHOLD) {
                stage++;
            }
            break;
        case 2:
            if (time % 200 > 100) {
                motor.setMotor(255,-255);
            } else {
                motor.setMotor(50,-50);
            }
            break;
        default:
            motor.setMotor(0,0);
            break;
    }

    Serial.println((String)"{\"stage\": " + stage + ", \"sonic_distance\": " + sonic_distance + "}");

    delay(100);
}
