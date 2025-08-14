#pragma once

#include "api.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "lemlib/api.hpp"


extern pros::Controller master;
extern lemlib::Chassis chassis;

inline pros::Motor bottom_intake(15);
inline pros::Motor middle_intake(17);
inline pros::Motor top_intake(-13);
inline pros::MotorGroup intake_rollers({19, -5});
//inline pros::Motor changer(12);

inline pros::MotorGroup flywheel({-12,10});

inline pros::Motor matchload(14);

inline pros::adi::Pneumatics piston('H', false);




