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
void autonomous(void) 
{
  transcribe(12, false);
  /*
  setIntake(0);
  transcribe(17.5, false);
  setVIntake(300);
  vex::wait(300, msec);
  setVIntake(0);

  rotate(90, true);
  transcribe(12, false);
  setIntake(0);
  rotate(45, true);
  transcribe(0.7 * 12, false);

  //First tower
  setVIntake(100);
  vex::wait(300,msec);
  setVIntake(0);

  transcribe(0.7 * 12, true);
  setIntake(100);
  rotate(135, false);
  transcribe(48, false);
  vex::wait(100, msec);
  setIntake(0);
  rotate(90, true);
  transcribe(0.5, false);

  //Second tower
  setVIntake(100);
  vex::wait(300,msec);
  setVIntake(0);

  transcribe(1.5, true);
  setIntake(100);
  rotate(90, false);
  transcribe(24, false);
  vex::wait(100, msec);
  rotate(90, true);
  transcribe(12, false);
  setIntake(0);
  rotate(45, false);
  transcribe(0.7 * 12, false);

  //Third tower
  setVIntake(100);
  vex::wait(300,msec);
  setVIntake(0);

  transcribe(34, true);
  rotate(45, true);
  setIntake(100);
  setDrive(30, 30);
  vex::wait(1000, msec);
  setDrive(0, 0);
  transcribe(60, true);
  setIntake(0);
  rotate(90, false);
  transcribe(24, false);

  //Fourth tower
  setVIntake(100);
  vex::wait(300,msec);
  setVIntake(0);

  transcribe(12, true);
  rotate(90, false);
  setIntake(100);
  transcribe(48, false);
  rotate(45, true);
  transcribe(0.7 * 12, false);

  //Fifth tower
  setVIntake(100);
  vex::wait(300,msec);
  setVIntake(0);

  transcribe(24, true);
  */
}

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
