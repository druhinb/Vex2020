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
