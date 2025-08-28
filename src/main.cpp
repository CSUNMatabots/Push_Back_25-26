#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "config.h"
#include "controls.h"
#include <iterator>
#include "liblvgl/llemu.hpp"
#include "pros/misc.hpp"
#include "subsystems.hpp"

#include "pros/rotation.hpp"

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

// === 15" BOT CONFIG ===
pros::MotorGroup leftMotors({-8, -6, -9}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({18, 20, 16}, pros::MotorGearset::blue);
// pros::Imu imu(7);
// pros::Rotation horizontalEnc(2);
// pros::Rotation verticalEnc(-1);
lemlib::TrackingWheel horizontalTW(&horizontalEnc, lemlib::Omniwheel::OLD_275, -5.514);
lemlib::TrackingWheel verticalTW(&verticalEnc, lemlib::Omniwheel::OLD_275, 0);
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 12.5, lemlib::Omniwheel::NEW_4, 480, 5);

lemlib::ControllerSettings linearController(7, // proportional gain (kP)
                                            0.01, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0.01, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

lemlib::OdomSensors sensors(&verticalTW, nullptr, &horizontalTW, nullptr, &imu);

lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);


// #ifdef RED_BOT
// // === 24" Bot CONFIG ===
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

int selected_auton = 0;
const char* AUTON_NAMES[] = {"Test", "Left", "Right", "Skills"};
void (*AUTON_FUNCS[])()   = {test_trackingwheels, 
                             auton_left,    
                             auton_right,    
                             auton_skills};

const int NUM_AUTONS  = sizeof(AUTON_FUNCS)/sizeof(AUTON_FUNCS[0]);

bool autonselect = false;

void auton_selector() { 

    if (!autonselect) { 

      //cycle thorugh logic 
      
      if (master.get_digital_new_press(BTN_PREV)) { // Navigate to previous auton
      // Wrap around if at the beginning
        selected_auton = (selected_auton - 1 + NUM_AUTONS) % NUM_AUTONS;
      } else if (master.get_digital_new_press(BTN_NEXT)) { // Navigate to next auton
      // Wrap around if at the end
      selected_auton = (selected_auton + 1) % NUM_AUTONS;
      }

      // master.clear_line(2); //Refresh Display 
      // master.print(2, 0, "Auton: %s", AUTON_NAMES[selected_auton]);
      pros::lcd::print(0, "Auton: %s", AUTON_NAMES[selected_auton]);

      if (master.get_digital_new_press(BTN_CONFIRM)) {
        autonselect = true;
        master.rumble(".");
      }

    }
  
  // master.clear_line(2); // Set the selected autonomous routine
  // master.print(2, 0, "Selected: %s", AUTON_NAMES[selected_auton]); 
  pros::lcd::print(0, "Selected: %s", AUTON_NAMES[selected_auton]);


//once auton locked in, press A again to run

// bool button_confirmed = false;

//   if (autonselect) {

//     pros::lcd::clear();
    
//     while (!button_confirmed) {
//       pros::lcd::print(0, "Selected: %s", AUTON_NAMES[selected_auton]); //flash chosen auton 
//       pros::delay(100);
//       pros::lcd::clear();
//       pros::delay(100);

//       if (master.get_digital_new_press(BTN_CONFIRM)) {
//         button_confirmed = true;
//         master.rumble("..");

//         AUTON_FUNCS[selected_auton]();

//         pros::lcd::print(0, "Locked: %s", AUTON_NAMES[selected_auton]);

//       }

//     pros::delay(100);
    
//     }

//   }   

}

void initialize() {

	pros::lcd::initialize(); // initialize brain screen
	chassis.calibrate();	 // calibrate sensors

  auton_selector();

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
            pros::lcd::print(2, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(3, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(4, "Theta: %f", chassis.getPose().theta); // heading
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


void competition_initialize() {


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

// AUTON_FUNCS[selected_auton]();
test_trackingwheels();


}



bool auton_running = false;

void run_selected_auton() {
    auton_running = true; //Change to auton is in progress
    master.rumble(".");

    AUTON_FUNCS[selected_auton](); //Run the auton 

    auton_running = false; //Auton over
    pros::lcd::clear();
    pros::lcd::print(0, "Auton done: %s", AUTON_NAMES[selected_auton]);

}


//Runs in driver control
void opcontrol()
{
	// controller
	// loop to continuously update motors
	while (true) {
  
  if (!auton_running && BTN_CONFIRM_RUN) {
          run_selected_auton();
      }


  if (!auton_running) {

		int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		// move the chassis with curvature drive
		chassis.tank(leftY, rightY);

//Robot Systems
		// flywheel_control();
		intake_control();
    
		matchload_control();
    // extender_control();

      objectDetectionTask();

    }

    pros::delay(10);

  }
}