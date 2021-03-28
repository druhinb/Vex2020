#include "vex.h"
#include "drive.h"

using namespace std;
//NOTE: All units are in either inches or radians


//Pi, a constant used throughout this program
double pi = 3.14159;
//The radius of the wheel (change 3.25 to whatever the diameter is) 
double wheelRadius = 3.25;
//Horizontal distance between the encoder wheels
double wheelTrack = 30.1;
//Total rEncoderValue
double rEncoderValue;
//The previous value of the rEncoder (used to compensate for overflow)
double rEncoder_PREV_VALUE = -1;

//ditto; see above
double lEncoderValue;
double lEncoder_PREV_VALUE = -1;

//The threshold within which it is reasonable to stop movement
double stopThreshold = 1;

//The threshold within which it is reasonable to stop turning
double angleStopThreshold = 3;

//Robot's current target angle and whether or not it is moving right now
double currTargetAngle = 10;
bool movementActive = false;


//Resets the positions of the left and right encoders
//and also resets the total variables to 0
void tareEncoders()
{
  rEncoder.resetPosition();
  lEncoder.resetPosition();
  rEncoder_PREV_VALUE = 0;
  lEncoder_PREV_VALUE = 0;
  rEncoderValue = 0;
  lEncoderValue = 0;
}

//Updates the angles of the encoders
void encoderAngleUpdate()
{ 
      //If the current angle of the encoder is less than the previous value
      //(signifying that it has overflowed past 360 back to 0...)
      if(rEncoder.position(rotationUnits::deg) < rEncoder_PREV_VALUE)
      {
        //add the remaining difference between the previous angle and 360 as well as
        //the overflow amount to get the actual angle of the encoder in total ticks
        rEncoderValue += (360 - rEncoder_PREV_VALUE) + rEncoder.position(rotationUnits::deg);
        rEncoder_PREV_VALUE = rEncoder.position(rotationUnits::deg);
      }
      else if (rEncoder.position(rotationUnits::deg) >= rEncoder_PREV_VALUE)
      {
        
        rEncoderValue += rEncoder.position(rotationUnits::deg) - rEncoder_PREV_VALUE;
      }

      if(lEncoder.position(rotationUnits::deg) < lEncoder_PREV_VALUE)
      {
        lEncoderValue += (360 - lEncoder_PREV_VALUE) + lEncoder.position(rotationUnits::deg);
        lEncoder_PREV_VALUE = lEncoder.position(rotationUnits::deg);
      }
      else if (lEncoder.position(rotationUnits::deg) >= rEncoder_PREV_VALUE)
      {
        lEncoderValue += lEncoder.position(rotationUnits::deg) - lEncoder_PREV_VALUE;
      }
      lEncoder_PREV_VALUE = lEncoder.position(rotationUnits::deg);
      rEncoder_PREV_VALUE = rEncoder.position(rotationUnits::deg);
}

void checkOvershoot()
{
  //If robot is not moving and the target angle isn't 0 (currrnt angle)...
  if(movementActive == false && currTargetAngle > 0)
  {
    double direction = 1;
    //Curent rotation of the robot (relative to last reset)
    double currentAngle = fabs((((direction) * (lEncoder.position(rotationUnits::deg) * pi / 180) * (pi * wheelRadius)) - ((direction) * (rEncoderValue * pi/180) * (pi * wheelRadius))) / wheelTrack) * 180/pi;
    while (fabs(currTargetAngle - currentAngle) > 3)
    {
      encoderAngleUpdate();
      currentAngle = fabs((((direction) * (lEncoder.position(rotationUnits::deg) * pi / 180) * (pi * wheelRadius)) - ((direction) * (rEncoder.position(rotationUnits::deg) * pi/180) * (pi * wheelRadius))) / wheelTrack) * 180/pi;
      //Finds which direction to turn to correct the movement, clockwise if angle is too little, counter
      //clockwise if the angle is too large
      direction = fabs(currTargetAngle - currentAngle) / currTargetAngle - currentAngle;
      setDrive(direction * 5, direction * 5);
      Brain.Screen.print(currentAngle);
      Brain.Screen.print(" ");
      vex::wait(500, msec);
    }
  }
}

void transcribe(int units, int velocity, bool reversed)
{
  movementActive = true;
  tareEncoders();
  //If reversed, switch the direction to backwards and set the drive to go back
  int direction = reversed ? -1 : 1;
  setDrive(direction * velocity, -(direction * velocity));

  //While the difference between units to travel and circumference of tracking wheel
  //covered is greater than some threshold amount...
  while(fabs(units - fabs((pi * wheelRadius * (rEncoder.position(rotationUnits::deg) / 360)))) > 1.5)
  {
    //Update the encoder angles, delay to let the motors handle the input
    Brain.Screen.print(rEncoder.position(rotationUnits::deg));
    Brain.Screen.print(" ");
    vex::wait(50, msec);
  } 
  //When movement is complete, stop bot, and check for any overshoot
  setDrive(0, 0);
  movementActive = false;
}

void rotate(int degrees, int velocity, bool reversed)
{
  //Sets the target angle for the Overshoot() function
  currTargetAngle = degrees;
  movementActive = true;
  tareEncoders();
  double direction = reversed ? -1 : 1;
  //If direction is reversed, reverses the direction of the drive
  setDrive(direction * velocity, direction * velocity);
  //While the difference between target angle and current angle (calculated as L - R / W) is greater than some threshold...
  double currentAngle = fabs(
    ((direction) * (lEncoder.position(rotationUnits::deg) * (pi / 180) * (wheelRadius / 2))) - 
    ((direction) * (rEncoder.position(rotationUnits::deg) * (pi / 180) * (wheelRadius / 2))) 
    / wheelTrack) * (180/pi);
  while(degrees - currentAngle > 5)
  {
    currentAngle = fabs(
    ((direction) * (lEncoder.position(rotationUnits::deg) * (pi / 180) * (wheelRadius / 2))) - 
    ((direction) * (rEncoder.position(rotationUnits::deg) * (pi / 180) * (wheelRadius / 2))) 
    / wheelTrack) * (180/pi);
     
    Brain.Screen.print(" L: ");
    Brain.Screen.print(degrees - currentAngle );
    //Wait to not overwhelm the CPU
    vex::wait(50, msec);
  } 
  //Stop the robot and check for any overshoot
  setDrive(0, 0);
  movementActive = false;
}

