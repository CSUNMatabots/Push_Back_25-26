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
#include <cmath>

double TW_Dia = 2; //inches

double x = 0.0, y = 0.0, theta = 0.0;
int prev_y = 0, prev_x = 0, prev_heading_deg = 0;

double TW_offset_y = 0;
double TW_offset_x = -5.15; //correct value 

// Heading fusion weight (0..1). Closer to 1 → trust IMU more.
double wIMU = 0.8;

/* --------------------------------
Constants
*/ 
float MoE_Drive = 0.1;

float MoE_Turn = 0.5;

float drive_kP = 10;

float drive_kD = 0;

// ========================== Helper Functions ==========================
void clearEncoders() {
  verticalEnc.reset();
  horizontalEnc.reset();
  imu.reset();
}

//Angle wrapping to find the shortest turn path 
int reduceAngle(int angle_deg) {

    while(angle_deg <= -180 || angle_deg > 180) {

        if (angle_deg < -180) { angle_deg += 360; }
        if (angle_deg > 180) { angle_deg -= 360; } 
    }
 return angle_deg;
}   

void Odom_initialize(double x_0, double y_0, double theta_0) {
     x = x_0; y = y_0; theta = reduceAngle(theta_0);

    clearEncoders();

    prev_y = verticalEnc.get_position() / 36000;   // baseline in revolutions
    prev_x = horizontalEnc.get_position() / 36000;
    prev_heading_deg = imu.get_heading();

}

void setDriveVelocity(double LSpeed, double RSpeed) {
leftMotors.move(LSpeed);
rightMotors.move(RSpeed);

}

void stopDrive() {
leftMotors.move(0);
rightMotors.move(0);
}


// =============================================================
int update_positon() {

//Read encoder values
    double v_enc = verticalEnc.get_position(); 
    double h_enc = horizontalEnc.get_position();
    double imu_deg = imu.get_heading(); 

    double v_rev = v_enc / 36000;
    double h_rev = h_enc / 36000;
        
//Convert rotations to linear distance
    float dist_y = v_rev * M_PI * TW_Dia;
    float dist_x = h_rev * M_PI * TW_Dia;

//Change in pos for x and y (deltas)
    double dy = dist_y - (prev_y * M_PI * TW_Dia);
        dist_y = prev_y;

    double dx = dist_x - (prev_x* M_PI * TW_Dia);
        dist_x = prev_x;


//Change in pos for theta (deltas), imu and horizontal TW
    double dtheta_wheel = 0.0;
        if (std::fabs(TW_offset_x) > 0) { //make sure that horiz tracking wheel offset not 0
            dtheta_wheel = dx / TW_offset_x;   // update horizontal wheel angle change, dtheta = arc length / TW wheel offset (radius)
        }

    double dtheta_imu = reduceAngle(imu_deg - prev_heading_deg);
        prev_heading_deg = reduceAngle(prev_heading_deg + dtheta_imu); //update imu heading by adding prev imu deg to delta to get new value 

//Combine dtheta values from imu and horizontal TW  
    double dTheta = wIMU * dtheta_imu + (1.0 - wIMU) * dtheta_wheel; //sclaes the theta (wheel & imu) contribution
    
/*Subtract out rotational component 
  dxmeas​=dxtrans​+dθ⋅TW_offset_x
*/

double dx_trans = dx - dTheta * TW_offset_x;
double dy_trans = dy - (-dTheta * TW_offset_y); // dy_trans = dy since TW_offset_y = 0 in this case

double theta_mid = reduceAngle(theta + (dTheta/2));

//Rotate to field coordinates not robot coor
double dx_f = cos(theta_mid) * dx_trans - sin(theta_mid) * dy_trans;
double dy_f = sin(theta_mid) * dx_trans + cos(theta_mid) * dy_trans;


//update position
x  += dx_f;                 // update field X position
y  += dy_f;                 // update field Y position
theta  = reduceAngle(theta + dTheta); // update heading (wrap to [-π, π])

return y;
return x;
return theta; 

}

float getXPos(){ return x; }
float getYPos(){ return y; }
float getTheta(){ return theta; }

// #pragma region Motion_Control 


void driveTo (double target)
{
    Odom_initialize(0, 0, 0);

    float driveError = 1 - (getYPos() / target); //error = 1 - (current position / target position)
    float driveDirec = std::fabs(target) / target; //direction = |target| / target (gives 1 or -1)

    float deltaDriveError = 0;
    float prevDriveError = driveError;
    
    while (driveError > MoE_Drive ) {

        update_positon(); 

        driveError = 1 - (getYPos() / target);
        deltaDriveError = driveError - prevDriveError;
        prevDriveError = driveError;

        float driveSpeed = (driveError * drive_kP) + (deltaDriveError * drive_kD);

        setDriveVelocity(driveDirec * driveSpeed, driveDirec * driveSpeed);
    
    pros::delay(5);
    
    }
    
stopDrive();

}


















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
/*void Odom::setPosition(double currentPosX, double currentPosY, double currentPosTheta) 
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
    
    
}
*/// #pragma endregion