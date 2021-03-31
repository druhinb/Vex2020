/*----------------------------------------------------------------------------/
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
  rotate(90, false);
  /*
  setIntake(-100);
  transcribe(17 ,10, false);
  setVIntake(-100);
  vex::wait(100, msec);
  setVIntake(0);

  rotate(91, true);
  transcribe(12, 10, false);
  setIntake(0);
  rotate(45, true);
  transcribe(1.1 * 12,10, false);

  //First tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(1.5 * 12,10, true);
  setIntake(-100);
  rotate(150, false);
  transcribe(53.5, 10, false);
  vex::wait(100, msec);
  setIntake(0);
  rotate(90, true);
  transcribe(6,10, false);

  //Second tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(18,10, true);
  setIntake(-100);
  rotate(85, false);
  transcribe(54.5,10, false);
  vex::wait(100, msec);
  rotate(90, true);
  transcribe(13,10, false);
  setIntake(0);
  rotate(45, false);
  transcribe(1.2 * 12,10, false);

  //Third tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(30,10, true);
  rotate(45, true);
  setIntake(-100);
  setDrive(30, 30);
  vex::wait(1000, msec);
  setDrive(0, 0);
  transcribe(60,10, true);
  setIntake(0);
  rotate(90, false);
  transcribe(24,10, false);

  //Fourth tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(12,10, true);
  rotate(90, false);
  setIntake(-100);
  transcribe(48,10, false);
  rotate(45, true);
  transcribe(0.7 * 12,10, false);

  //Fifth tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(24,10, true);
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