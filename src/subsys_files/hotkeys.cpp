#include "main.h"

void doubleIntakeHotkey()
{
  vertical_intake_L = -127;
}

void activeHotkeys()
{
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) == 1)
  {
    doubleIntakeHotkey();
  }
}
