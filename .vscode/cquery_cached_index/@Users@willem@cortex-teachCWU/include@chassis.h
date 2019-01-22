#ifndef _CHASSIS_H_
#define _CHASSIS_H_
// Place all chassis related globals, function stub declartions in this
// header file.
//

#define WHEEL_DIAMETER 4      // diameter of drive wheels
#define WHEEL_BASE 18         // wheel base in inches left to right wheel diagonal measured
                              // of chassis.

#define ARCADE_DRIVE false    // when false it runs tank mode, if true
                              /// we will run ARCADE mode

#define JOY_SCALE .5          // scale the joysticks to 50% valid values are 0 - 1
                              // note: 0 will diable joysticks 0 * x = 0 always....

#define DEAD_STICK 10        // Dead stick zone - joystick movement between
                             // -DEAD_STICK and DEAD_STICK will result in a joystick
                             // value of 0 - dealing with slow creepign of robot when joysticks
                             // do not land perfectly in the center position

// This file then can be included in any of the subsystem source files
// using #include "chassis.h"
void driveRobot(int speed);     // function declaration

// Sets the speeds of the left and right wheels of the chassis
void chassisSetOpcontrol(int left, int right);

// Create a convienant fucntin to stop drive motors
void chassisStopDrive();

// left turn function
void turnLeft(int speed);

// right turn function
void turnRight(int speed);

// drive forward with PID tankControl
void drivePID(int masterPower);

// drive with PID control for a given distnace in inches
void driveForDistancePID(int distance, int speed);

// make a pivot turn to the right or left for a given angle - andgle
//should be greater the 10 and less equal to 360
void pivotTurn(int direction, int speed, float angle);

#endif // _CHASSIS_H_
