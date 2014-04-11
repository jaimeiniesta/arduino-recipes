/************************************************************************
 * RedBot light follower using line sensors
 * ----------------------------------------
 * 
 * This is a simple script to make a RedBot follow a light projected on the
 * floor. It uses line sensors, which are not really thought for following
 * light, but for following lines, but that's what I had for a start :)
 * 
 * Just make sure you place your sensors on the front and quite apart one
 * from the other.
 * 
 * Some lessons learned building this:
 *
 *   - to turn, rather than braking a wheel, make them run in opposite
 *     directions. This way it can recover from crashing into walls
 *
 *   - running at a moderate speed makes it easier to turn due to
 *     less inertia. Well, as in real life :)
 *
 *   - you don't need a delay inside the loop
 * 
 ************************************************************************/

#include <RedBot.h>

RedBotMotor motor;

RedBotSensor lSen = RedBotSensor(2);
RedBotSensor cSen = RedBotSensor(3);
RedBotSensor rSen = RedBotSensor(6);

int mainSpeed = 150;

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
}

int lightDifference() {
  return abs(lSen.read() - rSen.read());
}

void goStraight() {
  Serial.println("STRAIGHT");
  motor.drive(mainSpeed);
}

void goLeft() {
  Serial.println("LEFT!!!");
  motor.rightDrive(mainSpeed);
  motor.leftDrive(-mainSpeed);
}

void goRight() {
  Serial.println("RIGHT!!!");
  motor.rightDrive(-mainSpeed);
  motor.leftDrive(mainSpeed);
}


