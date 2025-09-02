# pragma once

class Odom {
public:
    void setPosition(double x, double y, double theta);

    //Turns to specified heading 
    void pointTurn (double theta);

    //Drives to specified position
    void driveTo(double x, double y);

};
