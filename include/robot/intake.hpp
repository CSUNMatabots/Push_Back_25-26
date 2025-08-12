#pragma once

// =======Bottom Intake Code========
void b_intake_speed(int speed);

void b_intake_set_pos(double pos, int speed);

void b_intake_delay(int speed, int delay);

void b_intake_reset();

// =======Middle Intake Code========
void m_intake_speed(int speed);

void m_intake_set_pos(double pos, int speed);

void m_intake_delay(int speed, int delay);

void m_intake_reset();

// =======Top Intake Code========
void t_intake_speed(int speed);

void t_intake_set_pos(double pos, int speed);

void t_intake_delay(int speed, int delay);

void t_intake_reset();

// =======Changer Intake Code========
void changer_speed(int speed);

void changer_set_pos(double pos, int speed);

void changer_delay(int speed, int delay);

void changer_reset();

// =======Roller Intake Code========
void roller_speed(int speed);

void roller_set_pos(double pos, int speed);

void roller_delay(int speed, int delay);

void roller_reset();



void intake_control();