#pragma once

void intake_control();

struct Intake {
//all are public members w/ struct 


// Control functions
    void StopAll();
    void ScoreLow_Hop();
    void ScoreMid_Hop();
    void ScoreTop_Hop();
    void Into_Hopper();

};