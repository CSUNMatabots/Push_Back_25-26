#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "controls.h"
#include "liblvgl/llemu.hpp"
#include "pros/imu.h"
#include "pros/misc.hpp"
#include "subsystems.hpp"
#include "autons.hpp"

#include "robot/intake.hpp"
#include "robot/color_detection.hpp"
#include "odometry.hpp"

#include "pros/apix.h"
#include <cstdio>
#include <iostream>
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
pros::MotorGroup leftMotors({-8, -9, -10}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({18, 19, 20}, pros::MotorGearset::blue);

lemlib::TrackingWheel horizontalTW(&horizontalEnc, 2, -5.514);
lemlib::TrackingWheel verticalTW(&verticalEnc, 2, 0);
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 12.5, lemlib::Omniwheel::NEW_4, 480, 5);

lemlib::ControllerSettings linearController(16, // proportional gain (kP)
                                            0.1, // integral gain (kI)
                                            150, // derivative gain (kD)
                                            3, // anti windup
                                            0.25, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            1, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            16 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2.8, // proportional gain (kP)
                                             0.06, // integral gain (kI)
                                             2.8, // derivative gain (kD)
                                             3, // anti windup
                                             0.25, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             0.75, // large error range, in degrees
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
  //pros::lcd::print(0, "Selected: %s", AUTON_NAMES[selected_auton]);


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
  eye.set_led_pwm(100);
  auton_selector();


  // printf("terminal works");
  // std::cout << "cout works" << std::endl;


  	pros::Task screenTask([&]()
						  {
        while (true) {
          update_position();
          // pros::lcd::print(1, "X: %.2f in", x);
          pros::lcd::print(1, "Y: %.2f in", y);
          pros::lcd::print(2, "Theta: %.1f deg", theta);
          pros::delay(50);
            
            
            // pros::lcd::print(4, "Imu: %f", imu.get_heading()); // heading
            // log position telemetry

            // lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources

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

#pragma region Autonomous 

void autonomous() {
Odom_initialize(0, 0, 0);

moveTo(-24, 24, 45);

// pointTurn(45);
// pointTurn(0);




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
void opcontrol() {

  // autonomous();



  while (true) {
    
    // // if (!auton_running && BTN_CONFIRM_RUN) {
    // //         run_selected_auton();
    // //     }

    // if (!auton_running) {



      int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
      int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
      int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
      // move the chassis with curvature drive
      chassis.tank(leftY, rightY);

  //Robot Systems
      intake_control();
      objectDetectionTask();

      }

      pros::delay(10);

}
