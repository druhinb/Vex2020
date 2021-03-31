#include "drive.h"
#include "vex.h"

using namespace std;
// NOTE: All units are in either inches or radians

// Pi, a constant used throughout this program
double pi = 3.14159;
// The radius of the wheel (change 3.25 to whatever the diameter is)
double wheelRadius = 3.25;
// Horizontal distance between the encoder wheels
double wheelTrack = 6.3;
// Total rEncoderValue
double rEncoderValue;
// The previous value of the rEncoder (used to compensate for overflow)
double rEncoder_PREV_VALUE = -1;

// ditto; see above
double lEncoderValue;
double lEncoder_PREV_VALUE = -1;

// The threshold within which it is reasonable to stop movement
double stopThreshold = 1;

// The threshold within which it is reasonable to stop turning
double angleStopThreshold = 3;

// Robot's current target angle and whether or not it is moving right now
double currTargetAngle = 0;
bool movementActive = false;

// Following are PID variables;
double Kp = 0.5;
double Ki = 0.2;
double Kd = 0.1;

double previous_error = 0.0;
double integral = 0.0;
double derivative = 0.0;

//ignore these two functions, they are experimental
float bernstein(int i, int n, float t) {
  float r = (float)sqrt(n) / (float)(sqrtl(i) * sqrtl(n - i));
  r *= pow(t, i);
  r *= pow(1 - t, n - i);
  return r;
}

void splineGenerator(int x[], int y[]) {
  double xu = 0.0, yu = 0.0, u = 0.0;
  int i = 0;
  for (u = 0.0; u <= 1.0; u += 0.0001) {
    xu = pow(1 - u, 3) * x[0] + 3 * u * pow(1 - u, 2) * x[1] +
         3 * pow(u, 2) * (1 - u) * x[2] + pow(u, 3) * x[3];
    yu = pow(1 - u, 3) * y[0] + 3 * u * pow(1 - u, 2) * y[1] +
         3 * pow(u, 2) * (1 - u) * y[2] + pow(u, 3) * y[3];
    float accvalue = 0.77;
    float T = 0.001f; // the integration time
    float v = 0.0f;   // the starting velocity
    float x = 0.0f;   // the starting position
    float t = 0.0f;   // the increasing time
    if (t < 0.025f) {
      while (t <= 0.25f) { // the main control loop
        float a = accvalue;
        v += a * T;
        x += v * T;
        // use x to feed the motor controller
        // (or store it for later usage)

        // make sure that you wait T seconds
        // to enforce the control rate (use e.g. a thread)
        t += T;
      }
    }
    float delta = 2000.0f / 0.025f;
    float a;
    if (t <= 0.025f) {
      a = delta * t;
    } else if (t <= 0.05f) {
      a = 2000.0f - delta * (t - 0.025);
    }
  }
}

double motionController(double error) {
  integral += error;
  if (error == 0)
    integral = 0;
  if (fabs(error) > 60)
    integral = 0;

  derivative = error - previous_error;
  previous_error = error;
  return (Kp * error) + (Ki * integral) + (Kd * derivative);
}

void resetAllPIDValues() {
  previous_error = 0;
  integral = 0;
  derivative = 0;
}

// Resets the positions of the left and right encoders
// and also resets the total variables to 0
void tareEncoders() {
  rEncoder.resetPosition();
  lEncoder.resetPosition();
  rEncoder_PREV_VALUE = 0;
  lEncoder_PREV_VALUE = 0;
  rEncoderValue = 0;
  lEncoderValue = 0;
}

// Updates the angles of the encoders
void encoderAngleUpdate() {
  // If the current angle of the encoder is less than the previous value
  //(signifying that it has overflowed past 360 back to 0...)
  if (rEncoder.position(rotationUnits::deg) < rEncoder_PREV_VALUE) {
    // add the remaining difference between the previous angle and 360 as well
    // as the overflow amount to get the actual angle of the encoder in total
    // ticks
    rEncoderValue +=
        (360 - rEncoder_PREV_VALUE) + rEncoder.position(rotationUnits::deg);
    rEncoder_PREV_VALUE = rEncoder.position(rotationUnits::deg);
  } else if (rEncoder.position(rotationUnits::deg) >= rEncoder_PREV_VALUE) {

    rEncoderValue +=
        rEncoder.position(rotationUnits::deg) - rEncoder_PREV_VALUE;
  }

  if (lEncoder.position(rotationUnits::deg) < lEncoder_PREV_VALUE) {
    lEncoderValue +=
        (360 - lEncoder_PREV_VALUE) + lEncoder.position(rotationUnits::deg);
    lEncoder_PREV_VALUE = lEncoder.position(rotationUnits::deg);
  } else if (lEncoder.position(rotationUnits::deg) >= rEncoder_PREV_VALUE) {
    lEncoderValue +=
        lEncoder.position(rotationUnits::deg) - lEncoder_PREV_VALUE;
  }
  lEncoder_PREV_VALUE = lEncoder.position(rotationUnits::deg);
  rEncoder_PREV_VALUE = rEncoder.position(rotationUnits::deg);
}

