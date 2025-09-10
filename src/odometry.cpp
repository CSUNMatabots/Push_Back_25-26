/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odometry.cpp                                              */
/*    Author:       CSUN Matabots                                             */                                                   
/*    Description:  Contains odometry algorithms                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "main.h"
// #include "include/chassis.hpp"
#include "subsystems.hpp"
#include "odometry.hpp"
#include "math.h"

double TW_Dia = 2.77; //inches


void Odom::setPosition(double x, double y, double theta) {

}

void clearEncoders() {
  verticalEnc.reset();
  horizontalEnc.reset();
  imu.reset();
}

//Angle wrapping to find the shortest turn path 
int reduceAngle(int angle_deg) {

    while(angle_deg <= -180 && angle_deg > 180) {

        if (angle_deg < -180) { angle_deg += 360; }
        if (angle_deg > 180) { angle_deg -= 360; } 
    }
 return angle_deg;
}   

void setDriveVelocity(float LSpeed, float RSpeed) {



}

int rot_vertical = 0;
int rot_horizontal = 0;


int update_positon() {

clearEncoders();
int heading = imu.get_heading();


    rot_vertical = verticalEnc.get_position();
    rot_horizontal = horizontalEnc.get_position();
        

    float dist_V = rot_vertical * M_PI * TW_Dia;
    float dist_H = rot_vertical * M_PI * TW_Dia;

    int new_heading = imu.get_heading();

int dheading = new_heading - heading;

    if (dheading) {

    int halfAngle = dHeading / 2

}

}

#pragma region Motion_Control 





















/** 
*
* Samiul Code 
*
*/ 

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
