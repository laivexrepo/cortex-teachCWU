#ifndef _PORTDEF_H_
#define _PORTDEF_H_

#include "API.h"

// Place all cortex port defeintions here, you should have
// a section for the motors, analog sensors and deigital sensors
// If you are using Quadruatic ENcoders you may also have a section
// declaring the ENcoder Object.
//
// This file then can be included in any of the subsystem source files
// using #include "portdef.h"

// ---------------------MOTOR PORTS -----------------------------------
#define LEFT_M_FRONT 2      // motor on leftside of robot in port #2
#define RIGHT_M_FRONT 3     // motor on rightside of robot in port #3

#define LIFT_MOTOR 8        // motor for the lift (arm)

#define CLAW_MOTOR 9        // motor for the claw (manipulator)

// ----------- Digital Ports -----------------------------
// Drive train encoders
#define QUAD_TOP_LM_PORT 3
#define QUAD_BOTTOM_LM_PORT 4
#define QUAD_TOP_RM_PORT 1
#define QUAD_BOTTOM_RM_PORT 2

// ----------- Is DEBUGGING ON ---------------------------------------
#define DEBUG_ON true
#define VEXNET_MANUAL true        // turns opcontrol into allowing for
                                  // testing autonomous code
#define VEXNET_TIME 15            // 15 seconds or other time to run
                                  // not yet implemented

// ----------- Setup sensors as needed -------------------------------
// Setup Encoder and other device instances
Encoder encoderLM;
Encoder encoderRM;

#endif // _PORTDEF_H_
