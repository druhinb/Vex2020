#include "vex.h"

void setVIntake(int power)
{
  //Spins the vertical intakes in the same direction at the specified percentage of max power
  l_vertical_intake.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
  u_vertical_intake.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
}

void setVerticalMotors()
{
  //If the Right Bottom Bumper is being pressed (value 1), and Right Top (R1) is not, then will spin
  // at 100 * -1 (reverse) and vice versa
  int R1Value = main_Controller.ButtonR1.pressing() ? 1 : 0;
  int R2Value = main_Controller.ButtonR2.pressing() ? 1 : 0;

  setVIntake(100 * (R1Value - R2Value));
}