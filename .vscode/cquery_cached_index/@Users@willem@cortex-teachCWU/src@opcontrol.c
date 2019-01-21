/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "portdef.h"			// Cortex port defintions
#include "intake.h"
#include "shooter.h"
#include "chassis.h"
#include "manipulator.h"
#include "lift.h"
#include "auto.h"


/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
  // This section of code, allows for testing the autonomous code without being connected
  // to the field control system, or the use of a manual VEnet test switch.
  // operatorControl is triggered automatically during robot reboot, the below code
  // will wait for one of two actiosn to take place:
  // 8 JOY_UP pressed triggers autonomous() -- autonomouscode
  // 8 JOY_DOWN will by basss autonomous code
  //
  // This code shoudl be commented out or disbaled for a robot particiapting in a Competition
  // to ensure the robot is fully under fieldControl.

  bool autoRun = true;

  while(VEXNET_MANUAL && autoRun) {
     // CODE To test Autonomous without VEXnet switch
     // This should never be part of production code
     if(joystickGetDigital(1, 8, JOY_UP)) {
         autonomous();
     } else if(joystickGetDigital(1, 8, JOY_DOWN)) {
         autoRun = false;
     }
  }

  // Start of operator drive code
  int left = 0;               // variable used for left joystick value to drive train
  int right = 0;              // variable used for right joystick value to drive train

  //Reset the encoders on the drive train.
  encoderReset(encoderLM);
  encoderReset(encoderRM);

  while(true){
    // arcade drive or tank mode -- controlled by the ARCADE_DRIVE global
    if(ARCADE_DRIVE) {
        // We are driving in Arcade mode - single joystick controllling movement
		    left = joystickGetAnalog(1, 2);   // vertical axis on left joystick
		    right  = joystickGetAnalog(1, 1); // horizontal axis on left joystick
		    chassisSetOpcontrol(left + right, left - right);
    } else {
        /// tank drive - left joystick on left drive train, right joystick on right drive train
        // Joystick values are sclaed usign the global JOY_SCALE which can be a value between 0 and 1,
        // a value of 0 of course disbales the joystick movement X * 0 = 0 always
    	  left = joystickGetAnalog(1, 3); // vertical axis on left joystick
    		right  = joystickGetAnalog(1, 2); // horizontal axis on left joystick
        if(abs(left) < DEAD_STICK) { left = 0; }
        if(abs(right) < DEAD_STICK) { right = 0; }
        chassisSetOpcontrol(left * JOY_SCALE, right * JOY_SCALE);
    }
    // If in debug mode print to the console the control values of the driving
    // control (joystick and encoder data)
    if(DEBUG_ON) {
  		printf("Left Enc: %d", encoderGet(encoderLM));
	  	printf(" Right Enc: %d ", encoderGet(encoderRM));
      printf(" Left Joy: %d ", left);
      printf(" Right Joy: %d \n", right);
    }

    // The following buttons sequence controls the left going up-and Down
    // add the following logic:
    if(joystickGetDigital(1, 6, JOY_UP)) {
       liftMove(100);         // pressing up, so lift should go up
    }
    else if(joystickGetDigital(1, 6, JOY_DOWN)) {
       liftMove(-100);        // pressing down, so lift should go down
    }
    else {
       liftMove(0);           // no buttons are pressed, stop the lift
    }

    // The following code moves the claw - we use the button group 5 on the remote
    if(joystickGetDigital(1, 5, JOY_UP)) {
       moveClaw(75);         // pressing up, so lift should go up
    }
    else if(joystickGetDigital(1, 5, JOY_DOWN)) {
       moveClaw(-75);        // pressing down, so lift should go down
    }
    else {
       moveClaw(0);           // no buttons are pressed, stop the lift
    }

		delay(20);     // We need the electronics time to react to the processor commands
	}
}
