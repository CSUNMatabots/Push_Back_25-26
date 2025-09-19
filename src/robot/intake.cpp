#include "intake.hpp"
#include "main.h"
#include "subsystems.hpp"
#include "controls.h"

int m = 0;   // middle intake
int t = 0;   // top intake
int hop = 0; // hopper
int ag = 0;  // agitator


void intake_control() {

  if (ScoreLow_Hopper) {
    // Both back-left buttons: score low from hopper
    hop = 127;
    m   = 127;
    ag  = 127;
    Matchload.set_value(0);      
    Gate.set_value(0);     
  }

  else if (master.get_digital(ScoreTop_Hopper)) {
    // Top out of hopper (L2)
    hop = 127;
    m   = -127;
    t   = -127;
    ag  = 127;
    Matchload.set_value(0);
    Gate.set_value(0);      
  }

  else if (master.get_digital(ScoreMid_Hopper)) {
    // Mid out of hopper (L1)
    hop = 127;
    m   = -127;
    ag  = 127;
    Matchload.set_value(1);
    Gate.set_value(0);     
  }

  else if (master.get_digital(Into_Hopper_Button)) {
    // Feed into hopper (R2)
    m   = -127;
    t   = -127;
    Matchload.set_value(0);
    Gate.set_value(1);
  }

  else {
    // Stop motors (leave pneumatics latched as-is)
    m = t = hop = ag = 0;
  }

  // Apply outputs
  middle_int.move(m);
  top_intake.move(t);
  hopper.move(hop);
  agitator.move(ag);
}

// ============ Auton Code =============

//Use with Intake.ScoreLow_Hop()

void motorMove() {
  middle_int.move(m); top_intake.move(t); hopper.move(hop); agitator.move(ag);
}

void Intake::ScoreLow_Hop() {
  hop = 127;
  m   = 127;
  ag  = 127;
  Matchload.set_value(0);      
  Gate.set_value(0);  
  motorMove();
}

void Intake::ScoreMid_Hop() {
  hop = 127;
  m   = -127;
  ag  = 127;
  Matchload.set_value(1);
  Gate.set_value(0);  
  motorMove();
}

void Intake::ScoreTop_Hop() {
  hop = 127;
  m   = -127;
  t   = -127;
  ag  = 127;
  Matchload.set_value(0);
  Gate.set_value(0); 
  motorMove();  
}

void Intake::Into_Hopper() {
  m   = -127;
  t   = -127;
  Matchload.set_value(0);
  Gate.set_value(1);
  motorMove();
}

void Intake::StopAll() {
    m = t = hop = ag = 0;
    motorMove();
}



// bool roller_state = false;

// int angle_moved = 0;
// double start_angle;
// double end_angle;

// // =======Bottom Intake Code========
// void b_intake_speed(int speed){
//     bottom_intake.move(speed);
// }

// void b_intake_set_pos(double pos, int speed){
//     bottom_intake.move_absolute(pos, speed);
// }

// void b_intake_delay(int speed, int delay){
//     bottom_intake.move(speed);
//     pros::delay(delay);
//     bottom_intake.move(0);
// }

// void b_intake_reset(){
//     bottom_intake.tare_position();
// }

// =======Middle Intake Code========
// void m_intake_speed(int speed){
//     middle_int.move(speed);
// }

// void m_intake_set_pos(double pos, int speed){
//     middle_int.move(speed);
// }

// void m_intake_delay(int speed, int delay){
//     middle_int.move(speed);
//     pros::delay(delay);
//     middle_int.move(speed);
// }

// void m_intake_reset(){
//     middle_int.tare_position();
// }

// // =======Top Intake Code========
// void t_intake_speed(int speed){
//     top_intake.move(speed);
// }

// void t_intake_set_pos(double pos, int speed){
//     top_intake.move_absolute(pos, speed);
// }

// void t_intake_delay(int speed, int delay){
//     top_intake.move(speed);
//     pros::delay(delay);
//     top_intake.move(0);
// }

// void t_intake_reset(){
//     top_intake.tare_position();
// }

// // =======Roller Intake Code========
// void roller_speed(int speed){
//     hopper.move(speed);
// }

// void roller_set_pos(double pos, int speed){
//     hopper.move_absolute(pos, speed);
// }

// void roller_delay(int speed, int delay){
//     hopper.move(speed);
//     pros::delay(delay);
//     hopper.move(0);
// }

// void roller_reset(){
//     hopper.tare_position();
// }


