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
	pros::lcd::set_text(1, "Ani says hi");
  setAllBrake();
  pros::ADIGyro gyrolll(9);
  //pros::delay(2000);

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
        {1, 12}, //left motors are ports 1 and 2
        {-10, -19}
      )  //right motors are ports 10 and 20
      .withGains( //initializing integrated PID system
          {0.0020, 0.00001, 0}, // Distance controller gains
          {0.003, 0.00001, 0}, // Turn controller gains
          {0.002, 0.00001, 0.00006}  // Angle controller gains (helps drive straight)
      )
      .withDerivativeFilters(
       std::make_unique<AverageFilter<3>>(), // Distance controller filter
       std::make_unique<AverageFilter<3>>(), // Turn controller filter
       std::make_unique<AverageFilter<3>>()  // Angle controller filter
   )
      // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
      .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 9.5_in}, imev5GreenTPR})
      .build(); // build an odometry chassis

  chassisAuton->setMaxVelocity(100);
  setVIntake(-127);
  pros::delay(1000);
  setVIntake(0);

  setIntake(127);
  chassisAuton->moveDistance(16_in);
  pros::delay(500);
  chassisAuton->turnAngle(-100_deg);
  chassisAuton->moveDistance(12_in);
  setIntake(0);

  setVIntake(-127);
  pros::delay(300);
  setVIntake(0);

  chassisAuton->turnAngle(-55_deg);
  chassisAuton->moveDistance(10_in);
    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);
  chassisAuton->moveDistance(-11_in);

  setIntake(127);
  chassisAuton->turnAngle(150_deg);
  chassisAuton->moveDistance(48_in);
  chassisAuton->turnAngle(-105_deg);
  setIntake(0);
  chassisAuton->moveDistance(5_in);
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);
  chassisAuton->moveDistance(-5.5_in);
  setIntake(127);
  chassisAuton->turnAngle(195_deg);

  chassisAuton->moveDistance(16_in);
  setVIntake(-127);
  pros::delay(300);
  setVIntake(0);
  chassisAuton->turnAngle(50_deg);
  chassisAuton->moveDistance(34_in);
  chassisAuton->turnAngle(55_deg);
  setIntake(0);
  chassisAuton->moveDistance(31_in);
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);
  chassisAuton->moveDistance(-5.5_in);

  setIntake(127);
  //this was the area we need to fix
  chassisAuton->turnAngle(-95_deg);
  chassisAuton->moveDistance(42_in);
  chassisAuton->turnAngle(47_deg);
  setIntake(0);
  chassisAuton->moveDistance(20_in);
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);
  chassisAuton->moveDistance(-20_in);
  setIntake(127);
  chassisAuton->turnAngle(-84_deg);
  chassisAuton->moveDistance(10_in);
  chassisAuton->moveDistance(-10_in);
  chassisAuton->turnAngle(-66_deg);

  chassisAuton->moveDistance(16_in);
  chassisAuton->moveDistance(24_in);
  chassisAuton->turnAngle(100_deg);
    setIntake(0);
  chassisAuton->moveDistance(10_in);
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);
  chassisAuton->moveDistance(-10_in);
    setIntake(127);
  chassisAuton->turnAngle(-100_deg);
  chassisAuton->moveDistance(16_in);
  chassisAuton->moveDistance(24_in);
  chassisAuton->turnAngle(-100_deg);
  chassisAuton->moveDistance(12_in);
  chassisAuton->moveDistance(-12_in);
  chassisAuton->turnAngle(150_deg);
  chassisAuton->moveDistance(10_in);
  chassisAuton->moveDistance(-10_in)
  ;
  chassisAuton->turnAngle(-145_deg);
  chassisAuton->moveDistance(16_in);
  chassisAuton->moveDistance(72_in);
  chassisAuton->turnAngle(50_deg);
  chassisAuton->moveDistance(10_in);

  setIntake(127);
  setVIntake(127);

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
