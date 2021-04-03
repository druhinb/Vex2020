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
#include "iostream"

using namespace std;
using std::cout;
using std::endl;
vex::competition Competition;

double desiredDriveVelocity = 0.5;
void autonomous(void) 
{
  setIntake(-100);
  transcribe(18.00, 10, false);
  setVIntake(-100);
  vex::wait(100, msec);
  setVIntake(0);
  rotate(90.00, true);
  tareEncoders();
  transcribe(19.00, 30, false);
  tareEncoders();
  setIntake(0);
  rotate(40.00, true);
  tareEncoders();
  transcribe(7.00, 30, false);
  tareEncoders();

  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);


  transcribe(0.1 * 12.00, 30, true);
  rotate(137.00, false);
    setIntake(-127);
  transcribe(20.00, 30, false);
  transcribe(47.5, 30, false);
  rotate(90.00, true);
  setIntake(0);
  transcribe(6.00, 30, false);

  //Second tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);
  tareEncoders();

  transcribe(22.50,10, true);
  setIntake(-100);
  tareEncoders();
  rotate(90.00, false);
  tareEncoders();
  transcribe(48.00, 30, false);
  transcribe(18.00, 20, false);
  vex::wait(100, msec);
  rotate(90.00, true);
  transcribe(22.00,10, false);
  setIntake(0);
  rotate(50.00, false);
  transcribe(0.8 * 12,30, false);

  //Third tower
  setVIntake(-100);
  vex::wait(600, msec);
  setVIntake(0);

  transcribe(30.00,30, true);
  rotate(52.00, true);
  setIntake(-100);
  transcribe(26.00, 30, false);
  transcribe(68.00,30, true);
  setIntake(0);
  rotate(90, false);
  transcribe(24.00,30, false);

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