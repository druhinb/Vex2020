#include "main.h"

void doubleIntakeHotkey()
{
  setIntake(127);
  pros::delay(300);
  setIntake(0);
  setVIntake(127);
  pros::delay(300);
  setVIntake(0);
  setIntake(127);
  pros::delay(300);
  setIntake(0);
}

void activeHotkeys()
{
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) == 1)
  {
    doubleIntakeHotkey();
  }
}
