#include "intake.hpp"
#include "main.h"
#include "subsystems.hpp"

void intake_control(){ // Uses back buttons
    // int b = 0;
    int m = 0;
    int t = 0;
    int ml = 0;
    int hop = 0;
    int ag = 0;
    int fly = 0; 

    if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_L2) ) { // Check combo case first
        // Both Left Back Buttons -- Take out hopper, score out-low 
        hop = 127;
        m   = 127;
        ag  = 127;
        ml = 127;
        piston.set_value(0);

    } else if (master.get_digital(DIGITAL_L2)) {
        // Left Back Button -- Take out hopper, score out-high
        hop = 127;
        m   = -127;
        t   = -127;
        ag  = 127;
        fly = 127;
        piston.set_value(0);
    
    } else if (master.get_digital(DIGITAL_L1)) {
        // Left Front Button -- Take out hopper, score out-mid
        hop = 127;
        m   = -127;
        ag  = 127;
        piston.set_value(0); 

    } else if (master.get_digital(DIGITAL_R2)) {
        // Right Front Button -- Score High
        m = -127;
        t = -127;
        ml = 127;
        fly = 127; 
        piston.set_value(0);

    } else if (master.get_digital(DIGITAL_R1)) {
        // Right Back Button -- Score Low
        m = 127;
        t = 127;
        ml = -127;
        piston.set_value(0);

    } else {
        // Stop everything
        m = t = ml = hop = ag = fly = 0;
    }

    middle_intake.move(m);
    top_intake.move(t);
    matchload.move(ml);
    hopper.move(hop);
    agitator.move(ag);
    flywheel.move(fly);
}


// ============ Auton Code =============


bool roller_state = false;

int angle_moved = 0;
double start_angle;
double end_angle;

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
void m_intake_speed(int speed){
    middle_intake.move(speed);
}

void m_intake_set_pos(double pos, int speed){
    middle_intake.move_absolute(pos, speed);
}

void m_intake_delay(int speed, int delay){
    middle_intake.move(speed);
    pros::delay(delay);
    middle_intake.move(0);
}

void m_intake_reset(){
    middle_intake.tare_position();
}

// =======Top Intake Code========
void t_intake_speed(int speed){
    top_intake.move(speed);
}

void t_intake_set_pos(double pos, int speed){
    top_intake.move_absolute(pos, speed);
}

void t_intake_delay(int speed, int delay){
    top_intake.move(speed);
    pros::delay(delay);
    top_intake.move(0);
}

void t_intake_reset(){
    top_intake.tare_position();
}

// =======Roller Intake Code========
void roller_speed(int speed){
    hopper.move(speed);
}

void roller_set_pos(double pos, int speed){
    hopper.move_absolute(pos, speed);
}

void roller_delay(int speed, int delay){
    hopper.move(speed);
    pros::delay(delay);
    hopper.move(0);
}

void roller_reset(){
    hopper.tare_position();
}



// =======Changer Intake Code========
// void changer_speed(int speed){
//     changer.move(speed);
// }

// void changer_set_pos(double pos, int speed){
//     changer.move_absolute(pos, speed);
// }

// void changer_delay(int speed, int delay){
//     changer.move(speed);
//     pros::delay(delay);
//     changer.move(0);
// }

// void changer_reset(){
//     changer.tare_position();
// }

// void changer_open(){
//     //1350 for goal scoring and 550 for back basket
//     // changer.move(50);
//     // while (!(pot.get_value() > 1300 && pot.get_value() < 1400)){
//     //     pros::delay(2);
//     // }
//     // changer.move(0);
//     if (angle_moved == 0){
//         start_angle = potensh.get_angle();
//         end_angle = start_angle + 35;
//         changer.move(50);
//         while (!(potensh.get_angle() > end_angle)){
//             pros::delay(2);
//         }
//         changer.move(2);
//         start_angle = end_angle = 0;
//         angle_moved = 1;
//     }
// }

// void changer_close(){
//     //1350 for goal scoring and 550 for back basket
//     // changer.move(-50);
//     // while (!(pot.get_value() > 500 && pot.get_value() < 600)){
//     //     pros::delay(2);
//     // }
//     // changer.move(0);

//     if (angle_moved == 1){
//         start_angle = potensh.get_angle();
//         end_angle = start_angle - 35;
//         changer.move(50);
//         while (!(potensh.get_angle() < end_angle)){
//             pros::delay(2);
//         }
//         changer.move(2);
//         start_angle = end_angle = 0;
//         angle_moved = 0;
//     }
// }

