#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "lemlib/api.hpp"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

#include "robot/intake.hpp"
#include "robot/flywheel.hpp"


/*
Notes
    - 


*/


//Skills ---------------------------------------------------------



int DRIVE_SPEED = 127; //Default drive speed for the robot




void test_trackingwheels() {

// pros::Imu& get_imu(); 

lemlib::MoveToPointParams speedParams = {.maxSpeed = 100};

chassis.setPose(0, 0, 0);

chassis.moveToPoint(0, 24, 2000);
chassis.waitUntilDone();

chassis.moveToPoint(0, 0, 2000, {.forwards = false});
chassis.waitUntilDone();



pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);

    
}



void test_run(){
//Robot is 15" Wide
//Robot is 12.5" Long
//Front of the red part of the parking zone is 57" from the middle line
//Left Edge of red part of the parking zone is 9.5" from the middle line

lemlib::MoveToPointParams params = {.forwards = true};
lemlib::MoveToPointParams speedParams = {.maxSpeed = 127};

chassis.setPose(-17, -63.25, 0);

//Start intakes to pick up any game elements that are in the path
b_intake_speed(-127);
t_intake_speed(-127);
  
    // --- Block 1: go slow, ensure contact ---
    chassis.moveToPoint(-17, -39.25, 2000);
    chassis.waitUntilDone();

    chassis.moveToPoint(-17, -24, 2000);
    chassis.waitUntilDone();

    chassis.moveToPose (-20, 0, 270, 2500);        // heading specified
    chassis.waitUntilDone();

    chassis.moveToPoint( 36, 0, 2500);     
    chassis.waitUntilDone();
    

    // --- Block 2: to left match-load zone ---
    chassis.moveToPoint(-36, -24,   2000);
    chassis.waitUntilDone();

    chassis.moveToPoint(-36, -36,   2000);
    chassis.waitUntilDone();

    chassis.moveToPoint(-48, -48,   2500);
    chassis.waitUntilDone();

    chassis.moveToPoint(-51, -62.5, 3000);
    chassis.waitUntilDone();

    pros::delay(3000); // wait to collect

    // --- Block 3: to left high-goal zone ---
    chassis.moveToPoint(-50, -45, 2500); 
    chassis.waitUntilDone();

  
    chassis.moveToPoint(-50, -36, 2000);
    chassis.waitUntilDone();


    // shooter/intakes like your original
    t_intake_speed(-127);
    b_intake_speed(-127);
    flywheel_speed(127);
    pros::delay(3000);
    t_intake_speed(0);
    b_intake_speed(0);
    flywheel_speed(0);
}





void auton_left() {}
void auton_right() {}
void auton_skills() {}





















//   //Drives Robot to left side neutral zone game element line up
//   //When driving to point -36, 0; drive at 30/127 speed to 
//   //go slow enough and ensure contact with game elements
//   chassis.pid_odom_set({{{-17_in, -39.25_in}, fwd, DRIVE_SPEED},
//                         {{-17_in, -24_in}, fwd, DRIVE_SPEED},
//                         {{-20_in, 0_in, 270_deg}, fwd, 45},
//                         {{-36_in, 0_in}, fwd, 50}},
//                        true);
                      
//   chassis.pid_wait_until_index(0);
//   chassis.pid_speed_max_set(60);
//   chassis.pid_wait();

//   //Drive Robot to left side match load zone
//   //Wait 3000 msec to allow for robot to grab all 
//   //match load game elements
//   chassis.pid_odom_set({{{-36_in, -24_in}, fwd, DRIVE_SPEED},
//                         {{-36_in, -36_in}, fwd, DRIVE_SPEED},
//                         {{-48_in, -48_in}, fwd, DRIVE_SPEED},
//                         {{-51_in, -62.5_in}, fwd, 65}},
//                        true);
//   chassis.pid_wait();
//   pros::delay(3000);

//   //Drive to Left Side High Goal Zone
//   chassis.pid_odom_set({{{-50_in, -45_in}, rev, DRIVE_SPEED},
//                         {{-50_in, -36_in}, fwd, 75}}, 
//                        true);
//   chassis.pid_wait();

//   t_intake_speed(-127);
//   b_intake_speed(-127);
//   flywheel_speed(127);
//   pros::delay(3000);
//   t_intake_speed(0);
//   b_intake_speed(0);
//   flywheel_speed(0);
// }