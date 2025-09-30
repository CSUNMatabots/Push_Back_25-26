#pragma once

void intake_control();


struct IntakeConstants {
    int  m;        // middle intake
    int  t;        // top intake
    int  hop;      // hopper
    int  ag;       // agitator
    bool matchload;
    bool gate;
};

// Bundle of named presets to call on, ie. preset.top_hop
struct IntakePreset {
    IntakeConstants top_hop;
    IntakeConstants mid_hop;
    IntakeConstants low_hop;
    IntakeConstants into_hopper;
    IntakeConstants matchload_score;
    IntakeConstants stop_all; // motors stop; pneumatics unchanged is handled separately
    IntakeConstants stop_motors;
};

extern const IntakePreset preset; //functions, read only (const)
extern IntakeConstants current_preset; //constants

void IntakeRun(const IntakeConstants& run); //reads struct, but doesnt modify (const)