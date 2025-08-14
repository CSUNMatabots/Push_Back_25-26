#include "main.h"
#include "subsystems.hpp"
#include "matchload.hpp"


bool pistonExtended = false; // Declare outside the function to remember state

void piston_control() { 
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        pistonExtended = !pistonExtended;  // Toggle state
        
        if (pistonExtended) {
            piston.set_value(1);  // extend piston
        } else {
            piston.set_value(0);  // retract piston
        }
    }
}

void roller_control() {
    if (master.get_digital(DIGITAL_B)) {
        matchload.move(127);
    } 
    else if (master.get_digital(DIGITAL_Y)) {
        matchload.move(-127);
    } 
    else {
        matchload.move(0);
    }
}