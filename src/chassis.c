#include "main.h"    // includes API.h and other headers
#include "chassis.h" // ensures that the corresponding header file (chassis.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included

// Place all chassis specific functions here, forexample
// void driveForDistancePD(int speed, int distance) {}

void driveRobot(int speed) {
  // This function drives the robot forward/backwards at given speed
  motorSet(LEFT_M_FRONT, speed);
  motorSet(RIGHT_M_FRONT, -speed);  // Right motor is mirrored does needs to run reverse

}

void chassisSetOpcontrol(int left, int right) {
  // requires input for the left motor and right motor, typical from thei
  // the joystick
  motorSet(LEFT_M_FRONT, left);
  motorSet(RIGHT_M_FRONT, -right);
}

void chassisStopDrive(){
  // convienance fucntion to stop fhe drive train from moving
  motorSet(LEFT_M_FRONT, 0);
  motorSet(RIGHT_M_FRONT, 0);
}

void turnLeft(int speed) {
  // pivot turn the robot 'left' - use delay after the call to
  // turn for a given time = angle
  motorSet(LEFT_M_FRONT, speed);
  motorSet(RIGHT_M_FRONT, speed);
}

void turnRight(int speed) {
  // pivot turn the robot 'right' - use delay after the call to
  // turn for a given time = angle
  motorSet(LEFT_M_FRONT, -speed);
  motorSet(RIGHT_M_FRONT, -speed);
}

void drivePID(int masterPower) {
  // USE PID to drive straight forever - that is the funntion is called and a delayMsec
  // is used for how long the robot drives
  // Speed of the driving is also effectign its accuracy
  // Warning: do not get the P controller into a osciliating movement

  if(masterPower == 0 ) {
     masterPower = 30;
  } else if(masterPower > 110) {
    masterPower = 100;              // make sure we have head room for slave
                                    // motor to increass
  }
  int slavePower = masterPower;

  int error = 0;
  int kp = 5;

   //Reset the encoders.
   encoderReset(encoderLM);
   encoderReset(encoderRM);
   //Repeat ten times a second.
    while(true)
    {
      //Set the motor powers to their respective variables.
      motorSet(LEFT_M_FRONT, masterPower);
      motorSet(RIGHT_M_FRONT, -slavePower);

      delay(300);                     // control loop needs enough time to gather
                                      // data to base corrections on, to fast no effect,
                                      // to slow the robot will zig zag
                                      // Note: PWM can not run faster then 60Hz

      error = encoderGet(encoderLM) - encoderGet(encoderRM);
      slavePower += error / kp;

      if(DEBUG_ON){
        // We are going to write soem stuff to the terminal for debugging
        printf("MasterPower: %d ", masterPower);
        printf("SlavePower: %d ", slavePower);
        printf("Left Enc: %d ", encoderGet(encoderLM));
        printf("Right Enc: %d ", encoderGet(encoderRM));
        printf("Error: %d ", error);
        printf("Kp: %d ", kp);
        printf("\n ");
      }
      //Reset the encoders every loop.
      encoderReset(encoderLM);
      encoderReset(encoderRM);
    }
}
