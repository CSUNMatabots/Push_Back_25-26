#include "main.h"
#include "subsystems.hpp"
#include "color_detection.hpp"
// #include "pros/colors.hpp"

ColorTarget Red = ColorTarget::RED;
ColorTarget Blue = ColorTarget::BLUE;

bool isRed(int hue) {
    return hue >= 0 && hue <= 25; //sends true/false back to code based on hue range 
}
bool isBlue(int hue) {
    return hue >= 150 && hue <= 230; 
}

int hue = eye.get_hue();
int depth = distance_sensor.get();

void objectDetectionTask() {

    if (isBlue(hue) && depth < 105) {  //discard the blue blocks 
        pros::lcd::print(0, "Blue Block Detected");
        pros::lcd::print(1, "%f", distance_sensor.get()); // Records dist value, formatted as a double 
        ejector.set_value(1);   //ejector piston w/ fast rapid motion 
        pros::delay(5);
        ejector.set_value(0);
    
    }
    else if (isRed(hue) && depth < 105) {      //Keep the red blocks 
        pros::lcd::print(0, "Red Block Detected");
    
    }
    else { }    //do noting or keep running intake 

}