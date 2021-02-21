#include "main.h"

void on_center_button()
{
  static bool pressed = false;
  pressed = !pressed;
  if(pressed)
  {
    pros::lcd::set_text(2, "testing 123");
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
	pros::lcd::set_text(1, "HIHIHI");
  setAllBrake();
  pros::ADIGyro gyrolll(9);
  //pros::delay(2000);
  pros::ADIEncoder lEncoder('D','C');
  pros::ADIEncoder rEncoder('A','B');
  lEncoder.reset();
  rEncoder.reset();
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
  std::shared_ptr<OdomChassisController> chassisAuton = ChassisControllerBuilder()
      .withMotors(
        {1, 12}, //left motors are ports 1 and 2
        {-10, -19}
      )  //right motors are ports 10 and 20
/*
      .withGains( //initializing integrated PID system 635
        {0.0020, 0.00001, 0}, // Distance controller gains
        {0.003, 0.00001, 0}, // Turn controller gains
        {0.002, 0.00001, 0.00006}  // Angle controller gains (helps drive straight)
      )
      */
      // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
      .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 10.25_in}, imev5BlueTPR})
      .withSensors(
          ADIEncoder{'D', 'C', true}, // left encoder in ADI ports A & B
          ADIEncoder{'A', 'B', true}  // right encoder in ADI ports C & D (reversed)
      )
      .withOdometry({{3.25_in, 18_in}, quadEncoderTPR})
      .buildOdometry(); // build an odometry chassis

      std::shared_ptr<AsyncMotionProfileController> profileController =
        AsyncMotionProfileControllerBuilder()
          .withLimits({
            1.5, // Maximum linear velocity of the Chassis in m/s
            1.0, // Maximum linear acceleration of the Chassis in m/s/s
            5.0 // Maximum linear jerk of the Chassis in m/s/s/s
          })
          .withOutput(chassisAuton)
          .buildMotionProfileController();

          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {-5_ft, 0_ft, 0_deg}}, "A5");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {-4_ft, 0_ft, 0_deg}}, "A4");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {-2_ft, 0_ft, 0_deg}}, "A2");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {-1_ft, 0_ft, 0_deg}}, "A1");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {-1.5_ft, 0_ft, 0_deg}}, "T1.5");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {-1.2_ft, 0_ft, 0_deg}}, "T1.2");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {-0.5_ft, 0_ft, 0_deg}}, "T0.5");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-30.25_in, 0_in, 0_deg}}, "S30.25");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-17.5_in, 0_in, 0_deg}}, "S17.5");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-5.5_in, 0_in, 0_deg}}, "S5.5");




//
// TODO: double all the values in movement...|
// ALERT: X AND Y ARE SWITCHED SO MAKE SURE YOUR COORDINATES
// REFLECT THAT

setVIntake(-127);
pros::delay(2000);
setVIntake(0);

pros::ADIEncoder lEncoder('D','C', true);
pros::ADIEncoder rEncoder('A','B', true);
lEncoder.reset();
rEncoder.reset();


  chassisAuton->setState({6.5_in, 36_in, 0_deg});

    setIntake(127);


  chassisAuton->setMaxVelocity(100);
  profileController->setTarget("S17.5");
  profileController->waitUntilSettled();

  setVIntake(127);
  pros::delay(300);
  setVIntake(0);

  pros::delay (1000);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("A1");
  profileController->waitUntilSettled();
  setIntake(0);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-45_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("T1.2");
  profileController->waitUntilSettled();

    //First Tower
    setVIntake(-127);
    pros::delay(700);
    setVIntake(0);


  profileController->setTarget("T1.2", true);
  profileController->waitUntilSettled();

