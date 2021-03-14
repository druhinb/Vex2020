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
  Logger::setDefaultLogger(
    std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "include/logger.txt", // Output to the PROS terminal
        Logger::LogLevel::warn // Show errors and warnings
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
  pros::Rotation l(3);
  pros::Rotation r(5);
  l.reset_position(); r.reset_position();

  std::shared_ptr<OdomChassisController> chassisAuton = ChassisControllerBuilder()
      .withMotors(
        {1, 12}, //left motors are ports 1 and 2
        {-10, -19}
      )  //right motors are ports 10 and 19
      .withSensors( //declares rotation sensors; left at port 3 and right on port 5 (reversed)
        RotationSensor{3},
        RotationSensor{5, true}
      )
      //blue gearset, 3.25 inch wheel diameter, 9.5 inch wheelbase (Left-Back to Right-Back Wheel)
      .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 9.75_in}, imev5BlueTPR})
      //3.25in tracking wheel, 15_in distance between encoder wheels, 4090 Ticks Per Rotation
      .withOdometry({{3.25_in, 15.5_in}, quadEncoderTPR})
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

//
// TODO: double all the values in movement...|
// ALERT: X AND Y ARE SWITCHED SO MAKE SURE YOUR COORDINATES
// REFLECT THAT
/*
  Functions Available
  ===================
  chassisAuton->moveToPoint({y_units, x_units});
  chassisAuton->turnToPoint({y_units, x_units});
  chassisAuton->setState({y_units, x_units, angle_units})
  chassisAuton->setMaxVelocity({0-200});
  pros::delay(delay_milliseconds);
  setIntake(0-127);
  setVIntake(0-127);
  ==================
*/

//Sets the starting state (center of the drivetrain)
chassisAuton->setState({6.5_in, 36_in, 0_deg});

//Starts up the intake
setIntake(127);

//Delay to give the chassis time to configure
pros::delay(900);

//Sets the max velocity
chassisAuton->setMaxVelocity(100);

//---------------------------------------------------\\
//First tower code
//---------------------------------------------------\\

chassisAuton->driveToPoint({24_in, 36_in});
std::cout<<r.get_position();
std::cout<<l.get_position();


  //Brings up the ball so it doesn't get stuck
  setVIntake(127);
  pros::delay(300);
  setVIntake(0);


chassisAuton->driveToPoint({24_in, 24_in});


  setIntake(0);

chassisAuton->driveToPoint({15_in, 15_in});
chassisAuton->setState({15_in, 15_in, -135_deg});

  //First tower
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);

//---------------------------------------------------Second tower code

chassisAuton->driveToPoint({24_in, 24_in}, true);
chassisAuton->setState({24_in, 24_in, -135_deg});

  setIntake(127);

chassisAuton->driveToPoint({72_in, 24_in});
chassisAuton->setState({72_in, 24_in, 0_deg});

  pros::delay(100);
  setIntake(0);

chassisAuton->driveToPoint({72_in, 16_in});

  //Second tower
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);

chassisAuton->setState({72_in, 16_in, -90_deg});

//---------------------------------------------------\\
//Third tower code
//---------------------------------------------------\\
chassisAuton->driveToPoint({72_in, 36_in}, true);
chassisAuton->setState({72_in, 36_in, -90_deg});

  setIntake(127);

chassisAuton->setMaxVelocity(50);
chassisAuton->driveToPoint({120_in, 36_in});
chassisAuton->setMaxVelocity(100);
chassisAuton->setState({120_in, 36_in, 0_deg});

chassisAuton->driveToPoint({120_in, 24_in});
chassisAuton->setState({120_in, 24_in, -90_deg});

  pros::delay(200);
  setIntake(0);

chassisAuton->driveToPoint({130_in, 14_in});

  //Third tower
  setVIntake(-127);
  pros::delay(1500);
  setVIntake(0);

//---------------------------------------------------\\
//Fourth tower code
//---------------------------------------------------\\
chassisAuton->setState({130_in, 14_in, -45_deg});
chassisAuton->driveToPoint({108_in, 36_in}, true);

setIntake(127);

chassisAuton->setState({108_in, 36_in, -50_deg});

chassisAuton->driveToPoint({108_in, 16_in});
chassisAuton->setState({108_in, 16_in, -90_deg});

//Bang into the wall to correct
chassisAuton->moveDistanceAsync(24_in);
pros::delay(1000);
chassisAuton->stop();

chassisAuton->setState({108_in, 11.5_in, -90_deg});

chassisAuton->driveToPoint({108_in, 72_in}, true);
chassisAuton->setState({108_in, 72_in, -90_deg});

setIntake(0);

chassisAuton->driveToPoint({130_in, 72_in});
chassisAuton->setState({130_in, 72_in, 0_deg});

  //Fourth tower
  setVIntake(-127);
  pros::delay(1000);
  setVIntake(0);

//---------------------------------------------------\\
//Fifth tower code
//---------------------------------------------------\\
chassisAuton->driveToPoint({120_in, 72_in}, true);
chassisAuton->setState({120_in, 72_in, 0_deg});

setIntake(127);

chassisAuton->driveToPoint({120_in, 123_in});
chassisAuton->setState({120_in, 126_in, 90_deg});

setIntake(0);

chassisAuton->driveToPoint({132_in, 132_in});
chassisAuton->setState({132_in, 132_in, 45_deg});

  //Fifth tower
  setVIntake(-127);
  pros::delay(1500);

//Move away from the fifth tower
chassisAuton->driveToPoint({8_ft, 8_ft});



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
