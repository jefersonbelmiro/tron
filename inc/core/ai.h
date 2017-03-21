#ifndef AI_H
#define AI_H

#include "core/light_cycle.h"

LightCycle* ai_create(int position, int color, int direction);
void ai_destroy(LightCycle* ai);

#endif          
