#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "config.h"
#include <iterator>

#include "autons.hpp"
#include "robot/flywheel.hpp"
#include "robot/intake.hpp"
#include "robot/color_detection.hpp"
#include "robot/matchload.hpp"

/*
To Do...

- Add an auton selector module 
- Add two robot configurations (black and red bot) and upload the correct one based on the robot you are using
- Use color detection code from last year 
- Add correct auton code


*/





// controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// === BLACK BOT CONFIG ===
pros::MotorGroup leftMotors({-5, 4, -3}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({6, -9, 7}, pros::MotorGearset::blue);
pros::Imu imu(21);
pros::Rotation horizontalEnc(20);
pros::Rotation verticalEnc(-11);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 12.5, lemlib::Omniwheel::NEW_4, 480, 5);

lemlib::ControllerSettings linearController(7, // proportional gain (kP)
                                                0.07, // integral gain (kI)
                                                20, // derivative gain (kD)
                                                3, // anti windup
                                                0.25, // small error range, in inches
                                                100, // small error range timeout, in milliseconds
                                                1, // large error range, in inches
                                                500, // large error range timeout, in milliseconds
                                                16 // maximum acceleration (slew)
);
lemlib::ControllerSettings angularController(2.8, // proportional gain (kP)
                                                0.06, // integral gain (kI)
                                                18, // derivative gain (kD)
                                                3, // anti windup
                                                0.5, // small error range, in degrees
                                                100, // small error range timeout, in milliseconds
                                                1, // large error range, in degrees
                                                500, // large error range timeout, in milliseconds
                                                0 // maximum acceleration (slew)
);

lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);

lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);


// #ifdef RED_BOT
// // === RED BOT CONFIG ===
// pros::MotorGroup leftMotors({1, -2, 3}, pros::MotorGearset::blue);
// pros::MotorGroup rightMotors({-8, 7, 6}, pros::MotorGearset::blue);
// pros::Imu imu(16);
// pros::Rotation horizontalEnc(19);
// pros::Rotation verticalEnc(-12);
// lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -6.0);
// lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -3.0);
// lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 11, lemlib::Omniwheel::NEW_4, 360, 2);

// lemlib::ControllerSettings linearController(12, 0, 4, 3, 1, 100, 3, 500, 15);
// lemlib::ControllerSettings angularController(2.5, 0.1, 8, 3, 1, 100, 3, 500, 0);

// lemlib::OdomSensors sensors(&vertical, nullptr, &horizontal, nullptr, &imu);

// lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
// lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);

// lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);
// #endif



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize(); // initialize brain screen
	chassis.calibrate();	 // calibrate sensors

	// the default rate is 50. however, if you need to change the rate, you
	// can do the following.
	// lemlib::bufferedStdout().setRate(...);
	// If you use bluetooth or a wired connection, you will want to have a rate of 10ms

	// for more information on how the formatting for the loggers
	// works, refer to the fmtlib docs

	// thread to for brain screen and position logging
	pros::Task screenTask([&]()
						  {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        } });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */

int selected_auton = 0;
const char* AUTON_NAMES[] = {"Left", "Right", "Skills"};
void (*AUTON_FUNCS[])()   = {auton_left,    auton_right,    auton_skills};
const int NUM_AUTONS  = sizeof(AUTON_FUNCS)/sizeof(AUTON_FUNCS[0]);


void competition_initialize() {
// Auton selector when connected to field control

const auto BTN_PREV    = pros::E_CONTROLLER_DIGITAL_LEFT;
const auto BTN_NEXT    = pros::E_CONTROLLER_DIGITAL_RIGHT;
const auto BTN_CONFIRM = pros::E_CONTROLLER_DIGITAL_A;

pros::lcd::initialize(); // Initialize the LCD screen


  while (true) {
    if (master.get_digital_new_press(BTN_PREV)) { // Navigate to previous auton
	  // Wrap around if at the beginning
      selected_auton = (selected_auton - 1 + NUM_AUTONS) % NUM_AUTONS;
    } else if (master.get_digital_new_press(BTN_NEXT)) { // Navigate to next auton
	  // Wrap around if at the end
	  selected_auton = (selected_auton + 1) % NUM_AUTONS;
	}
   

    // Refresh display
    master.clear_line(2);
    master.print(2, 0, "Auton: %s", AUTON_NAMES[selected_auton]);
    pros::lcd::print(0, "Auton: %s", AUTON_NAMES[selected_auton]);

        if (master.get_digital_new_press(BTN_CONFIRM)) {
            master.rumble(".");
            break;
        }
        pros::delay(100);
    }

  // Set the selected autonomous routine
  master.clear_line(2);
  master.print(2, 0, "Selected: %s", AUTON_NAMES[selected_auton]);
  pros::lcd::print(0, "Selected: %s", AUTON_NAMES[selected_auton]);



}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
	
AUTON_FUNCS[selected_auton]();


}

/**
 * Runs in driver control
 */
void opcontrol()
{
	// controller
	// loop to continuously update motors
	while (true)
	{
		// get joystick positions
		int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		// move the chassis with curvature drive
		chassis.tank(leftY, rightY);
		// delay to save resources
    
		flywheel_control();
		intake_control();
		piston_control();
		roller_control();

		pros::delay(10);
	}
}