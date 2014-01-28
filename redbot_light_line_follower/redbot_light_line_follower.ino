/************************************************************************
 RedBot light follower using line sensors
 ----------------------------------------
 
 This is a simple script to make a RedBot follow a light projected on the
 floor. It uses line sensors, which are not really thought for following
 light, but for following lines, but that's what I had for a start :)
 
 Just make sure you place your sensors on the front and quite apart one
 from the other.

************************************************************************/

#include <RedBot.h>
#include <SoftwareSerial.h>

RedBotMotor motor;

RedBotSensor lSen = RedBotSensor(2);
RedBotSensor cSen = RedBotSensor(3);
RedBotSensor rSen = RedBotSensor(6);

void setup() {
  Serial.begin(57600);
  Serial.println("Hello world!");
}

void loop() {  
  if (lightDifference() < 50) {
    goStraight();
  } 
  else if (lSen.read() < rSen.read()) {
    goLeft();
  } 
  else {
    goRight();
  }

  delay(100);
}

int lightDifference() {
  return abs(lSen.read() - rSen.read());
}

void goStraight() {
  Serial.println("STRAIGHT");
  motor.drive(100);
}

void goLeft() {
  Serial.println("LEFT!!!");
  motor.rightDrive(255);
  motor.leftStop();
}

void goRight() {
  Serial.println("RIGHT!!!");
  motor.rightStop();
  motor.leftDrive(255);
}


