# pragma once

class Odom {
public:
    void initialize(double x_0, double y_0, double theta_0);

    //Turns to specified heading 
    void pointTurn (double theta);

    //Drives to specified position
    void driveTo(double x, double y);

};
