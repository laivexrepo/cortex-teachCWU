#ifndef _LIFT_H_
#define _LIFT_H_
// Place all lift related globals, function stub declartions in this
// header file.
//
// This file then can be included in any of the subsystem source files
// using #include "lift.h"

// function to move the lift arm up and down
void liftMove(int speed);

void liftMoveAngle (int speed, int angle);

void liftCalibrate(int speed);

#endif // _LIFT_H_
