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
  setIntake(-100);
  transcribe(18.00, 30, false);
  setVIntake(-100);
  vex::wait(100, msec);
  setVIntake(0);
  rotate(90.00, true);
  tareEncoders();
  transcribe(13.00, 30, false);
  tareEncoders();
  setIntake(0);
  rotate(45.00*0.66, true);
  tareEncoders();
  transcribe(12.00, 30, false);
  tareEncoders();

  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  setIntake(127);
  transcribe(0.7 * 12.00, 30, true);
  rotate(123.00, false);
  transcribe(20.00, 30, false);
  transcribe(52.00, 30, false);
  rotate(90.00, true);
  transcribe(6.00, 30, false);

  //Second tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);
  tareEncoders();

  transcribe(20.00,10, true);
  setIntake(-100);
  tareEncoders();
  rotate(93.00, false);
  tareEncoders();
  transcribe(18.00, 30, false);
  transcribe(52.00, 30, false);
  vex::wait(100, msec);
  rotate(90.00, true);
  transcribe(20.00,10, false);
  setIntake(0);
  rotate(53.00, false);
  transcribe(1.2 * 12,30, false);

  //Third tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(30.00,30, true);
  rotate(45.00, true);
  setIntake(-100);
  transcribe(12.00, 30, false);
  transcribe(60.00,30, true);
  setIntake(0);
  rotate(90, false);
  transcribe(24.00,10, false);

  //Fourth tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(12.00,10, true);
  rotate(90.00, false);
  setIntake(-100);
  transcribe(48,10, false);
  rotate(45.00, true);
  transcribe(0.7 * 12,10, false);

  //Fifth tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(24.00,10, true);
  

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
    
    setDrive((left_joystick + right_joystick) / 1.3, (left_joystick - right_joystick) / 1.3);
    
    setIntakeMotors();
    setVerticalMotors();
    
    vex::wait(20, msec);
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