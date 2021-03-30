/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Administrator                                    */
/*    Created:      Sat Mar 27 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "autonFunctions.h"
#include "drive.h"
#include "hIntake.h"
#include "vIntake.h"
#include "vex.h"

using namespace vex;

vex::competition Competition;

double desiredDriveVelocity = 0.5;
void autonomous(void) {rotate(90, 10, true);}

// For some reason, tasks and semaphores hog too much CPU memory. As a result,
// put the controller joystick update in this instead...
void usercontrol(void) {
  while (true) {
    int right_joystick = main_Controller.Axis3.position();
    int left_joystick = main_Controller.Axis1.position();

    if (abs(left_joystick) < 7)
      left_joystick = 0;
    if (abs(right_joystick) < 7)
      right_joystick = 0;
    
    setDrive((left_joystick / 3 + right_joystick) / 2, (left_joystick / 3 - right_joystick) / 2);
    
    setIntakeMotors();
    setVerticalMotors();
    
    vex::wait(10, msec);
  }
}

// Sets the functions to be used for the competition mode (usercontrol and
// autonomous for driverocntrol and autonomous) respectively
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);
}
