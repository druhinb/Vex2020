#include "main.h"

void setDrive(int left, int right)
{
  LF_drive = left;
  LB_drive = left;
  RF_drive = right;
  RB_drive = right;
}
//Driver Control Functions
void setDriveMotors()
{
  setDrive(0, 0);
  int left_joystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right_joystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  if(abs(left_joystick) < 10)
    left_joystick = 0;
  if (abs(right_joystick) < 10)
    right_joystick = 0;
  setDrive(left_joystick, right_joystick);
}
