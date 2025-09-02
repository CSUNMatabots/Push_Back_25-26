#include "liblvgl/llemu.hpp"
#include "main.h"
#include "subsystems.hpp"
#include "color_detection.hpp"
#include "controls.h"
// #include "pros/colors.hpp"

#define ALLIANCE_COLOR ColorTarget::BLUE

const int MAX_STORAGE = 13;
int storage_count = 0;



ColorTarget detect_color (int hue) { //helper function 

    if (hue >= 0 && hue <= 25) {
        return ColorTarget::RED;
    }

    else if (hue >= 125 && hue <= 230) {
        return ColorTarget::BLUE;
    }

    else {
        return ColorTarget::NONE;
    }
}

void StorageControl(int hue, int MAX_STORAGE)
{
    if(storage_count == MAX_STORAGE)
    {
        pros::lcd::clear_line(2);
        pros::lcd::print(2, "Storage Full");
    } 
    else 
    {

        if (detect_color(hue) != ColorTarget::NONE)
        {
            ++storage_count;
            pros::lcd::clear_line(2);
            pros::lcd::print(2, "Storage Count = ", storage_count);
        }
    }
}

const char* color_to_string(ColorTarget color) { //changes enum integers to string so Alliance color can be reported
    switch (color) {
        case ColorTarget::RED: return "RED";
        break;
        case ColorTarget::BLUE: return "BLUE";
        break;
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
    else {
        return ColorTarget::NONE; //default

    }

}


void objectDetectionTask() 
{

    eye.set_led_pwm(100);
    int hue = eye.get_hue();
    int depth = eye.get_proximity();

    ColorTarget detected = detect_color(hue);
    if (depth < 200) // rel far (higher value = closer) //made detection closer so less false readings(blue being red)
    { 
        
        pros::lcd::print(2, "No Object Nearby");

    } 
    else 
    { 
    
        if (detected != ColorTarget::NONE) //means there is a color detection
        {   
            if (detected == ALLIANCE_COLOR) 
            {
                pros::lcd::clear_line(2);
                pros::lcd::print(2, "Alliance Color (%s) detected", color_to_string(ALLIANCE_COLOR));
                /*
                                this is breaking the program for some reason
                pros::lcd::clear_line(3);   
                pros::lcd::print(3, "%f", eye.get_proximity()); // Records dist value, formatted as a double */

                /*while (1) 
                {   pros::lcd::clear_line(3);
                    pros::lcd::print(3, "%f", eye.get_proximity());
                    pros::delay(20);
                }*/
                
            }
            else
            {  
                pros::lcd::clear_line(2);
                pros::lcd::print(2, "Opponent Color (%s) detected", color_to_string(getOpponentColor(ALLIANCE_COLOR)));//problem here
                
                /*while (1) 
                {   
                    pros::lcd::clear_line(3);
                    pros::lcd::print(3, "%f", eye.get_proximity());
                    pros::delay(20);
                }*/

                // ejector.set_value(1);   //ejector piston w/ fast rapid motion 
                // pros::delay(5);
                // ejector.set_value(0);
            

            }

        }            
    }   

}
   
