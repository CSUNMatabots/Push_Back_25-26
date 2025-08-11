#include "main.h"
#include "subsystems.hpp"
#include "flywheel.hpp"

int flywheel_counter = 0;
bool toggle = false;

void flywheel_speed(int speed){
    flywheel.move(speed);
}

void flywheel_reset(){
    flywheel.tare_position_all();
}

void flywheel_control(){
    if (master.get_digital_new_press(DIGITAL_Y)){
        toggle = !toggle;
    }
    if(toggle){
        flywheel.move(127);
    }else{
        flywheel.move(0);
    }
}