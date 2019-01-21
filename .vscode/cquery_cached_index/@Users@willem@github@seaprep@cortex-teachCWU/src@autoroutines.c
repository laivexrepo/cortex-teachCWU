// This source file should contain various autonomous routine functions and grouped
// together to run one of multiple autonomous routine sequences based on some selection
//

#include "main.h"
#include "portdef.h"			// Cortex port defintions
#include "intake.h"
#include "shooter.h"
#include "chassis.h"
#include "manipulator.h"
#include "lift.h"
#include "auto.h"

void compAutoRedRight(){
  // All the veraious autonomous commands for the Competition, Red Sqaure
  // Right position go here.  THen this function is called in auto.c the autonomous()
  // function based on some selector input.

}

void testAutoDrive(){
  // lets drive forward for a set speed using PID and will drive forever
  // unless asked to stop.....
  driveRobot(80);       // dirve robot forward at speed '80'
  delay(2000);         // drive for 200mSec (2Sec)
}
