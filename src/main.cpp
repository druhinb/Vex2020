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
	pros::lcd::set_text(1, "testing 123");
  setAllBrake();
  pros::ADIGyro gyrolll(9);
  RotationSensor leftRot(3);
  RotationSensor rightRot(4, true);
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
  RotationSensor l(3);
  RotationSensor r(4, true);
  l.reset();
  r.reset();
  std::shared_ptr<OdomChassisController> chassisAuton = ChassisControllerBuilder()
      .withMotors(
        {1, 12}, //left motors are ports 1 and 2
        {-10, -19}
      )  //right motors are ports 10 and 20

    /*  .withGains(
      		{0.0035, 0, 0}, // Distance controller gains
      		{0.006, 0, 0}, // Turn controller gains
      		{0.002, 0, 0.00006}  // Angle controller gains (helps drive straight)
      )*/
      // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
      .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 9.75_in}, imev5BlueTPR})

      .withSensors(
          l, //left rotation sensor in port 1
          r//right rotation sensor in port 2 ()
      )
      .withOdometry({{3.25_in, 15.5_in}, 4090})
      .buildOdometry(); // build an odometry chassis

      std::shared_ptr<AsyncMotionProfileController> profileController =
        AsyncMotionProfileControllerBuilder()
          .withLimits({

            8.0, // Maximum linear velocity of the Chassis in m/s
            5.0, // Maximum linear acceleration of the Chassis in m/s/s
            50.0 // Maximum linear jerk of the Chassis in m/s/s/s


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
          profileController->generatePath({{0_in, 0_in, 0_deg}, {17.5_in, 0_in, 0_deg}}, "S17.5");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-5.5_in, 0_in, 0_deg}}, "S5.5");

//
// TODO: double all the values in movement...|
// ALERT: X AND Y ARE SWITCHED SO MAKE SURE YOUR COORDINATES
// REFLECT THAT




/*
pros::ADIEncoder lEncoder('D','C', true);
pros::ADIEncoder rEncoder('A','B', true);
lEncoder.reset();
rEncoder.reset();
*/

/*
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

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-41_deg);
  chassisAuton->setMaxVelocity(120);

  profileController->setTarget("T1.2");
  profileController->waitUntilSettled();

  profileController->setTarget("S5.5", true);
  profileController->waitUntilSettled();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  profileController->setTarget("T1.5");
  profileController->waitUntilSettled();

  //Fourth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  profileController->setTarget("T0.5", true);
  profileController->waitUntilSettled();
  setIntake(127);

  //-------------------------------------\\

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
*/
l.reset();
r.reset();

chassisAuton->setState({7_in, 36_in, 0_deg});
    setIntake(127);
  pros::delay(900);
  chassisAuton->setMaxVelocity(100);
  chassisAuton->driveToPoint({24_in, 36_in});
  chassisAuton->setState({2_ft, 2.5_ft, 0_deg});
  setVIntake(127);
  pros::delay(300);
  setVIntake(0);

  chassisAuton->driveToPoint({2_ft, 1.9_ft});
  chassisAuton->setState({2_ft, 2_ft, -90_deg});
  setIntake(0);

  chassisAuton->driveToPoint({1.2_ft, 1.2_ft});
  chassisAuton->setState({1.2_ft, 1.2_ft, -135_deg});

    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);


  chassisAuton->driveToPoint({2_ft, 2_ft}, true);
    chassisAuton->setState({2_ft, 2_ft, -135_deg});

  setIntake(127);

  chassisAuton->driveToPoint({5.9_ft, 2_ft});
  chassisAuton->setState({6_ft, 2_ft, 0_deg});

  chassisAuton->driveToPoint({6_ft, 1.9_ft});
  chassisAuton->setState({6_ft, 1.9_ft, -90_deg});

    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);


  chassisAuton->driveToPoint({6_ft, 3_ft}, true);
  chassisAuton->setState({6_ft, 3_ft, -90_deg});
      setIntake(127);

  chassisAuton->driveToPoint({10_ft, 3_ft});
    chassisAuton->setState({10_ft, 3_ft, 0_deg});

  chassisAuton->driveToPoint({10_ft, 2_ft});
  chassisAuton->setState({10_ft, 2_ft, -90_deg});

  setIntake(0);

  chassisAuton->driveToPoint({10.6_ft, 1.4_ft});
  chassisAuton->setState({10.6_ft, 1.6_ft, -45_deg});

  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);

  chassisAuton->driveToPoint({9_ft, 3_ft}, true);
  chassisAuton->setState({9_ft, 3_ft, -90_deg});
  setIntake(127);


  chassisAuton->driveToPoint({9_ft, 1.45_ft});
    chassisAuton->setState({9_ft, 1.45_ft, -90_deg});

  chassisAuton->driveToPoint({9_ft, 6_ft}, true);
    chassisAuton->setState({9_ft, 6_ft, -90_deg});

  setIntake(0);

  chassisAuton->driveToPoint({10.5_ft, 6_ft});
    chassisAuton->setState({10.5_ft, 6_ft, 0_deg});


  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);
  chassisAuton->driveToPoint({10_ft, 6_ft}, true);
  chassisAuton->setState({10_ft, 6_ft, 0_deg});
  setIntake(127);

  chassisAuton->driveToPoint({10_ft, 10.5_ft});
  chassisAuton->setState({10_ft, 10.5_ft, 90_deg});

  setIntake(0);

  chassisAuton->driveToPoint({10.4_ft, 10.9_ft});
  chassisAuton->setState({10.4_ft, 10.9_ft, 45_deg});
  setVIntake(-127);
  pros::delay(1500);
  chassisAuton->driveToPoint({8_ft, 8_ft});
//   setVIntake(0);

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
