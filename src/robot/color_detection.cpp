#include "main.h"
#include "subsystems.hpp"
#include "color_detection.hpp"
#include "controls.h"
// #include "pros/colors.hpp"

#define ALLIANCE_COLOR ColorTarget::BLUE

ColorTarget detect_color (int hue) { //helper function 

    if (hue >= 0 && hue <= 25) {
        return ColorTarget::RED;
    }

    else if (hue >= 150 && hue <= 230) {
        return ColorTarget::BLUE;
    }

    else {
        return ColorTarget::NONE;
    }
}

const char* color_to_string(ColorTarget color) { //changes enum integers to string so Alliance color can be reported
    switch (color) {
        case ColorTarget::RED: return "RED";
        case ColorTarget::BLUE: return "BLUE";
        default: return "NONE"; //default option  

    }
}

ColorTarget getOpponentColor(ColorTarget Alliance) {
    if (Alliance == ColorTarget::RED) {
        return ColorTarget::BLUE;
    }
    else if  (Alliance == ColorTarget::BLUE) {
        return ColorTarget::RED;
    }
        return ColorTarget::NONE; //default

}


void objectDetectionTask() {

    int hue = eye.get_hue();
    int depth = distance_sensor.get();

    ColorTarget detected = detect_color(hue);

    if (detected != ColorTarget::NONE && depth < 105) {  //means there is a color detection 
        
        if (detected == ALLIANCE_COLOR) {
            pros::lcd::print(0, "Alliance Color (%s) detected", color_to_string(ALLIANCE_COLOR));
            pros::lcd::print(1, "%f", distance_sensor.get()); // Records dist value, formatted as a double 
        }   
        else {
            pros::lcd::print(0, "Opponent Color (%s) detected", getOpponentColor(ALLIANCE_COLOR));
            ejector.set_value(1);   //ejector piston w/ fast rapid motion 
            pros::delay(5);
            ejector.set_value(0);

        }
    }    
}
//change