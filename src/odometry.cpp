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

float currentPosX = 0, currentPosY = 0, currentPosTheta = 0;
//x = current position
float targetX = 0, targetY = 0, targetTheta = 0;
//target position
float distanceToTargetX = 0, distanceToTargetY = 0, distanceToTargetTheta = 0;
//distance to target position

//target postion - current position = distance to target position

/*
x = 0, 5, 20
targetX = 10, 20, 10

10 - 0 = 10

20 - 5 = 15

10 - 20 = -10
*/



//functions 
void Odom::setPosition(double currentPosX, double currentPosY, double currentPosTheta) 
{
    currentPosX = 0;
    currentPosY = 0;
    currentPosTheta = 0;
}

void setTargetPosition(double x, double y, double theta)
 {
    targetX = x;
    targetY = y;
    targetTheta = theta;
}

void calculateDistanceToTarget()
 {
    distanceToTargetX = targetX - currentPosX;
    distanceToTargetY = targetY - currentPosY;
    distanceToTargetTheta = targetTheta - currentPosTheta;
}

void driveTo()
{
    /*
    while(currentPosX != targetX && currentPosY != targetY) //add theta later  
    {
        I think theta should come first be evaluated first, then x and y
        
        might be more efficient to seperate into 2 while loops, one for x and one for y
        

        calculateDistanceToTarget(); //updates distance to target values
        lower power of motors as you get closer to target position //most likey a function using PID
        
        if (currentPosX < targetX) 
        {
            //set power to the motors to drive foward
        } 
        else if (currentPosX > targetX)
        {
            //set power to the motors to drive backward
        } 
        else
        {
            if (currentPosY < targetY) 
            {
                //set power to the motors to strafe right
            } 
            else if (currentPosY > targetY)
            {
                //set power to the motors to strafe left
            }
        }
        
       
       
    }
    
    */
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