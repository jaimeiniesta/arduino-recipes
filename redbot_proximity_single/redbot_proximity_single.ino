/************************************************************************
 * RedBot proximity sensor
 *
 * Using one Infrared Proximity Sensor on front to keep a reasonable distance
 * https://www.sparkfun.com/products/242
 ************************************************************************/

#include <RedBot.h>

RedBotMotor  motor;
RedBotSensor frontSensor = RedBotSensor(0);

// Having a greater backwards speed makes it seem scared when going backwards :D
const int forwardSpeed   = 150;
const int backwardsSpeed = 255;

// Calibrate this according to your sensor.
const int tooFarDistance   =  75;
const int tooCloseDistance = 225;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello world!");
}

void loop() {  
  if (tooFar()) {
    goForward();
  } else if (tooClose()) {
    goBackwards();
  } else {
    beStill();
  }
}

// Returns an int between 0 and 1023, the bigger, the closer an object is
int frontProximity() {
  frontSensor.read();
}

boolean tooFar() {
  if (frontProximity() < tooFarDistance) {
    return(true);
  } else {
    return(false);
  }
}

boolean tooClose() {
  if (frontProximity() > tooCloseDistance) {
    return(true);
  } else {
    return(false);
  }
}

void goForward() {
  Serial.println("FORWARD");
  motor.drive(forwardSpeed);
}

void goBackwards() {
  Serial.println("BACKWARDS");
  motor.drive(-backwardsSpeed);
}

void beStill() {
  Serial.println("STILL");
  motor.brake();
}

