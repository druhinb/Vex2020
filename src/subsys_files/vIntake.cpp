#include "main.h"
//Helper Functions
void setVIntake(int power)
{
  vertical_intake_L = power;
  vertical_intake_U = power;
}

void setIntakeMotor()
{
  int intakePower = 200 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
  - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setVIntake(intakePower);
}
