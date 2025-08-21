#pragma once

#include "api.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "lemlib/api.hpp"
#include "pros/optical.hpp"


extern pros::Controller master;
extern lemlib::Chassis chassis;


// Ports up to date 
inline pros::Motor bottom_intake(15);
inline pros::Motor middle_intake(5);
inline pros::Motor top_intake(-13);
inline pros::Motor hopper(10);
inline pros::Motor agitator(19);
inline pros::MotorGroup flywheel({3,4});
inline pros::Motor matchload(14);

//Sensors and Pneumatics
inline pros::adi::Pneumatics piston('H', false);
inline pros::adi::Pneumatics ejector('G', false);
inline pros::Optical eye (12);
inline pros::Distance distance_sensor(7);




