#include "main.h"

pros::ADIGyro gyro(9);

int getExponentialCurveVal(int joystickValue)
{
  return (1.2 * pow(1.0356, abs(joystickValue)) - 1.2 + 0.2 * abs(joystickValue));
}

void setDrive(int left, int right)
{
  LF_drive = left;
  LB_drive = left;
  RF_drive = right;
  RB_drive = right;
}

void resetDriveEncoders()
{
  LF_drive.tare_position();
  LB_drive.tare_position();
  RF_drive.tare_position();
  RB_drive.tare_position();
}

double averageDriveEncoderValue()
{
  return (fabs(LF_drive.get_position())+
          fabs(LB_drive.get_position())+
          fabs(RF_drive.get_position())+
          fabs(RB_drive.get_position())) / 4;
}
//Driver Control Functions
void setDriveMotors()
{
  setDrive(0, 0);
  int left_joystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  //uncomment out below line for tank control
  //int right_joystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  //comment out the below line to remove arcade control
  int right_joystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  if(abs(left_joystick) < 10)
    left_joystick = 0;
  if (abs(right_joystick) < 10)
    right_joystick = 0;
  //uncomment out the below line for tank control
  //setDrive(left_joystick, right_joystick);

  //comment out the below line to remove arcade control
  setDrive(left_joystick + right_joystick, left_joystick - right_joystick);
}

void setAllBrake()
{
  LB_drive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  RB_drive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  LF_drive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  RF_drive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  l_horizontal_intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  r_horizontal_intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  vertical_intake_L.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  vertical_intake_U.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void transcribe(int units, int voltage)
{
  int direction = abs(units) / units;
  //reset motor encoders
  resetDriveEncoders();
  gyro.reset();
  //drive forward until units are reached
  while(averageDriveEncoderValue() < abs(units))
  {
    //sets the drive to the desired voltage while accounting for the gyro correction
    setDrive(voltage * direction + gyro.get_value(), voltage * direction - gyro.get_value());
    pros::delay(10);
  }
  //brief brake
  setDrive(-10 * direction, -10 * direction);
  pros::delay(50);
  //set drive back to neutral
  setDrive(0, 0);
}

void rotate(int degrees, int voltage)
{
  //calculates direction based on a simple algorithm
  int direction = abs(degrees) / degrees;
  gyro.reset();

//since drive will move at same speed, no need to put it in while loop
  setDrive(-voltage * direction, voltage * direction);
  while(fabs(gyro.get_value()) < abs(degrees * 10) - 50)
    pros::delay(10);

  pros::delay(100);
  //if overshot
  if(fabs(gyro.get_value()) > abs(degrees * 10))
  {
    setDrive(0.5 * voltage * direction, 0.5 * -voltage * direction);
    while(fabs(gyro.get_value()) > abs(degrees * 10))
      pros::delay(10);
  }
  //if undershot
  else if (fabs(gyro.get_value()) < abs(degrees * 10))
  {
    setDrive(0.5 * -voltage * direction, 0.5 * voltage * direction);
    while(fabs(gyro.get_value()) > abs(degrees * 10))
      pros::delay(10);
  }

  //stops drive
  setDrive(0, 0);
}
