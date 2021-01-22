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
	pros::lcd::set_text(1, "'Hello There' said Mr. Doom");
  setAllBrake();
  pros::ADIGyro gyrolll(9);
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
        {1, 12}, //left motors are ports 1 and 2
        {-10, -19}
      )  //right motors are ports 10 and 20
      .withGains( //initializing integrated PID system
          {0.001, 0, 0.0001}, // Distance controller gains
          {0.001, 0, 0.0001}, // Turn controller gains
          {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
      )
      .withDerivativeFilters(
       std::make_unique<AverageFilter<3>>(), // Distance controller filter
       std::make_unique<AverageFilter<3>>(), // Turn controller filter
       std::make_unique<AverageFilter<3>>()  // Angle controller filter
   )
      // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
      .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 12.5_in}, imev5GreenTPR})
      .build(); // build an odometry chassis

    auto profileController = AsyncControllerFactory::motionProfile(
    1.0,  // Maximum linear velocity of the Chassis in m/s
    2.0,  // Maximum linear acceleration of the Chassis in m/s/s
    10.0, // Maximum linear jerk of the Chassis in m/s/s/s
    chassisAuton // Chassis Controller
  );
  chassisAuton->moveDistance(1_m);
  chassisAuton->turnAngle(90_deg);

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
