#include "main.h"

//Motor Functions
void setDrive(int left, int right);

void resetDriveEncoders();

double averageDriveEncoderValue();
//Driver Control Functions
void setDriveMotors();

void setAllBrake();

//Auton Functions
void transcribe(int units, int voltage);

void rotate(int degrees, int voltage);
