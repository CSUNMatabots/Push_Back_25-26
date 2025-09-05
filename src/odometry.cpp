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



void clearEncoders() {
  verticalEnc.reset();
  horizontalEnc.reset();
}

//Angle wrapping to find the shortest turn path 
int reduceAngle(int angle_deg) {

    while(angle_deg <= -180 && angle_deg > 180) {

        if (angle_deg < -180) { angle_deg += 360; }
        if (angle_deg > 180) { angle_deg -= 360; } 

    }

 return angle_deg;

}   




//functions 
void Odom::setPosition(double x, double y, double theta) {


}

void trackingWheelTest() {
    

//linear dist is arc length ( s = r * θ )





}