/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "auto.h"
#include "chassis.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

int autoState = 1;

void autonomous() {
   // run different autonomous routines based on the valye of autoState; autoState
   // could be sleected via some method during initialization usign for example a
   // a potentiometer.
   switch(autoState) {
     case 0:
       drivePID(60);      //will run forever until powered off
     case 1:
       driveForDistancePID(36, 60);     // for 36" at speed 60
       pivotTurn(0, 30, 90);            // turn at seed 30 for 90 degree angle right turn
       driveForDistancePID(12, 50);     // After turn drive a bit more forward
     break;

     case 2:
      compAutoRedRight();
     break;

     case 3:
       drivePID(80);
     break;

     default:
       // default case shoudl not run anything or competition autonomous
     break;
  }
}
