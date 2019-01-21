#include "main.h"    // includes API.h and other headers
#include "manipulator.h" // ensures that the corresponding header file (manipluator.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included

// Place all manipluator specific functions here, forexample
// void flipGrabber(int speed, int rotation) {}

void moveClaw(int speed) {
  motorSet(CLAW_MOTOR, speed);
}
