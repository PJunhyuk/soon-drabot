#include <IRremote.h>

int IN_motor_left_forward = 10;
int IN_motor_left_backward = 11;
int IN_motor_right_forward = 6;
int IN_motor_right_backward = 5;

const int trigPin = 8;
const int echoPin = 9;

int IN_line_finder_front = 7;
int IN_line_finder_back = 4;
int line_finded_front = 0;
int line_finded_back = 0;
int line_on_front = 0;
int line_on_back = 0;

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);

int WALL_THRESHOLD = 25;
int WALL_NEAR_THRESHOLD = 7;
int way_count = 0;

decode_results results;

void setup() {
  // put your setup code here, to run once:

  pinMode(IN_motor_right_backward , OUTPUT);
  pinMode(IN_motor_right_forward , OUTPUT);
  pinMode(IN_motor_left_backward , OUTPUT);
  pinMode(IN_motor_left_forward , OUTPUT);

  pinMode(IN_line_finder_front, INPUT);
  pinMode(IN_line_finder_back, INPUT);

  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver

  digitalWrite(trigPin, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

int line_finded = 0;
int stage_number = 0;
int rotated_time = 0;
int irrecv_variable = 0;
int quit_variable = 0;
int second_time = 0;

int period = 0;
int minperiod = 0;
int mindistance = 150;

int near_count = 0;

long ultrasonic_distance;

void setMotor(int left, int right) {
  if (left >= 0) {
    analogWrite(IN_motor_left_forward, left);
    analogWrite(IN_motor_left_backward, 0);
  } else {
    analogWrite(IN_motor_left_forward, 0);
    analogWrite(IN_motor_left_backward, -left);
  }
  if (right >= 0) {
    analogWrite(IN_motor_right_forward, right);
    analogWrite(IN_motor_right_backward, 0);
  } else {
    analogWrite(IN_motor_right_forward, 0);
    analogWrite(IN_motor_right_backward, -right);
  }
}

long getUltrasonicDistance() {
  long distance;
  long duration;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int tries = 0;
  do {
    period++;
    duration = pulseIn( echoPin, HIGH, 50000);
    distance = 0.034 * duration / 2;
    if ( duration == 0 ) {
      delay(100);
      pinMode(echoPin, OUTPUT);
      digitalWrite(echoPin, LOW);
      pinMode(echoPin, INPUT);
    }
  } while (duration == 0 && ++tries < 2);

  return distance;
}

void loop() {
  // put your main code here, to run repeatedly:

  if (HIGH == digitalRead(IN_line_finder_front)) {
    line_finded_front = line_finded_front + 1;
    if (line_finded_front == 2) {
      line_on_front = 1;
    }
  } else {
    line_finded_front = 0;
    line_on_front = 0;
  }

  if (line_on_front == 1) {
    Serial.println("LINE FRONT!");
    setMotor(-255, -255);
    delay(300);
  }

//////

  if (HIGH == digitalRead(IN_line_finder_back)) {
    line_finded_back = line_finded_back + 1;
    if (line_finded_back == 2) {
      line_on_back = 1;
    }
  } else {
    line_finded_back = 0;
    line_on_back = 0;
  }

  if (line_on_back == 1) {
    Serial.println("LINE BACK!");
    setMotor(255, 255);
    delay(300);
  }

////////

  if (quit_variable == 1) {
    setMotor(0, 0);
    Serial.println("QUIT!");
    delay(10000);
  } else {
    if (stage_number == 0) {
//      setMotor(150, 177);
      setMotor(-255, -255);
//      setMotor(100, -118);
//      delay(100);
//      setMotor(0, 0);
//      delay(100);
//
//      // Ultrasonic Sensor
//      ultrasonic_distance = getUltrasonicDistance();
//      Serial.println(ultrasonic_distance);
//      if (ultrasonic_distance != 0 && ultrasonic_distance <= WALL_THRESHOLD) {
//        way_count++;
//      }
//      if (way_count > 3) {
//        stage_number = 1;
//        Serial.println("Going to Stage 1");
//      }
//
//      rotated_time = rotated_time + 1;
    } else if (stage_number == 1) {
      // Approach Wall
      setMotor(100, 118);
//      setMotor(150, 177);
      delay(100);
      setMotor(0, 0);
      delay(100);

      ultrasonic_distance = getUltrasonicDistance();
      Serial.println(ultrasonic_distance);
      if (ultrasonic_distance != 0 && ultrasonic_distance <= WALL_NEAR_THRESHOLD) {
        near_count++;
      }
      if (near_count >= 3) {
        stage_number = 2;
        Serial.println("Going to Stage 2");
      }

    
    
    } else if (stage_number == 2) {
      // Find Block Direction using IR
      setMotor(100, -118);
      delay(100);
      setMotor(0, 0);
      delay(100);

//      if (irrecv.decode(&results)) {
//        Serial.println(results.value, HEX);
//        irrecv_variable = irrecv_variable + 1;
//        if (irrecv_variable > 1) {
//          stage_number = 3;
//          irrecv_variable = 0;
//          Serial.println("Going to Stage 3");
//        }
//        irrecv.resume(); // Receive the next value
//      }
//      delay(10);
    } else if (stage_number == 3) {
      //  Attack!
      setMotor(238, 255);
      Serial.println(digitalRead(IN_line_finder_front));
      if (HIGH == digitalRead(IN_line_finder_front)) {
        line_finded = line_finded + 1;
      } else {
        line_finded = 0;
      }
      if (line_finded > 5) {
        stage_number = 4;
        Serial.println("Going to Stage 4");
      }
    } else if (stage_number == 4) {
      // Retreat
      setMotor(-200,-200);
      delay(500);
      setMotor(0, 0);
      delay(5000);
      
      second_time = 1;
      stage_number = 2;
      Serial.println("Going to Stage 2");
    } else {
      // Follow the line
      if (HIGH == digitalRead(IN_line_finder_front)) {
        setMotor(230,255);
      } else {
        setMotor(0,255);
      }
    }



  }
}
