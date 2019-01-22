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
      slavePower = slavePower + (error / kp);

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

void driveForDistancePID(int distance, int speed) {
  // drive the robot using PID control on the drive base for a given
  // distance. Distance is supplied in inches, and speed should be < 100 to allow
  // for enough head space for the slave motor to catchup.

  int masterPower = speed;                      // Set the master motor to the incoming speed
                                                // we are doign a sanity check a bit further down

  float wheelCircum = WHEEL_DIAMETER * 3.14;    // global WHEEL_DIAMETER is set in chassis.h
  float motorDegree = (distance / wheelCircum) * 360;  // cast into full degrees

  if(DEBUG_ON) {
    printf("Dist: %1.2f \n", motorDegree);
    wait(200);                        // Let terminal catch up
  }

  if(masterPower == 0 ) {
     masterPower = 30;
  } else if(masterPower > 110) {
    masterPower = 100;              // make sure we have head room for slave
                                    // motor to increass
  }

  int totalTicks = 0;               // track total trveled
  int slavePower = speed - 5;
  int error = 0;
  int kp = 5;                       // can be tuned to help zig-zag and accuracy, be careful!

  encoderReset(encoderLM);
  encoderReset(encoderRM);

  while(abs(totalTicks) < motorDegree)
  {
    //Set the motor powers to their respective variables.
    motorSet(LEFT_M_FRONT, masterPower);
    motorSet(RIGHT_M_FRONT, -slavePower);

    delay(300);                     // control loop needs enough time to gather
                                    // data to base corrections on, to fast no effect,
                                    // to slow the robot will zig zag
                                    // Note: PWM can not run faster then 60Hz

    error = encoderGet(encoderLM) - encoderGet(encoderRM);
    slavePower = slavePower + (error / kp);

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

    //Add this iteration's encoder values to totalTicks.
    totalTicks+= encoderGet(encoderLM);
    if(DEBUG_ON) {
      printf("error: %d", error);
      printf(" slavePower: %d", slavePower);
      printf(" totalTicks: %d \n", totalTicks);
    }
    // reset the encoders for the next loop around
    encoderReset(encoderLM);
    encoderReset(encoderRM);
  }
  // we have reached our desired distance, so stop the motors.
  motorSet(LEFT_M_FRONT, 0);
  motorSet(RIGHT_M_FRONT, 0);

}

void pivotTurn(int direction, int speed, float angle) {
  // direction -- 1 = left turn, 0 = right pivotTurn
  // speed -- -100 -- 100
  // angle -- desired turn angle in degrees
  //
  // Assumes a quadriatic encoder - 360 tics = 360 degrees

  // incoming speed variable sanity check
  if(speed == 0 ) {
     speed = 30;
  } else if(speed > 110) {
    speed = 100;              // make sure we have head room for slave
                              // motor to increass
  }

  // pivotTurn - turn radius is 1/2 * dimaeter of wheel base
  float turnCircum = WHEEL_BASE * 3.14;           // wheel_base is defind in chassis.h
  float wheelCircum = WHEEL_DIAMETER * 3.14;      // wheel_diameter is defined in chassis.h

  float motorDegree = (((angle/360) * turnCircum) / wheelCircum) * 360;

  if(DEBUG_ON) {
    printf("turnCricum: %1.2f \n", turnCircum);
    printf("wheelCricum: %1.2f \n", wheelCircum);
    printf("turn Angle: %1.2f \n", angle);
    printf("motorDegree: %1.2f \n", motorDegree);
  }

  if(direction == 1) {
    // Left turn
    // we need todo a while loop and count until we get to motorDegree
    // on quadriatic encoders
    encoderReset(encoderLM);
    delay(10);                   // give encoder time to reset

    while(encoderGet(encoderLM) <= motorDegree) {
      if(DEBUG_ON){
        printf("encoderLM: %d \n", encoderGet(encoderLM));
      }
      motorSet(LEFT_M_FRONT, speed);
      motorSet(RIGHT_M_FRONT, speed);

      delay(10);                 // we need to give it a bit of time to settle, but
                                 // if we make thsi time to long we will overshoot!
    }
  } else {
    // Right turn
    // we need todo a while loop and count until we get to motorDegree
    // on quadriatic encoders
    encoderReset(encoderRM);

    while(encoderGet(encoderRM) <= motorDegree) {
      if(DEBUG_ON){
        printf("encoderRM: %d \n", encoderGet(encoderRM));
      }
      motorSet(LEFT_M_FRONT, -speed);
      motorSet(RIGHT_M_FRONT, -speed);

      delay(10);                 // we need to give it a bit of time to settle, but
                                 // if we make thsi time to long we will overshoot!
    }
  }
  // stop the turn when we reach destination
  motorSet(LEFT_M_FRONT, 0);
  motorSet(RIGHT_M_FRONT, 0);
}
