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
      .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 10.1_in}, imev5BlueTPR})
      .withSensors(
          ADIEncoder{'D', 'C', true}, // left encoder in ADI ports A & B
          ADIEncoder{'A', 'B', true}  // right encoder in ADI ports C & D (reversed)
      )
      .withOdometry({{2.75_in, 18_in}, quadEncoderTPR})
      .buildOdometry(); // build an odometry chassis

      std::shared_ptr<AsyncMotionProfileController> profileController =
        AsyncMotionProfileControllerBuilder()
          .withLimits({
            1.0, // Maximum linear velocity of the Chassis in m/s
            1.0, // Maximum linear acceleration of the Chassis in m/s/s
            5.0 // Maximum linear jerk of the Chassis in m/s/s/s
          })
          .withOutput(chassisAuton)
          .buildMotionProfileController();

          profileController->generatePath({{0_in, 0_in, 0_deg}, {-16_in, 0_in, 0_deg}}, "A1");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-12_in, 0_in, 0_deg}}, "B1");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-48_in, 0_in, 0_deg}}, "C1");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-31_in, 0_in, 0_deg}}, "C2");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-34_in, 0_in, 0_deg}}, "C3");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-42_in, 0_in, 0_deg}}, "C4");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-5_in, 0_in, 0_deg}}, "D1");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {-6.5_in, 0_in, 0_deg}}, "D2");

//TODO: double all the values in movement...|
//ALERT: X AND Y ARE SWITCHED SO MAKE SURE YOUR COORDINATES
//REFLECT THAT

// setVIntake(-127);
// pros::delay(2000);
// setVIntake(0);

pros::ADIEncoder lEncoder('D','C', true);
pros::ADIEncoder rEncoder('A','B', true);
lEncoder.reset();
rEncoder.reset();

/*
  chassisAuton->setState({6.5_in, 36_in, 0_deg});

    setIntake(127);
    setVIntake(127);
    pros::delay(300);
    setVIntake(0);

  chassisAuton->setMaxVelocity(100);
  chassisAuton->driveToPoint({24_in, 36_in});

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(1_ft);
  setIntake(0);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-45_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(1.1_ft);

    //First Tower
    setVIntake(-127);
    pros::delay(700);
    setVIntake(0);


  chassisAuton->moveDistance(-1.1_ft);

//-------------------------------------\\
lEncoder.reset();
rEncoder.reset();
  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(145_deg);
  chassisAuton->setMaxVelocity(120);
  setIntake(127);
  chassisAuton->moveDistance(4_ft);

  setIntake(0);
  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-95_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(0.3_ft);

    //Second Tower
    setVIntake(-127);
    pros::delay(700);
    setVIntake(0);


  chassisAuton->moveDistance(-1.3_ft);
  setIntake(127);
  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();
  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(4_ft);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(1_ft);

  setIntake(0);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(1.1_ft);

  //Third Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  chassisAuton->moveDistance(-30.17_in);
  setIntake(127);

  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-41_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(1.7_ft);

  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->moveDistance(-4.9_ft);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  chassisAuton->moveDistance(1.4_ft);

  //Fourth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  chassisAuton->moveDistance(-0.5_ft);
  setIntake(127);

  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(4_ft);

  setIntake(0);
  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-45_deg);
  chassisAuton->setMaxVelocity(100);

  chassisAuton->moveDistance(1.1_ft);

  //Fifth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  chassisAuton->moveDistance(-1.1_ft);
  setIntake(127);

  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(135_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(4_ft);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  chassisAuton->moveDistance(0.5_ft);

  //Sixth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  chassisAuton->moveDistance(-1.5_ft);
  setIntake(127);

  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(4_ft);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(1_ft);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  chassisAuton->moveDistance(1.1_ft);

  //Seventh Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  chassisAuton->moveDistance(-1.1_ft);
  setIntake(127);
  //-------------------------------------\\
  lEncoder.reset();
  rEncoder.reset();

  chassisAuton->moveDistance(-30.7_in);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
  chassisAuton->setMaxVelocity(120);

  chassisAuton->moveDistance(1.2_ft);

  chassisAuton->moveDistance(-4.2_ft);

  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(90_deg);
  chassisAuton->setMaxVelocity(120);

  setIntake(0);

  chassisAuton->moveDistance(0.7_ft);

  //Eighth Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);

  chassisAuton->moveDistance(-0.7_ft);
  setIntake(127);
  //-------------------------------------\\
*/

  chassisAuton->setState({6.5_in, 36_in, 0_deg});
      setIntake(127);
      setVIntake(127);
      pros::delay(300);
      setVIntake(0);
    chassisAuton->setMaxVelocity(100);
    chassisAuton->driveToPoint({24_in, 36_in});



    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToAngle(-90);
    chassisAuton->setMaxVelocity(120);

    chassisAuton->driveToPoint({2_ft, 2_ft});
    setIntake(0);

    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({1.4_ft, 1.4_ft});
    chassisAuton->setMaxVelocity(120);

    chassisAuton->driveToPoint({1.4_ft, 1.4_ft});


      setVIntake(-127);
      pros::delay(1500);
      setVIntake(0);


    chassisAuton->driveToPoint({2_ft, 2_ft}, true);


    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({6_ft, 1.2_ft});
    chassisAuton->setMaxVelocity(120);
    setIntake(127);
    chassisAuton->driveToPoint({6_ft, 1.8_ft});

    setIntake(0);
    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({6_ft, 0_ft});
    chassisAuton->setMaxVelocity(120);

    chassisAuton->driveToPoint({6_ft, 1.70_ft});

      setVIntake(-127);
      pros::delay(1500);
      setVIntake(0);


    chassisAuton->driveToPoint({6_ft, 3_ft}, true);
        setIntake(127);
    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({10_ft, 3_ft});
    chassisAuton->setMaxVelocity(120);

    chassisAuton->driveToPoint({10_ft, 3_ft});

    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({10_ft, 2.2_ft});
    chassisAuton->setMaxVelocity(120);

    chassisAuton->driveToPoint({10_ft, 2_ft});

    setIntake(0);

    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({12_ft, 0_ft});
    chassisAuton->setMaxVelocity(120);


    chassisAuton->driveToPoint({10.6_ft, 1.4_ft});

    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);

    chassisAuton->driveToPoint({9_ft, 3_ft}, true);
    setIntake(127);

    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({9_ft, 1.5_ft});
    chassisAuton->setMaxVelocity(120);


    chassisAuton->driveToPoint({9_ft, 1.45_ft});

    chassisAuton->driveToPoint({9_ft, 6.3_ft}, true);

    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({12_ft, 6.3_ft});
    chassisAuton->setMaxVelocity(120);


    setIntake(0);

    chassisAuton->driveToPoint({10.3_ft, 6.3_ft});


    //chassisAuton->driveToPoint({10.2_ft, 6_ft});
    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);
    chassisAuton->driveToPoint({10_ft, 6.3_ft}, true);
    setIntake(127);

    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({10_ft, 10.5_ft});
    chassisAuton->setMaxVelocity(120);

    chassisAuton->driveToPoint({10_ft, 10.5_ft});

    setIntake(0);
    chassisAuton->setMaxVelocity(75);
    chassisAuton->turnToPoint({12_ft, 12.5_ft});
    chassisAuton->setMaxVelocity(100);
    chassisAuton->driveToPoint({10.6_ft, 11_ft});
    setVIntake(-127);
    pros::delay(1500);
    setVIntake(0);

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
