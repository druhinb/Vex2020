#include "drive.h"
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;
motor LFDrive(vex::PORT12, vex::gearSetting::ratio6_1);
motor LBDrive(vex::PORT1, vex::gearSetting::ratio6_1);
motor RFDrive(vex::PORT10, vex::gearSetting::ratio6_1);
motor RBDrive(vex::PORT19, vex::gearSetting::ratio6_1);

motor r_horizontal_intake(vex::PORT8, vex::gearSetting::ratio6_1);
motor l_horizontal_intake(vex::PORT2, vex::gearSetting::ratio6_1);

motor u_vertical_intake(vex::PORT6, vex::gearSetting::ratio6_1);
motor l_vertical_intake(vex::PORT7, vex::gearSetting::ratio6_1);
rotation rEncoder(vex::PORT5);
rotation lEncoder(vex::PORT3, true);

vex::controller main_Controller = vex::controller();
// VEXcode device constructors

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // nothing to initialize
  setAllBrake();
  rEncoder.resetPosition();
  lEncoder.resetPosition();
}