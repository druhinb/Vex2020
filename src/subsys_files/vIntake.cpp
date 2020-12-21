#include "main.h"
//Helper Functions
void setVIntake(int power)
{
  vertical_intake = power;
}

void setIntakeMotor()
{
  int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
  - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setVIntake(intakePower);
}
