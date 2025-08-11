#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "lemlib/api.hpp"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

#include "intake.hpp"
#include "flywheel.hpp"


/*
Notes
    - 


*/


//Skills ---------------------------------------------------------









void test_run(){
  //Robot is 15" Wide
  //Robot is 12.5" Long
  //Front of the red part of the parking zone is 57" from the middle line
  //Left Edge of red part of the parking zone is 9.5" from the middle line
  chassis.odom_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  chassis.pid_targets_reset();

  chassis.odom_xyt_set(-17_in, -63.25_in, 0_deg);

  //Start intakes to pick up any game elements that are in the path
  b_intake_speed(-127);
  t_intake_speed(-127);
  
  //Drives Robot to left side neutral zone game element line up
  //When driving to point -36, 0; drive at 30/127 speed to 
  //go slow enough and ensure contact with game elements
  chassis.pid_odom_set({{{-17_in, -39.25_in}, fwd, DRIVE_SPEED},
                        {{-17_in, -24_in}, fwd, DRIVE_SPEED},
                        {{-20_in, 0_in, 270_deg}, fwd, 45},
                        {{-36_in, 0_in}, fwd, 50}},
                       true);
                      
  chassis.pid_wait_until_index(0);
  chassis.pid_speed_max_set(60);
  chassis.pid_wait();

  //Drive Robot to left side match load zone
  //Wait 3000 msec to allow for robot to grab all 
  //match load game elements
  chassis.pid_odom_set({{{-36_in, -24_in}, fwd, DRIVE_SPEED},
                        {{-36_in, -36_in}, fwd, DRIVE_SPEED},
                        {{-48_in, -48_in}, fwd, DRIVE_SPEED},
                        {{-51_in, -62.5_in}, fwd, 65}},
                       true);
  chassis.pid_wait();
  pros::delay(3000);

  //Drive to Left Side High Goal Zone
  chassis.pid_odom_set({{{-50_in, -45_in}, rev, DRIVE_SPEED},
                        {{-50_in, -36_in}, fwd, 75}}, 
                       true);
  chassis.pid_wait();

  t_intake_speed(-127);
  b_intake_speed(-127);
  flywheel_speed(127);
  pros::delay(3000);
  t_intake_speed(0);
  b_intake_speed(0);
  flywheel_speed(0);
}