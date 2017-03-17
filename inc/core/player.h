#ifndef PLAYER_H
#define PLAYER_H

#include "core/light_cycle.h"

LightCycle* player_create(int position, int color, int direction);
void player_destroy(LightCycle* player);

#endif
