#include "main.h"
#include "subsystems.hpp"
#include "matchload.hpp"

void piston_control() { //toggles the piston state
    bool pistonExtended = false; // track piston state

    if (master.get_digital_new_press(DIGITAL_A)) {
        pistonExtended = !pistonExtended; // flip state
        piston.set_value(pistonExtended); // update piston
    }
}

void roller_control() {
    if (master.get_digital(DIGITAL_B)) {
        matchload.move(127);
    } 
    else if (master.get_digital(DIGITAL_X)) {
        matchload.move(-127);
    } 
    else {
        matchload.move(0);
    }
}