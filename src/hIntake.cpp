#include "vex.h"

void setIntake(int power) {
  // Spins the horizontal intakes in opposite direction as specified by the
  // percentage of maximum power
  l_horizontal_intake.spin(vex::directionType::rev, power,
                           vex::velocityUnits::pct);
  r_horizontal_intake.spin(vex::directionType::fwd, power,
                           vex::velocityUnits::pct);
}

void setIntakeMotors() {
  // If the Left Bottom Button (L2) is being pressed (value 1) and the Left Top
  // is not (value 0)... Intakes will spin at 100 * -1, or reverse (and vice
  // versa)
  int L1Value = main_Controller.ButtonL1.pressing() ? 1 : 0;
  int L2Value = main_Controller.ButtonL2.pressing() ? 1 : 0;

  setIntake(100 * (L1Value - L2Value));
}