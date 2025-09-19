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
#include <cstdlib>

double TW_Dia = 2; //inches

double x = 0.0, y = 0.0, theta = 0.0;
double prev_y = 0, prev_x = 0, prev_heading_deg = 0;

double TW_offset_y = 0;
double TW_offset_x = -5.15; //correct value 

// Heading fusion weight (0..1). Closer to 1 → trust IMU more.
double wIMU = 0;

float cycle_time = 20; // in millisec


#pragma region Constants

double MoE_Drive = 0.75;

double MoE_Turn = 0.5;

double drive_kP = 3.5;
double drive_kD = 20;

double turn_kP = 3;
double turn_kD = 12;

double kp_heading = 3; //4 but turns out at end
double kd_heading = 10; 

// ========================== Helper Functions ==========================
void clearEncoders() {
  verticalEnc.reset();
  horizontalEnc.reset();
//   imu.reset();
}

//Angle wrapping to find the shortest turn path 
int reduceAngle(int angle_deg) {

    while(angle_deg <= -180 || angle_deg > 180) {

        if (angle_deg < -180) { angle_deg += 360; }
        if (angle_deg > 180) { angle_deg -= 360; } 
    }
 return angle_deg;
}   

/*
If v > 127, return 127 
If v < -127, reutrn -127
else (: v), v remains unchagned 
*/
double clamp127(double v){ 
    return v > 127 ? 127 : (v < -127 ? -127 : v); 
}

void Odom_initialize(double x, double y, double theta) {

    clearEncoders();

    prev_x = (horizontalEnc.get_position() / 36000.0) * M_PI * TW_Dia;
    prev_y = (verticalEnc.get_position() / 36000.0) * M_PI * TW_Dia;
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

#pragma region Update Odometry  


int update_position() {

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
    double dy = dist_y - (prev_y);
        prev_y = dist_y;

    double dx = dist_x - (prev_x);
        prev_x = dist_x;


//Change in pos for theta (deltas), imu and horizontal TW
    double dtheta_wheel_deg = 0.0;
        if (std::fabs(TW_offset_x) > 0) { //make sure that horiz tracking wheel offset not 0
            dtheta_wheel_deg = dx / TW_offset_x * (180.0 / M_PI);   // update horizontal wheel angle change, dtheta = arc length / TW wheel offset (radius)
        }

    double dtheta_imu_deg = (imu_deg - prev_heading_deg);
        prev_heading_deg = (prev_heading_deg + dtheta_imu_deg); //update imu heading by adding prev imu deg to delta to get new value 

//Combine dtheta values from imu and horizontal TW  
    double dTheta_deg = wIMU * dtheta_imu_deg + (1.0 - wIMU) * dtheta_wheel_deg; //sclaes the theta (wheel & imu) contribution
    
    double dTheta_rad = dTheta_deg * (M_PI / 180.0);

/*Subtract out rotational component 
  dxmeas​=dxtrans​+dθ⋅TW_offset_x
*/

// double dx_trans = dx - (dTheta_rad * TW_offset_x); //not reading correctly 
double dy_trans = dy - (-dTheta_rad * TW_offset_y); // dy_trans = dy since TW_offset_y = 0 in this case

double theta_mid_rad = theta + (dTheta_rad/2);

//Rotate to field coordinates not robot coor
// double dx_f = cos(theta_mid_rad) * dx_trans - sin(theta_mid_rad) * dy_trans;
// double dy_f = sin(theta_mid_rad) * dx_trans + cos(theta_mid_rad) * dy_trans;

// double dy_f = cos(theta_mid_rad) * dy_trans; //Projects into field coordinates


//update position
// x  += dx_f;                 // update field X position
y  += dy;                 // update field Y position
theta += dTheta_deg; // update heading (deg)

return 1; 

}

// float getXPos(){ return x; }
float getYPos(){ return y; }
float getTheta(){ return theta; } //in deg 


#pragma region Motion_Control 

void driveTo (double target) {

    float driveError = 127 - (127*(getYPos()/target)); 
    float driveDirec = std::fabs(target) / target; //direction = |target| / target (gives 1 or -1)

    double headingError = kp_heading * getTheta(); //inital 
    // float headingDirec = std::fabs(getTheta()) / getTheta(); 

    float deltadriveError = 0;
    float deltaheadingError = 0;
    float prevDriveError = driveError;
    float prevheadingError = headingError;
    
    while (driveError > MoE_Drive ) {

        update_position(); 

        std::cout << "Y-value: %.2f" << y << std::endl; //should print to pros terminal 

        driveError = 127 - (127*(getYPos()/target)); 
        deltadriveError = driveError - prevDriveError;
        prevDriveError = driveError;

        headingError = reduceAngle(getTheta());
        deltaheadingError = headingError - prevheadingError;
        prevheadingError = headingError;        

        float driveSpeed = (driveError * drive_kP) + (deltadriveError * drive_kD);
        float turnSpeed = (headingError * kp_heading);

        //small speed, no turn (prevent pivot)
        if (std::fabs(driveSpeed) < 20) 
            turnSpeed = 0;

        // correct turning w/ both sides
        // passed as an integer
        float L = clamp127((driveSpeed * driveDirec) - turnSpeed); 
        float R = clamp127((driveSpeed * driveDirec) + turnSpeed);

        setDriveVelocity(std::round(L), std::round(R));
    
    pros::delay(cycle_time);
    
    }
    
stopDrive(); //hard stop

}

/*
Add to drive to...
- correct heading with pid control to make sure it doesnt drift off y-target 
*/


void pointTurn(float (angle_deg)) {

angle_deg = reduceAngle(angle_deg);

double turnError = 127 - 127*((getTheta()/fabs(angle_deg))); //only place you should need to reduceAngle, in deg 

int turnDirec = fabs(angle_deg)/angle_deg;

float deltaTurnError = 0;
float prevTurnError = turnError;

while(turnError > MoE_Turn) {

        update_position(); 

        std::cout << "Theta: %.2f" << theta << std::endl;

        turnError = 127 - 127*((getTheta()/fabs(angle_deg)));

        deltaTurnError = turnError - prevTurnError;
        prevTurnError = turnError;

        float turnSpeed = (turnError * turn_kP) + (deltaTurnError * turn_kD);

        setDriveVelocity(turnDirec * turnSpeed, turnDirec * -turnSpeed); //make one side neg for direc

    pros::delay(cycle_time);

    }

stopDrive();

}



void moveTo (double x_1, double y_1, double theta_1) {

    pointTurn(theta_1);

    pros::delay(200);

    double linear_dist = sqrt(pow(x_1 - x, 2) + pow(y_1 - y, 2));

    driveTo(linear_dist);

    x_1 = x, y_1 = y, theta_1 = theta; //save values as new imput

}

/*
1. pointTurn to target theta value
      exit within certain margin of error and move onto next 
2. Calculate dist between cartesian points
3. assign to driveTo function 
4. Save x, y, theta as new values to be used for next call   

*/

















/** 
*
* Samiul Code 
*
*/ 

// float currentPosX = 0, currentPosY = 0, currentPosTheta = 0;
// //x = current position
// float targetX = 0, targetY = 0, targetTheta = 0;
// //target position
// float distanceToTargetX = 0, distanceToTargetY = 0, distanceToTargetTheta = 0;
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