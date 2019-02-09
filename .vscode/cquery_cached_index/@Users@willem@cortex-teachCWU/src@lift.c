#include "main.h"    // includes API.h and other headers
#include "lift.h"    // ensures that the corresponding header file (lift.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included

// Place all lift specific functions here, forexample
// void setHeightPID(int speed, int height) {}

void liftMove(int speed){
  // move a lift arm up and down based o nthe given speed
  motorSet(LIFT_MOTOR, speed);
}

void liftMoveAngle(int speed, int angle){
  // angle = ticks/degree for potentiometer move
  // get current potetniometer value
  int current_position = 0;
  current_position = analogRead(POT_PORT);
  if(DEBUG_ON){
    printf("Current Pot Value: %d ", current_position);
    printf(" Requested: %d \n", angle);
  }
  if(current_position > angle) {
    // we meed to move Down
    if(DEBUG_ON) {
      printf("Current Pos > Angle routine \n");
    }
    motorSet(LIFT_MOTOR, speed);
    while(analogRead(POT_PORT) >= angle && digitalRead(LIMSWITCH_PORT) == HIGH) {
      motorSet(LIFT_MOTOR, speed);
      delay(2);
    }
    motorSet(LIFT_MOTOR, 0 );       // reached our position we stop
  } else if( current_position < angle) {
     // we need to move up
     if(DEBUG_ON) {
       printf("Current Pos < Angle routine \n");
     }
     motorSet(LIFT_MOTOR, -speed);
     while(analogRead(POT_PORT) <= angle && analogRead(POT_PORT) <= 4000) {
       motorSet(LIFT_MOTOR, -speed);
       delay(2);
     }
     motorSet(LIFT_MOTOR, 0 );       // reached our position we stop
  } else {
    // we are assuming we are at same position as we ask it to move to
    motorSet(LIFT_MOTOR, 0);
  }
}


void liftCalibrate(int speed){
  if(DEBUG_ON) {
    printf("Limit Switch: ");
    if(digitalRead(LIMSWITCH_PORT) == LOW) { printf(" LOW \n"); }
    if(digitalRead(LIMSWITCH_PORT) == HIGH) { printf( "HIGH \n"); }

    printf("Pot value: %d \n",analogRead(POT_PORT));
  }

  motorSet(LIFT_MOTOR, speed);
  while (digitalRead(LIMSWITCH_PORT) == HIGH){
    motorSet(LIFT_MOTOR, speed);
    delay(2);
  }
  motorSet(LIFT_MOTOR, 0);
  printf("Pot value: %d \n",analogRead(POT_PORT));

  delay(3000);

  while (analogRead(POT_PORT) < 1000){
    motorSet(LIFT_MOTOR, -speed);
    delay(2);
  }
  motorSet(LIFT_MOTOR, 0);
  printf("Pot value: %d \n",analogRead(POT_PORT));

}
