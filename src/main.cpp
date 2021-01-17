#include "main.h"


void on_center_button()
{
  static bool pressed = false;
  pressed = !pressed;
  if(pressed)
  {
    pros::lcd::set_text(2, "I was pressed!");
  }
  else
  {
    pros::lcd::clear_line(2);
  }
}


void initialize()
{
  //test comment
	pros::lcd::initialize();
	pros::lcd::set_text(1, "SKYNET INITIATED. LAUNCHING NUCLEAR WEAPONS.");
  setAllBrake();
  pros::ADIGyro gyro('B');
  pros::delay(2000);

}

//not important...
void disabled()
{

}

//not important...
void competition_initialize()
{

}

void autonomous()
{
  std::shared_ptr<ChassisController> chassisAuton = ChassisControllerBuilder()
      .withMotors(1, -10) // left motor is 1, right motor is 2 (reversed)
      .withGains(
          {0.001, 0, 0.0001}, // Distance controller gains
          {0.001, 0, 0.0001}, // Turn controller gains
          {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
      )
      // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
      .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
      .build(); // build an odometry chassis
  chassisAuton->moveDistance(1_m);
  chassisAuton->turnAngle(90_deg);
  setIntake(127);

}

void opcontrol()
{
  while (true)
  {
    setDriveMotors();
    setIntakeMotors();
    setIntakeMotor();
    pros::delay(10);
  }
}
