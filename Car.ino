const int leftMotorPin1 = 2; // connected to pin 7 on the H-bridge
const int leftMotorPin2 = 3; // connected to pin 2 on the H-bridge
const int rightMotorPin1 = 5;
const int rightMotorPin2 = 6;
const int enableLeftPin = 9;   // connected to pin 1 on the H-bridge
const int enableRightPin = 10;

const int pingPin = 8;
const int echoPin = 7;

void setup() {

  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(enableLeftPin, OUTPUT);
  pinMode(enableRightPin, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  // pull the enable pin LOW to start
  digitalWrite(enableLeftPin, LOW);
  digitalWrite(enableRightPin, LOW);

}

void loop() {

  // read the value of the on/off switch
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  long cm;
  ping(cm);

  if (cm < 10) {
    backGoLeft();
  }
  else {
    forward();
  }
}

void backGoLeft() {
    // PWM the enable pin to vary the speed
    // change the direction the motor spins by talking
    // to the control pins on the H-Bridge
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(enableRightPin,10);

    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    analogWrite(enableLeftPin, 50);

    
    delay(500);
}

void forward() {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(enableRightPin,250);

    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    analogWrite(enableLeftPin,250);
    
    delay(1);
}

void stay() {
    analogWrite(enableRightPin,0);
    analogWrite(enableLeftPin,0);
    delay(1);
}

long ping(long cm) {
    long duration;

    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    digitalWrite(echoPin, LOW);

    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    cm = microsecondsToCentimeters(duration);

    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    return cm;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
