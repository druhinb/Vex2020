#include "main.h"

void setIntake(int power)
{
  l_horizontal_intake = power;
  r_horizontal_intake = -power;
}

void setIntakeMotors()
{
  int intakePower = 200 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)
  - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
  setIntake(intakePower);
}
