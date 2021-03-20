#include "main.h"

void on_center_button()
{
  static bool pressed = false;
  pressed = !pressed;
  if(pressed)
  {
    pros::lcd::set_text(2, "Test Upload");
  }
  else
  {
    pros::lcd::clear_line(2);
  }
}


void initialize()
{
  pros::Rotation l(3);
  pros::Rotation r(5);
  l.reset_position(); r.reset_position();
  Logger::setDefaultLogger(
    std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::debug // Show errors and warnings
    )
);
  //test comment
	pros::lcd::initialize();
	pros::lcd::set_text(1, "uibhghvhgvuhy");
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


  std::shared_ptr<OdomChassisController> chassisAuton = ChassisControllerBuilder()
      .withMotors(
        {1, 12}, //left motors are ports 1 and 2
        {-10, -19}
      )  //right motors are ports 10 and 19
      /*
      .withGains(
        		{0.0035, 0, 0}, // Distance controller gains
        		{0.006, 0, 0}, // Turn controller gains
        		{0.002, 0, 0.00006}  // Angle controller gains (helps drive straight)
        )*/
      .withSensors( //declares rotation sensors; left at port 3 and right on port 5 (reversed)
        RotationSensor{3},
        RotationSensor{5, true}
      )
      //blue gearset, 3.25 inch wheel diameter, 9.5 inch wheelbase (Left-Back to Right-Back Wheel)
      .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 9.75_in}, imev5BlueTPR})
      //3.25in tracking wheel, 15_in distance between encoder wheels, 4090 Ticks Per Rotation
      .withOdometry({{3.25_in, 15.5_in}, 4090})
      //Ignore, this is an experiment
      .withLogger(
        std::make_shared<Logger>(
            TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
            "include/logger.txt", // Output to the PROS terminal
            Logger::LogLevel::debug // Show errors and warnings
        )
      )
      //Builds the chassis
      .buildOdometry(); // build an odometry chassis

      std::shared_ptr<AsyncMotionProfileController> profileController =
        AsyncMotionProfileControllerBuilder()
          .withLimits({

            0.8, // Maximum linear velocity of the Chassis in m/s
            2.0, // Maximum linear acceleration of the Chassis in m/s/s
            5.0 // Maximum linear jerk of the Chassis in m/s/s/s


          })
          .withOutput(chassisAuton)
          .buildMotionProfileController();

          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {5_ft, 0_ft, 0_deg}}, "A5");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {4_ft, 0_ft, 0_deg}}, "A4");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}}, "A2");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {108_in, 0_ft, 0_deg}}, "A1");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {1.5_ft, 0_ft, 0_deg}}, "T1.5");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {1.2_ft, 0_ft, 0_deg}}, "T1.2");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {0.5_ft, 0_ft, 0_deg}}, "T0.5");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {30.25_in, 0_in, 0_deg}}, "S30.25");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {17.5_in, 0_in, 0_deg}}, "S17.5");
          profileController->generatePath({{0_in, 0_in, 0_deg}, {5.5_in, 0_in, 0_deg}}, "S5.5");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {0_ft, 0_ft, 90_deg}}, "T1");
          profileController->generatePath({{0_ft, 0_ft, 0_deg}, {12_ft, 0_ft, 0_deg}}, "TEST");
//
// TODO: double all the values in movement...|
// ALERT: X AND Y ARE SWITCHED SO MAKE SURE YOUR COORDINATES
// REFLECT THAT

  setIntake(127);
  chassisAuton-> setMaxVelocity(70);
  chassisAuton->moveDistance(17.5_in);
  profileController->waitUntilSettled();
  setVIntake(127);
  pros::delay(300);
  setVIntake(0);
  pros::delay (1000);
  //chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-95_deg);

  //chassisAuton->setMaxVelocity(200);
  chassisAuton->moveDistance(11_in);
  profileController->waitUntilSettled();
  setIntake(0);
//  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-47_deg);
  //chassisAuton->setMaxVelocity(120);
  chassisAuton->moveDistance(16_in);
  profileController->waitUntilSettled();
    //First Tower
    setVIntake(-127);
    pros::delay(1100);
    setVIntake(0);
    pros::delay(200);
  chassisAuton->moveDistance(-16_in);
  profileController->waitUntilSettled();
//-------------------------------------\\
  chassisAuton->setMaxVelocity(60);
  chassisAuton->turnAngle(147_deg);
  //chassisAuton->setMaxVelocity(120);
  setIntake(127);
  chassisAuton->moveDistance(45_in);
  profileController->waitUntilSettled();
  setIntake(0);
  //chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-98_deg);
  //chassisAuton->setMaxVelocity(120);
  chassisAuton->moveDistance(5.5_in);
  profileController->waitUntilSettled();
    //Second Tower
    setVIntake(-127);
    pros::delay(700);
    setVIntake(0);
    chassisAuton->moveDistance(-19_in);
    profileController->waitUntilSettled();
  setIntake(127);
  //-------------------------------------\\
  //chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(93_deg);
  //chassisAuton->setMaxVelocity(120);
  chassisAuton->moveDistance(48_in);
  profileController->waitUntilSettled();
//  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(-90_deg);
//  chassisAuton->setMaxVelocity(120);
  chassisAuton->moveDistance(11_in);
  profileController->waitUntilSettled();
  setIntake(0);
//  chassisAuton->setMaxVelocity(75);
  chassisAuton->turnAngle(45_deg);
//  chassisAuton->setMaxVelocity(120);
  chassisAuton->moveDistance(14_in);
  profileController->waitUntilSettled();
  //Third Tower
  setVIntake(-127);
  pros::delay(700);
  setVIntake(0);
  chassisAuton->moveDistance(-37.5_in);
  profileController->waitUntilSettled();
  setIntake(127);
  //-------------------------------------\\
setIntake(127);

//-------------------------------------\\
chassisAuton->setMaxVelocity(75);
chassisAuton->turnAngle(-45_deg);
chassisAuton->setMaxVelocity(120);

chassisAuton->moveDistance(1.5_ft);

chassisAuton->moveDistance(-5.5_ft);

chassisAuton->setMaxVelocity(75);
chassisAuton->turnAngle(90_deg);
chassisAuton->setMaxVelocity(120);

setIntake(0);

chassisAuton->moveDistance(0.7_ft);

//Fourth Tower
setVIntake(-127);
pros::delay(700);
setVIntake(0);

chassisAuton->moveDistance(-0.7_ft);
setIntake(127);

//-------------------------------------\\
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
chassisAuton->setMaxVelocity(75);
chassisAuton->turnAngle(135_deg);
chassisAuton->setMaxVelocity(120);

chassisAuton->moveDistance(4_ft);

chassisAuton->setMaxVelocity(75);
chassisAuton->turnAngle(-90_deg);
chassisAuton->setMaxVelocity(120);

setIntake(0);

chassisAuton->moveDistance(0.7_ft);

//Sixth Tower
setVIntake(-127);
pros::delay(700);
setVIntake(0);

chassisAuton->moveDistance(-1.7_ft);
setIntake(127);

//-------------------------------------\\
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
chassisAuton->moveDistance(-40_in);

chassisAuton->setMaxVelocity(75);
chassisAuton->turnAngle(45_deg);
chassisAuton->setMaxVelocity(120);

chassisAuton->moveDistance(0.5_ft);

chassisAuton->moveDistance(-6.5_ft);

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
  //-------------------------------------\\


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
