#include "main.h"
#include "subsystems.hpp"
#include "matchload.hpp"
#include "controls.h"


bool pistonExtended = false; 

void matchload_control() { 
    if (master.get_digital_new_press(Matchload_Button)) {
        pistonExtended = !pistonExtended;  // Toggle state
        
        if (pistonExtended) {
            piston.set_value(1);  // extend piston
            matchload.move(-127); 
        } else {
            piston.set_value(0);  // retract piston
        }
    }
}

// bool Extended = false;

// void extender_control() { 
//     if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
//         Extended = !Extended;  // Toggle state
        
//         if (Extended) {
//             ejector.set_value(1);  // extend piston
//         } else {
//             ejector.set_value(0);  // retract piston
//         }
//     }
// }