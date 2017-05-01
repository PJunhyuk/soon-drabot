const int trigPin = 9;
const int echoPin = 8;
int period = 0;
int minperiod = 0;
int mindistance = 150;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(trigPin, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    long duration, inches, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  
  // ... this is the reading loop
    long pulseDuration;
    long distance;
    int tries = 0;
    do
    {
        period ++;
        duration = pulseIn( echoPin, HIGH, 50000);
        distance = 0.034 * duration / 2;
        if ( duration == 0 ) {
            delay(100);
            pinMode(echoPin, OUTPUT);
            digitalWrite(echoPin, LOW);
            delay(100);
            pinMode(echoPin, INPUT);
        }
    } while (duration == 0 && ++tries < 3);
    if (distance < mindistance && distance != 0){
      mindistance = distance;
      minperiod = period;
    }
  Serial.println(mindistance);
  Serial.println(minperiod);
  delay(100);
}