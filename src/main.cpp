#include "main.h"

#define LEFT_FRONT_WHEEL_PORT 1
#define RIGHT_FRONT_WHEEL_PORT 1
#define LEFT_BACK_WHEEL_PORT 1
#define RIGHT_BACK_WHEEL_PORT 1

#define VERTICAL_INTAKE_PORT 10
#define R_HORIZONTAL_INTAKE_PORT 8
#define L_HORIZONTAL_INTAKE_PORT 3

#define LEFT_BUMPER_PORT 'a'
#define RIGHT_BUMPER_PORT 'b'

void on_center_button()
{
  //not important...
}


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "SKYNET INITIATED. LAUNCHING NUCLEAR WEAPONS.");

	pros::lcd::register_btn1_cb(on_center_button);
}

//not important...
void disabled() {}

//not important...
void competition_initialize() {}

//todo later
void autonomous() {}


//Main driving control schematics
 void opcontrol() {
	 //Declaration of all motors and such
   pros::Motor LF_drive (LEFT_FRONT_WHEEL_PORT);
   pros::Motor LB_drive (LEFT_BACK_WHEEL_PORT);
	 pros::Motor RB_drive (RIGHT_BACK_WHEEL_PORT);
	 pros::Motor RF_drive (RIGHT_FRONT_WHEEL_PORT);
   pros::Motor vertical_intake(VERTICAL_INTAKE_PORT, MOTOR_GEARSET_06);
   pros::Motor r_horizontal_intake (R_HORIZONTAL_INTAKE_PORT, true);
	 pros::Motor l_horizontal_intake (L_HORIZONTAL_INTAKE_PORT, true);

   pros::ADIDigitalIn left_bumper (LEFT_BUMPER_PORT);
   pros::ADIDigitalIn right_bumper (RIGHT_BUMPER_PORT);

   pros::Controller master (CONTROLLER_MASTER);

	 //Delcaration of variables
	 float motor_speed = 1.0f;
	 int y_left_stick;
   int y_right_stick;
	 int threshold = 5;

   while (true)
	 {
		 //Checking joystick values to ensure elimination of "drift"
		 if (abs(master.get_analog(ANALOG_LEFT_Y)) > threshold)
		 {
			 y_left_stick = master.get_analog(ANALOG_LEFT_Y);
		 }
		 else
		 {
			 y_left_stick = 0;
			 LF_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
			 RF_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
			 LB_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
			 RB_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
		 }

		 if (abs(master.get_analog(ANALOG_LEFT_X)) > threshold)
		 {
			 y_right_stick = master.get_analog(ANALOG_LEFT_X);
		 }
		 else
		 {
			 y_right_stick = 0;
			 LF_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
			 RF_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
			 LB_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
			 RB_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
		 }

		 //Computation for lateral movement
		 //FIRST ONE IS TANK, SECOND ONE IS ARCADE, UNCOMMENT AND RECOMMENT AS YOU SEE FIT.
		 LF_drive.move(motor_speed * y_left_stick);
		 LB_drive.move(motor_speed * y_right_stick);
		 RF_drive.move(motor_speed * y_left_stick);
		 RB_drive.move(motor_speed * y_right_stick);

		 /*
		 LF_drive.move(motor_speed * y_left_stick + y_right_stick);
		 LF_drive.move(motor_speed * y_left_stick + y_right_stick)
		 LF_drive.move(motor_speed * y_left_stick - y_right_stick)
		 LF_drive.move(motor_speed * y_left_stick - y_right_stick)
     */

		 //Horizontal Intaking/Outtaking, will hold when no input detected
     if (master.get_digital(DIGITAL_L1) > 0)
		 {
       // One of the bump switches is currently pressed
    		r_horizontal_intake.move(100);
				l_horizontal_intake.move(100);
     }
		 else if (master.get_digital(DIGITAL_R1))
		 {
			 r_horizontal_intake.move(-100);
			 l_horizontal_intake.move(-100);
		 }
		 else
		 {
			 r_horizontal_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
			 l_horizontal_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
		 }

 	 	 //Vertical Intaking/Outtaking, will hold when no input detected
		 if (master.get_digital(DIGITAL_L2))
		 {
			 vertical_intake.move(600);
		 }
		 else if (master.get_digital(DIGITAL_R2))
		 {
			 vertical_intake.move(-600);
		 }
		 else
		 {
			 vertical_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
		 }

		 //LEGACY INTAKING/OUTTAKING, UNCOMMENT AND RECOMMENT THE ABOVE AS NECESSARY
    /*
		 if (master.get_digital(DIGITAL_R1))
		 {
			 r_horizontal_intake.move(100);
			 l_horizontal_intake.move(100);
			 vertical_intake.move(600);
		 }
		 else if (master.get_digital(DIGITAL_R2))
		 {
			 r_horizontal_intake.move(-100);
			 l_horizontal_intake.move(-100);
			 vertical_intake.move(-600);
		 }
		 else
		 {
			 r_horizontal_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
			 l_horizontal_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
			 vertical_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
		 }
		 */
     pros::delay(2);
   }
 }
