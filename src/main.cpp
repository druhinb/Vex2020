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
          {0.00034, 0.001, 0}, // Distance controller gains
          {0.003, 0.0009, 0.00008}, // Turn controller gains
          {0.00038, 0.00080, 0.00008}  // Angle controller gains (helps drive straight)
      )
      // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
      .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 9.5_in}, imev5GreenTPR})
      .build(); // build an odometry chassis

      std::shared_ptr<AsyncMotionProfileController> profileController =
        AsyncMotionProfileControllerBuilder()
          .withLimits({
            1.0, // Maximum linear velocity of the Chassis in m/s
            1.0, // Maximum linear acceleration of the Chassis in m/s/s
            5.0 // Maximum linear jerk of the Chassis in m/s/s/s
          })
          .withOutput(chassisAuton)
          .buildMotionProfileController();

  chassisAuton->setMaxVelocity(150);

  profileController->generatePath({{0_in, 0_in, 0_deg}, {-16_in, 0_in, 0_deg}}, "A1");
  profileController->generatePath({{0_in, 0_in, 0_deg}, {-12_in, 0_in, 0_deg}}, "B1");
  profileController->generatePath({{0_in, 0_in, 0_deg}, {-48_in, 0_in, 0_deg}}, "C1");
  profileController->generatePath({{0_in, 0_in, 0_deg}, {-31_in, 0_in, 0_deg}}, "C2");
  profileController->generatePath({{0_in, 0_in, 0_deg}, {-34_in, 0_in, 0_deg}}, "C3");
  profileController->generatePath({{0_in, 0_in, 0_deg}, {-42_in, 0_in, 0_deg}}, "C4");
  profileController->generatePath({{0_in, 0_in, 0_deg}, {-5_in, 0_in, 0_deg}}, "D1");
  profileController->generatePath({{0_in, 0_in, 0_deg}, {-6.5_in, 0_in, 0_deg}}, "D2");

    setVIntake(-127);
    pros::delay(1000);
    setVIntake(0);
    setIntake(127);

  profileController->setTarget("A1");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(150);

  profileController->setTarget("B1");
  profileController->waitUntilSettled();

    setIntake(0);

    setVIntake(-127);
    pros::delay(300);
    setVIntake(0);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-45_deg);
  chassisAuton->setMaxVelocity(150);

  profileController->setTarget("B1");
  profileController->waitUntilSettled();

    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);

  profileController->setTarget("B1", true);
  profileController->waitUntilSettled();

    setIntake(127);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(135_deg);
  chassisAuton->setMaxVelocity(150);

  profileController->setTarget("C1");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(150);

    setIntake(0);

  profileController->setTarget("D1");
  profileController->waitUntilSettled();

    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);

  profileController->setTarget("D1", true);
  profileController->waitUntilSettled();

    setIntake(127);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(180_deg);
  chassisAuton->setMaxVelocity(150);

  profileController->setTarget("A1");
  profileController->waitUntilSettled();

    setVIntake(-127);
    pros::delay(300);
    setVIntake(0);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(150);

  profileController->setTarget("C3");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(150);

    setIntake(0);
  profileController->setTarget("C2");
  profileController->waitUntilSettled();

    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);

  profileController->setTarget("D2");
  profileController->waitUntilSettled();

    setIntake(127);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(150);

  profileController->setTarget("C4");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(150);

    setIntake(0);

  profileController->setTarget("A1");
  profileController->waitUntilSettled();

    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);

  profileController->setTarget("A1", true);
  profileController->waitUntilSettled();
//------------------------------------------------------------------------------------\\
#pragma region oldAuton
/*
  setVIntake(-127);
  pros::delay(1000);
  setVIntake(0);
  setIntake(127);
  chassisAuton->moveDistance(16_in);
  pros::delay(500);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->moveDistance(12_in);
  setIntake(0);

  setVIntake(-127);
  pros::delay(300);
  setVIntake(0);

  chassisAuton->turnAngle(-45_deg);
  chassisAuton->moveDistance(11_in);
    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);
  chassisAuton->moveDistance(-11_in);

  setIntake(127);
  chassisAuton->turnAngle(130_deg);
  chassisAuton->moveDistance(48_in);
  chassisAuton->turnAngle(-90_deg);
  setIntake(0);
  chassisAuton->moveDistance(5_in);
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);
  chassisAuton->moveDistance(-5.5_in);
  setIntake(127);
  chassisAuton->turnAngle(180_deg);

  chassisAuton->moveDistance(17_in);
  setVIntake(-127);
  pros::delay(300);
  setVIntake(0);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->moveDistance(34_in);
  chassisAuton->turnAngle(57_deg);
  setIntake(0);
  chassisAuton->moveDistance(31_in);
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);
  chassisAuton->moveDistance(-6.5_in);

  setIntake(127);
  //this was the area we need to fix
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(75);
  chassisAuton->moveDistance(42_in);
  chassisAuton->turnAngle(45_deg);
  setIntake(0);
  chassisAuton->moveDistance(17_in);
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);
  chassisAuton->moveDistance(-17_in);



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
*/
#pragma endregion oldAuton
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
