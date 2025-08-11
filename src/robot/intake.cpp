#include "main.h"
#include "subsystems.hpp"

bool roller_state = false;

int angle_moved = 0;
double start_angle;
double end_angle;

// =======Bottom Intake Code========
void b_intake_speed(int speed){
    bottom_intake.move(speed);
}

void b_intake_set_pos(double pos, int speed){
    bottom_intake.move_absolute(pos, speed);
}

void b_intake_delay(int speed, int delay){
    bottom_intake.move(speed);
    pros::delay(delay);
    bottom_intake.move(0);
}

void b_intake_reset(){
    bottom_intake.tare_position();
}

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
    rollers.move(speed);
}

void roller_set_pos(double pos, int speed){
    rollers.move_absolute(pos, speed);
}

void roller_delay(int speed, int delay){
    rollers.move(speed);
    pros::delay(delay);
    rollers.move(0);
}

void roller_reset(){
    rollers.tare_position();
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

void intake_control(){

    //Middle Intake (Rollers that are connected to the storage) Controls
    if (master.get_digital(DIGITAL_UP)){
        middle_intake.move(127);
    }
    else if (master.get_digital(DIGITAL_DOWN)){
        middle_intake.move(-127);
    }
    else{
        middle_intake.move(0);
    }

    
    //Angle Changer Controls
    // if (master.get_digital(DIGITAL_RIGHT)){
    //     //changer_open();
    //     changer.move(30);
    // }
    // else if (master.get_digital(DIGITAL_LEFT)){
    //     //changer_close();
    //     changer.move(-30);
    // }
    // else {
    //     changer.move(5);
    // }

    //Top And Bottom Intake Controls
    // if (master.get_digital(DIGITAL_R1)){
    //     top_intake.move(127);
    //     bottom_intake.move(127);
    // }
    // else if (master.get_digital(DIGITAL_R2)){
    //     top_intake.move(-127);
    //     bottom_intake.move(-127);
    // }
    // else {
    //     top_intake.move(0);
    //     bottom_intake.move(0);
    // }

    if (master.get_digital(DIGITAL_R1)){
        top_intake.move(127);
    }
    else if (master.get_digital(DIGITAL_R2)){
        top_intake.move(-127);
    }
    else {
        top_intake.move(0);
    }

    //Bottom Only Controls
    if (master.get_digital(DIGITAL_L1)){
        bottom_intake.move(127);
    }
    else if (master.get_digital(DIGITAL_L2)){
        bottom_intake.move(-127);
    }
    else {
        //This allows for the bottom roller to still move
        //when either R1 or R2 is pressed
        // if (!(master.get_digital(DIGITAL_R1) || master.get_digital(DIGITAL_R2))){
        //     bottom_intake.move(0);
        // }
        bottom_intake.move(0);
    }

    if (master.get_digital_new_press(DIGITAL_A)){
        roller_state = !roller_state;
    }
    if (roller_state){
        rollers.move(127);
    }
    else{
        rollers.move(0);
    }

}