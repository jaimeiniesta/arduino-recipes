/************************************************************************
 * RedBot proximity sensor
 *
 * Using two Infrared Proximity Sensors on front to find a way around the house
 * https://www.sparkfun.com/products/242
 ************************************************************************/

// Include the RedBot library which abstracts the use of the motor and other useful things
#include <RedBot.h>

// Declare the motor and the sensors
RedBotMotor  motor;
RedBotSensor leftSensor  = RedBotSensor(0);
RedBotSensor rightSensor = RedBotSensor(5);

// Define the speeds. Due to variations in the performance of motors, we'll use slightly
// different speeds for the left and right motors so that it moves straight.
const int leftForwardSpeed  = 180;
const int rightForwardSpeed = 200;

// It will only go backwards as a escape sequence, so we don't care about different left and right speeds.
const int backwardsSpeed    = 180;

// This defines the proximity value (the higher, the nearer an object is detected) where we determine
// that we've come too close and it's time to go backwards. Calibrate this according to your sensors.
const int tooCloseProximity = 400;

// We'll use this value to determine if we have a clear path ahead, that is, if the difference between both
// sensors is under this value, we can go forward; else, we'll go to the side with more space ahead
const int tolerance = 100;

// Set it all up, using the serial port to log messages
void setup() {
  Serial.begin(9600);
  Serial.println("Hello world!");
  delay(10000);
}

// Main loop. Make it go forward if there's a clear path ahead, if not, go to the side with more space,
// or go backwards if we've come too close
void loop() {
  if (clearPath()) {
    goForward(100);
  } else if (tooClose()) {
    escapeSequence();
  } else if (leftProximity() < rightProximity()) {
    turnLeft(25);
  } else {
    turnRight(25);
  } 
}

// Returns an int between 0 and 1023, the bigger, the closer an object is
int leftProximity() {
  leftSensor.read();
}

// Returns an int between 0 and 1023, the bigger, the closer an object is
int rightProximity() {
  rightSensor.read();
}

// We could use min(leftProximity, rightProximity) here
boolean tooClose() {
  if ((leftProximity() > tooCloseProximity) || (rightProximity() > tooCloseProximity)) {
    return(true);
  } else {
    return(false);
  }
}

boolean clearPath() {
  if (abs(leftProximity() - rightProximity()) < tolerance) {
    return(true);
  } else {
    return(false);
  }
}

void goForward(int milliseconds) {
  Serial.println("FORWARD");
  motor.leftDrive(leftForwardSpeed);
  motor.rightDrive(rightForwardSpeed);
  
  delay(milliseconds);
}

void turnLeft(int milliseconds) {
  Serial.println("LEFT!!!");
  motor.leftStop();
  motor.rightDrive(backwardsSpeed);
  
  delay(milliseconds);
}

void turnRight(int milliseconds) {
  Serial.println("RIGHT!!!");
  motor.rightStop();
  motor.leftDrive(backwardsSpeed);
  
  delay(milliseconds);
}


// Turn backwards towards the site with more space ahead
void escapeSequence() {
  Serial.println("BACKWARDS");
  
  if (leftProximity() < rightProximity()) {
    motor.leftDrive(-255);
    motor.rightDrive(-100);
  } else {
    motor.leftDrive(-100);
    motor.rightDrive(-255);
  }
  
  delay(250);
}