void checkOvershoot() {
  // If robot is not moving and the target angle isn't 0 (currrnt angle)...
  if (movementActive == false && currTargetAngle > 0) {
    double direction = 1;
    double currentVelocity;
    // Curent rotation of the robot (relative to last reset)
    double currentAngle =
        fabs(((direction) * (lEncoder.position(rotationUnits::deg) *
                             (pi / 180) * (wheelRadius / 2))) -
             ((direction) * (rEncoder.position(rotationUnits::deg) *
                             (pi / 180) * (wheelRadius / 2)))) /
        wheelTrack * (180 / pi);
    while (currTargetAngle - currentAngle > 2) {
      currentAngle =
          fabs(((direction) * (lEncoder.position(rotationUnits::deg) *
                               (pi / 180) * (wheelRadius / 2))) -
               ((direction) * (rEncoder.position(rotationUnits::deg) *
                               (pi / 180) * (wheelRadius / 2)))) /
          wheelTrack * (180 / pi);
      // Finds which direction to turn to correct the movement, clockwise if
      // angle is too little, counter clockwise if the angle is too large
      direction =
          fabs(currTargetAngle - currentAngle) / currTargetAngle - currentAngle;
      currentVelocity = 0.3 * motionController(currTargetAngle - currentAngle);
      setDrive(direction * currentVelocity, direction * currentVelocity);
      Brain.Screen.print(currentAngle);
      Brain.Screen.print(" ");
      vex::wait(10, msec);
    }
    setDrive(0, 0);
  }
}

//usage: transcribe(12, false); [will result in the robot moving forwards 12 inches (1 foot)]
void transcribe(double units, int velocity, bool reversed) {
 movementActive = true;
 tareEncoders();
 // If reversed, switch the direction to backwards and set the drive to go back
 double angle = fabs(lEncoder.position(rotationUnits::deg));
 double direction = reversed ? -1 : 1;
 double targetMovement = (units / (pi * wheelRadius)) * 360; 
 // While the difference between units to travel and circumference of tracking
 // wheel covered is greater than some threshold amount...
 while (targetMovement - angle > 3) {
 angle = fabs(lEncoder.position(rotationUnits::deg));
 setDrive(direction * velocity, ((-direction) * velocity));
 // Update the encoder angles, delay to let the motors handle the input
 vex::wait(10, msec);
 }
 // When movement is complete, stop bot, and check for any overshoot
 setDrive(0, 0);
 movementActive = false;
 Brain.Screen.print(lEncoder.position(rotationUnits::deg));
 Brain.Screen.print(targetMovement);
 vex::wait(300, msec);
}
//usage: rotate(90, false); [will result in the robot turning 90 degrees clockwise]
void rotate(int degrees, bool reversed) {
  // Sets the target angle for the Overshoot() function
  resetAllPIDValues();
  currTargetAngle = degrees;
  movementActive = true;
  tareEncoders();
  double direction = reversed ? -1.0 : 1.0;
  double controlVelocity;

  // While the difference between target angle and current angle (calculated as
  // L - R / W) is greater than some threshold...
  double currentAngle =
      (fabs(((direction) * (lEncoder.position(rotationUnits::deg) / 360) * (pi * wheelRadius )) -
           ((direction) * (rEncoder.position(rotationUnits::deg) / 360) * (pi * wheelRadius ))) /
      wheelTrack) * (180 / pi);
  while (degrees - currentAngle > 2) {
    currentAngle =
      (fabs(((direction) * (lEncoder.position(rotationUnits::deg) / 360) * (pi * wheelRadius )) -
           ((direction) * (rEncoder.position(rotationUnits::deg) / 360) * (pi * wheelRadius ))) /
      wheelTrack) * (180 / pi);
    controlVelocity = motionController(degrees - currentAngle);
    // If direction is reversed, reverses the direction of the drive
    setDrive(direction * controlVelocity, direction * controlVelocity);


    // Wait to not overwhelm the CPU
    vex::wait(10, msec);
  }
  // Stop the robot and check for any overshoot
  Brain.Screen.print(currentAngle);
  setDrive(0, 0);
  movementActive = false;
  vex::wait(300, msec);
}