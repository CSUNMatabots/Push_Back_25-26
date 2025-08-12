#pragma once

#include "api.h"
#include "pros/motors.hpp"
#include "lemlib/api.hpp"
#include "pros/rotation.hpp"

extern pros::Controller master;
extern lemlib::Chassis chassis;

inline pros::Motor bottom_intake(15);
inline pros::Motor middle_intake(14);
inline pros::Motor top_intake(-13);
inline pros::MotorGroup intake_rollers({19, -5});
//inline pros::Motor changer(12);

inline pros::MotorGroup flywheel({-12, 17});

inline pros::Motor matchload(18);


//inline pros::ADIPotentiometer pot ('H', pros::E_ADI_POT_EDR);

//inline pros::adi::AnalogIn pot ('H');

inline pros::ADIPotentiometer potensh('H');
inline pros::ADIDigitalOut piston ('A');
