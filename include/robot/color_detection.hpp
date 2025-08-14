#pragma once

enum class ColorTarget { RED, BLUE };

extern ColorTarget Red;
extern ColorTarget Blue;

void objectDetectionTask(void* param);