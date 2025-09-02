/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odometry.cpp                                              */
/*    Author:       CSUN Matabots                                             */                                                   
/*    Description:  Contains odometry algorithms                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "main.h"
#include "subsystems.hpp"
#include "odometry.hpp"
#include "math.h"

double WHEEL_RADIUS = 2.77; //inches

float x = 0, y = 0, theta = 0;

//functions 
void Odom::setPosition(double x, double y, double theta) {

}

void trackingWheelTest() {
    

//linear dist is arc length ( s = r * θ )

double WHEEL_DIAMETER = 2.77;
double WHEEL_RADIUS = WHEEL_DIAMETER / 2;
double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * M_PI; // pi * d

float rotation = rotsensor.get_position(); //returns postion in degrees

double Total_Dist = WHEEL_RADIUS * rotation * (M_PI / 180); //arc length formula uses radians 

pros::lcd::print(0, "Total Distance: %.3f", Total_Dist);



}