//-------------------------------------\\
lEncoder.reset();
rEncoder.reset();
  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(130_deg);
  chassisAuton->setMaxVelocity(120);
  setIntake(127);
  profileController->setTarget("A4");
  profileController->waitUntilSettled();

  setIntake(0);
  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("T0.5");
  profileController->waitUntilSettled();

    //Second Tower
    setVIntake(-127);
    pros::delay(700);
    setVIntake(0);


    profileController->setTarget("T1.5", true);
    profileController->waitUntilSettled();
  setIntake(127);
  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();
  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("A4");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("A1");
  profileController->waitUntilSettled();

  setIntake(0);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("T1.2");
  profileController->waitUntilSettled();

  //Third Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  profileController->setTarget("S30.25", true);
  profileController->waitUntilSettled();
  setIntake(127);

  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-41_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("T1.5");
  profileController->waitUntilSettled();

  lEncoder.reset();
  rEncoder.reset();

  profileController->setTarget("S5.5", true);
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  profileController->setTarget("T1.5");
  profileController->waitUntilSettled(s);

  //Fourth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  profileController->setTarget("T0.5", true);
  profileController->waitUntilSettled();
  setIntake(127);

  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("A4");
  profileController->waitUntilSettled();

  setIntake(0);
  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-45_deg);
  chassisAuton->setMaxVelocity(100);

  profileController->setTarget("T1.2");
  profileController->waitUntilSettled();

  //Fifth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  profileController->setTarget("T1.2", true);
  profileController->waitUntilSettled();
  setIntake(127);

  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(135_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("A4");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  profileController->setTarget("T0.5");
  profileController->waitUntilSettled();

  //Sixth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  profileController->setTarget("T1.5", true);
  profileController->waitUntilSettled();
  setIntake(127);

  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("A4");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("A1");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  profileController->setTarget("T1.2");
  profileController->waitUntilSettled();

  //Seventh Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  profileController->setTarget("T1.2", true);
  profileController->waitUntilSettled();
  setIntake(127);
  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  profileController->setTarget("S30.25", true);
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("T1.5");
  profileController->waitUntilSettled();

  profileController->setTarget("S5.5");
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  profileController->setTarget("T0.5");
  profileController->waitUntilSettled();

  //Eighth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  profileController->setTarget("T0.5");
  profileController->waitUntilSettled();
  setIntake(127);
  //-------------------------------------\\

//
// chassisAuton->setState({7_in, 36_in, 0_deg});
//     setIntake(127);
//     setVIntake(127);
//     pros::delay(300);
//     setVIntake(0);
//   chassisAuton->setMaxVelocity(100);
//   chassisAuton->driveToPoint({24_in, 36_in});
//
//   chassisAuton->driveToPoint({2_ft, 2_ft});
//   setIntake(0);
//
//   chassisAuton->setMaxVelocity(75);
//   chassisAuton->turnToPoint({0_ft, 0_ft});
//   chassisAuton->setMaxVelocity(120);
//
//   chassisAuton->driveToPoint({1.4_ft, 1.4_ft});
//
//
//     setVIntake(-127);
//     pros::delay(1500);
//     setVIntake(0);
//
//
//   chassisAuton->driveToPoint({2_ft, 2_ft}, true);
//
//   setIntake(127);
//   chassisAuton->driveToPoint({6_ft, 2_ft});
//
//   setIntake(0);
//
//   chassisAuton->driveToPoint({6_ft, 1.70_ft});
//
//     setVIntake(-127);
//     pros::delay(1500);
//     setVIntake(0);
//
//
//   chassisAuton->driveToPoint({6_ft, 3_ft}, true);
//       setIntake(127);
//
//   chassisAuton->driveToPoint({10_ft, 3_ft});
//
//   chassisAuton->driveToPoint({10_ft, 2_ft});
//
//   setIntake(0);
//
//   chassisAuton->driveToPoint({10.6_ft, 1.4_ft});
//
//   setVIntake(-127);
//   pros::delay(1500);
//   setVIntake(0);
//
//   chassisAuton->driveToPoint({9_ft, 3_ft}, true);
//   setIntake(127);
//
//
//   chassisAuton->driveToPoint({9_ft, 1.45_ft});
//
//   chassisAuton->driveToPoint({9_ft, 6_ft}, true);
//
//   chassisAuton->setMaxVelocity(75);
//   chassisAuton->turnToPoint({12_ft, 6_ft});
//   chassisAuton->setMaxVelocity(120);
//
//
//   setIntake(0);
//
//   chassisAuton->driveToPoint({10.4_ft, 6.4_ft});
//
//
//   setVIntake(-127);
//   pros::delay(1500);
//   setVIntake(0);
//   chassisAuton->driveToPoint({10_ft, 6_ft}, true);
//   setIntake(127);
//
//   chassisAuton->driveToPoint({10_ft, 10_ft});
//
//   setIntake(0);
//   chassisAuton->setMaxVelocity(75);
//   chassisAuton->turnToPoint({12_ft, 12.5_ft});
//   chassisAuton->setMaxVelocity(100);
//
//   chassisAuton->driveToPoint({10.6_ft, 11_ft});
//   setVIntake(-127);
//   pros::delay(1500);
// //   setVIntake(0);

}

void opcontrol()
{
  while (true)
  {
    setDriveMotors();
    setIntakeMotors();
    setIntakeMotor();
    activeHotkeys();
    pros::delay(10);
  }


}
