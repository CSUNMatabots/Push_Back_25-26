#ifndef CONTROLS_H
#define CONTROLS_H

// #include "api.h"

//Robot Systems
#define ScoreTop_Hopper pros::E_CONTROLLER_DIGITAL_L2
#define Into_Hopper_Button pros::E_CONTROLLER_DIGITAL_R2
#define Matchload_Button pros::E_CONTROLLER_DIGITAL_R1
#define ScoreMid_Hopper pros::E_CONTROLLER_DIGITAL_L1
#define switch_auton_button pros::E_CONTROLLER_DIGITAL_A

//Auton Selector
#define BTN_PREV pros::E_CONTROLLER_DIGITAL_LEFT
#define BTN_NEXT pros::E_CONTROLLER_DIGITAL_RIGHT
#define BTN_CONFIRM pros::E_CONTROLLER_DIGITAL_A
#define BTN_CONFIRM_RUN ( master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && \
                          master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && \
                          master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) )


#endif 