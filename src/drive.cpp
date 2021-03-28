#include "vex.h"

void setDrive(int left, int right)
{
  //Sets the left motors to spin at the value for the left motors, and the 
  //right motors to spin at the value for the right motors as a percentage
  //of maximum power
  LFDrive.spin(vex::directionType::fwd, left, velocityUnits::pct);
  LBDrive.spin(vex::directionType::fwd, left, velocityUnits::pct);
  RFDrive.spin(vex::directionType::fwd, right, velocityUnits::pct);
  RBDrive.spin(vex::directionType::fwd, right, velocityUnits::pct);
}

void resetDriveEncoders()
{
  //Resets the positions of the integrated motor encoders (currently not being used in anything)
  LFDrive.resetPosition();
  LBDrive.resetPosition();
  RFDrive.resetPosition();
  RBDrive.resetPosition();
}

//Sets the motor power based on the joystick value
void setDriveMotors()
{
  //Left Y-Axis = forwards/backwards, Right X-Axis = left and right turns
  int right_joystick = main_Controller.Axis3.position();
  int left_joystick = main_Controller.Axis1.position();

  //If the joystick values are above some threshold...
  if(abs(left_joystick) < 5)
    left_joystick = 0;
  if(abs(right_joystick) < 5)
    right_joystick = 0;

  //Formula for calculating arcade movement based on joystick input
  setDrive(left_joystick + right_joystick, left_joystick - right_joystick);
}

//Sets the brake modes to coast (for the drive) and to brake (for everything else)
void setAllBrake()
{
  LFDrive.setBrake(brakeType::coast);
  LBDrive.setBrake(brakeType::coast);
  RFDrive.setBrake(brakeType::coast);
  RBDrive.setBrake(brakeType::coast);

  l_horizontal_intake.setBrake(brakeType::brake);
  r_horizontal_intake.setBrake(brakeType::brake);

  u_vertical_intake.setBrake(brakeType::brake);
  l_vertical_intake.setBrake(brakeType::brake);
  
}