int IN_motor_left_forward = 6;
int IN_motor_left_backward = 5;
int IN_motor_right_forward = 11;
int IN_motor_right_backward = 10;
int IN_line_finder = 7;

void setup() {
  // put your setup code here, to run once:

  pinMode(IN_motor_right_backward , OUTPUT);
  pinMode(IN_motor_right_forward , OUTPUT);
  pinMode(IN_motor_left_backward , OUTPUT);
  pinMode(IN_motor_left_forward , OUTPUT);

  pinMode(IN_line_finder, INPUT);

  Serial.begin(9600);
}

int line_finded = 0;
int rotate_finished = 0;
int rotated_time = 0;
int motor_power_left;
int motor_power_right;

void loop() {
  // put your main code here, to run repeatedly:

  if (line_finded < 3) {
//    if (rotate_finished == 0) {
//      // @TODO: rotate and measure distance using ultrasonic sensor, without moving
//    
//      motor_power_left = 100;
//      motor_power_right = -100;
//
//      rotated_time = rotated_time + 1;
//
//      if (rotated_time > 400) {
//        rotate_finished = 1;
//      }
//    } else {
  
      // @TODO: 
  
      motor_power_left = 200;
      motor_power_right = 200;
    
      if (HIGH == digitalRead(IN_line_finder)) {
        line_finded = line_finded + 1;
      } else {
        line_finded = 0;
      }
    
      if (line_finded >= 2) {
        motor_power_left = 0;
        motor_power_right = 0;
        analogWrite(IN_motor_left_forward, 0);
        analogWrite(IN_motor_left_backward, 0);
        analogWrite(IN_motor_right_forward, 0);
        analogWrite(IN_motor_right_backward, 0);
      }
//    }
  } else {
    Serial.println("LINE! quit");
  }

  if (motor_power_left > 0) {
    analogWrite(IN_motor_left_forward, motor_power_left);
  } else {
    analogWrite(IN_motor_left_backward, - motor_power_left);
  }

  if (motor_power_right > 0) {
    analogWrite(IN_motor_right_forward, motor_power_right);
  } else {
    analogWrite(IN_motor_right_backward, - motor_power_right);
  }

//  Serial.print(line_finded);
//  Serial.print(" / ");
//  Serial.println(motor_power_right);
  Serial.println(line_finded);
}
