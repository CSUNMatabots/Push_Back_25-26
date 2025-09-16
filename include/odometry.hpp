# pragma once

float getXPos();
float getYPos();
float getTheta();

void Odom_initialize(double x_0, double y_0, double theta_0);

void pointTurn (double angle_deg); //Turns to specified heading 

void driveTo(double target); //Drives to specified position (only y-pos right now)

void moveTo (double x, double y, double theta);

