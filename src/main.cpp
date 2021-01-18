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
      .withMotors(
        {-1, -2}, //left motors are ports 1 and 2
        {10, 20}  //right motors are ports 10 and 20
      .withGains( //initializing integrated PID system
          {0.001, 0, 0.0001}, // Distance controller gains
          {0.001, 0, 0.0001}, // Turn controller gains
          {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
      )
      // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
      .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 13_in}, imev5GreenTPR})
      .build(); // build an odometry chassis
  chassisAuton->moveDistance(1_m);
  chassisAuton->turnAngle(90_deg);
  setIntake(127);
  setIntake(0);

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
