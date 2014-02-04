/************************************************************************
 * RedBot line follower using two sensors
 * ----------------------------------------
 * 
 * This is a simple script to make a RedBot follow a dark line 
 * using two line sensors
 *
 * You should set the lineContrast depending on the perceived contrast
 * between the line and the surface.
 * 
 * Tip: place the sensors as close to the surface as possible
 ************************************************************************/

#include <RedBot.h>
#include <SoftwareSerial.h>

RedBotMotor motor;

RedBotSensor lSen = RedBotSensor(2);
RedBotSensor rSen = RedBotSensor(6);

const int mainSpeed    = 200;
const int lineContrast = 300;

void setup() {
  Serial.begin(57600);
  Serial.println("Hello world!");
}

void loop() {  
  if (detectedContrast() < lineContrast) {
    goStraight();
  } 
  else if (lSen.read() > rSen.read()) {
    turnLeft();
  } 
  else {
    turnRight();
  }
}

int detectedContrast() {
  return abs(lSen.read() - rSen.read());
}

void goStraight() {
  Serial.println("STRAIGHT");
  motor.drive(mainSpeed);
}

void turnLeft() {
  Serial.println("LEFT!!!");
  motor.leftStop();
  motor.rightDrive(mainSpeed);
}

void turnRight() {
  Serial.println("RIGHT!!!");
  motor.rightStop();
  motor.leftDrive(mainSpeed);
}


