#include "Ultrasonic.h"
#include "IRController.h"
#include "Motor.h"

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

int LINE1_PIN = 4; // line detector
int LINE2_PIN = 7; // line detector

// CONSTANTS
int WALL_THRESHOLD = 25;
int WALL_NEAR_THRESHOLD = 9;
int RETREAT_LOOP_COUNT  = 5;


//  Set up sensors
Ultrasonic sonic(TRIG_PIN,ECHO_PIN);
IRController ircon(RECV1_PIN,RECV2_PIN,RECV3_PIN,RECV4_PIN,RECV5_PIN);
Motor motor(A1_PIN,A2_PIN,B1_PIN,B2_PIN);

unsigned long sonic_distance;
unsigned long time;
int stage = 0;
int last_stage = 0;
int loop_number = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LINE1_PIN,OUTPUT);
    pinMode(LINE2_PIN,OUTPUT);
}

int reference_loop = 0;
int set_timer(goal_loop) {
    if (reference_loop == 0) {
        reference_loop = loop_number;
    }
    if (loop_number - reference_loop >= goal_loop) {
        return 1;
    } else {
        return 0;
    }
}

void loop() {
    sonic_distance = sonic.getDistance();

    if (digitalRead(LINE1_PIN) == HIGH) {
        last_stage = stage;
        stage = 98;
    } else if (digitalRead(LINE2_PIN) == HIGH) {
        last_stage = stage;
        stage = 99;
    }

    switch (stage) {
        case 0: // search for wall
            if (loop_number % 2 == 0) {
                motor.setMotor(100,-100);
            } else {
                motor.setMotor(50,-50);
            }
            if (sonic_distance <= WALL_THRESHOLD && sonic_distance > 0) {
                stage++;
            } 
            break;
        case 1: // head for motor
            motor.setMotor(100,100);
            if (sonic_distance <= WALL_NEAR_THRESHOLD && sonic_distance > 0) {
                stage++;
            }
            break;
        case 2: // search IR detector
            if (loop_number % 2 == 0) {
                motor.setMotor(100,-100);
            } else {
                motor.setMotor(50,-50);
            }
            if (ircon.receive(0) == 1) {
                stage++;
            }
            break;
        case 3: // charge forward
            motor.setMotor(100,100);
            break;
        case 4: // retreat backward
            if (set_timer()) {
            }
            motor.setMotor(-100,-100);
            
            if (time - time_backward >= total_time/2) {
                stage = 0;
            }
            break;
        case 98:
            motor.setMotor(-100,-100);
            break;
        case 99:
            motor.setMotor(100,100);
            break;
        default:
            motor.setMotor(0,0);
            break;
    }

    Serial.println((String)"{\"stage\": " + stage + ", \"sonic_distance\": " + sonic_distance + "}");

    loop_number++;
    delay(100);
}
