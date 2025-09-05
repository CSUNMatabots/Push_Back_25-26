#pragma once

#include "api.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "lemlib/api.hpp"
#include "pros/optical.hpp"
#include "pros/imu.hpp"


extern pros::Controller master;
extern lemlib::Chassis chassis;
extern pros::Imu imu;


// Ports up to date 
inline pros::Motor middle_int(12);
inline pros::Motor top_intake(-11);
inline pros::Motor hopper(13);
inline pros::Motor agitator(14);

//Sensors and Pneumatics
inline pros::adi::Pneumatics piston('H', false);
inline pros::adi::Pneumatics ejector('G', false);
inline pros::Optical eye (12);
// inline pros::Distance distance_sensor(20);

inline pros::Imu imu(3);
inline pros::Rotation horizontalEnc(2);
inline pros::Rotation verticalEnc(-1);


