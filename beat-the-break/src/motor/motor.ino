int IN_motor_left_forward = 11;
int IN_motor_left_backward = 10;
int IN_motor_right_backward = 5;
int IN_motor_right_forward = 6;

void setup() {
  // put your setup code here, to run once:

  pinMode(5 , OUTPUT);
  pinMode(6 , OUTPUT);
  pinMode(10 , OUTPUT);
  pinMode(11 , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int motor_power_left = 255;
  int motor_power_right = -255;

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
}
