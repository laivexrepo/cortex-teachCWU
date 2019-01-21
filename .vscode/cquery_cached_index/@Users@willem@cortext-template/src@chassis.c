#include "main.h"    // includes API.h and other headers
#include "chassis.h" // ensures that the corresponding header file (chassis.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included

// Place all chassis specific functions here, forexample
// void driveForDistancePD(int speed, int distance) {}

void driveRobot(int speed) {
  // This function drives the robot forward/backwards at given speed
  motorSet(LEFT_M_FRONT, speed);
  motorSet(RIGHT_M_FRONT, -speed);  // RIght motor is mirrored does needs to run reverse

}
