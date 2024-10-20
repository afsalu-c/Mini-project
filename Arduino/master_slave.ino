 #include <Wire.h>

#define SLAVE_ADDRESS 0x04

const int trigPin = 9;
const int echoPin = 10;
const int motorPin1 = 2; // Motor pin 1
const int motorPin2 = 3; // Motor pin 2
const int motorPin3 = 4; // Motor pin 3
const int motorPin4 = 5; // Motor pin 4
const int enablePin1 = 7; // Enable pin for motor 1,2
const int enablePin2 = 6; // Enable pin for motor 3,4

int received=0;

long duration;
int distance;
bool objectDetected = false;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);

  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
//  // Initially, keep motors enabled
//  digitalWrite(enablePin1, HIGH);
//  digitalWrite(enablePin2, HIGH);
}

void loop() {
//  if (!objectDetected) {
//    measureDistance();
//    moveForward();
//  } else {
//    stopMotors();
    measureDistance();
    if (distance > 10) {
      moveForward();
    } else {
      while(received==0){
      stopMotors();
      }
      
      moveBackward();
      delay(100);
      moveRight();
      delay(1000);
      moveLeft();
      delay(1000);
    }
  }
 
void receiveEvent(int howMany) {
  while (Wire.available()) {
    int received = Wire.read();
  }
}

void measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
}

void requestEvent() {
  if (objectDetected) {
    Wire.write(-1); // Signal Raspberry Pi that object is detected
  } else {
    Wire.write(distance);
  }
}

void moveForward() {
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void moveBackward() {
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void moveLeft() {
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void moveRight() {
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void stopMotors() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}
