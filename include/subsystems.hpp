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

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// Ports up to date 
inline pros::MotorGroup middle_int({12,-13});
inline pros::Motor top_intake(-11);
inline pros::Motor hopper(14);
inline pros::Motor agitator(15);

//Sensors and Pneumatics
inline pros::adi::Pneumatics Matchload('H', false);
inline pros::adi::Pneumatics Gate('G', false);
inline pros::Optical eye (5);

//Encoders & IMU 
inline pros::Imu imu(3);
inline pros::Rotation horizontalEnc(2);
inline pros::Rotation verticalEnc(-1);


