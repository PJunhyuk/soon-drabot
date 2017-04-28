int signalPin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(signalPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (HIGH == digitalRead(signalPin))
    Serial.println("black");
  else Serial.println("white");
}
