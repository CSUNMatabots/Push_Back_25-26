#include "intake.hpp"
#include "main.h"
#include "subsystems.hpp"
#include "controls.h"


// PRESET TABLE   
const IntakePreset preset = {
    /* top_hop    */ { -127, -127, 127, 127, false, false },
    /* mid_hop    */ { -60,    40, 127, 127, true,  false },
    /* low_hop    */ {  80,    0, 127, 127, false, false },
    /* into_hopper*/ { -127, -127,   0,   0, false, true  },
    /* macthload  */ {-127, -127,   0,   0, true, true  },
    /* stop_all   */ {   0,     0,   0,   0, false, false}, //everything set to 0
    /* stop_motors */{   0,     0,   0,   0}

  };

void IntakeRun(const IntakeConstants& run) {
    middle_int.move(run.m);
    top_intake.move(run.t);
    hopper.move(run.hop);
    agitator.move(run.ag);
    Matchload.set_value(run.matchload);
    Gate.set_value(run.gate);
}

IntakeConstants current_preset = preset.stop_all; //intially set all to 0 

void intake_control() {

  if (ScoreLow_Hopper) { // Both back-left buttons: score low from hopper
    current_preset = preset.low_hop;
  }

  else if (master.get_digital(Matchload_Score)) { // Both back-left buttons: score low from hopper
    current_preset = preset.matchload_score;
  }

  else if (master.get_digital(ScoreTop_Hopper)) {
        current_preset = preset.top_hop;
  }      

  else if (master.get_digital(ScoreMid_Hopper)) {
        current_preset = preset.mid_hop;
  }
        
  else if (master.get_digital(Into_Hopper_Button)) {
        current_preset = preset.into_hopper;
  } 

  else {
    bool keepMatch = current_preset.matchload;
    bool keepGate  = current_preset.gate;

    current_preset = preset.stop_all;    

    current_preset.matchload = keepMatch; // restore pistons
    current_preset.gate      = keepGate;
  }     

  IntakeRun(current_preset);

}

// ============ Auton Code =============





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


