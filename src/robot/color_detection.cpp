#include "main.h"
#include "subsystems.hpp"
#include "pros/optical.h"
#include "color_detection.hpp"
#include "pros/colors.hpp"

ColorTarget Red = ColorTarget::RED;
ColorTarget Blue = ColorTarget::BLUE;

bool isRed(int hue) {
    return hue >= 0 && hue <= 25; //sends true/false back to code based on hue range 
}
bool isBlue(int hue) {
    return hue >= 150 && hue <= 230; 
}

int hue = eye.get_hue();


void objectDetectionTask(void* param) {

if (eye.get_proximity() > 150) { //if block are within a certain prox

    if (isBlue(hue)) {  //discard the blue blocks 
    pros::lcd::print(0, "Blue Block Detected");
    
    }
    else if (isRed(hue)) {  //Keep the red blocks 
    pros::lcd::print(0, "Red Block Detected");
    
    }
    else { //do noting or keep running intake 

    }


}





}