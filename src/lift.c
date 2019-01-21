#include "main.h"    // includes API.h and other headers
#include "lift.h"    // ensures that the corresponding header file (lift.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included

// Place all lift specific functions here, forexample
// void setHeightPID(int speed, int height) {}

void liftMove(int speed){
  // move a lift arm up and down based o nthe given speed
  motorSet(LIFT_MOTOR, speed);
}
