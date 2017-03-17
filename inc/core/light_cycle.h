#ifndef LIGHT_CYCLE_H
#define LIGHT_CYCLE_H

#include "core/game.h"

typedef struct LightCycle LightCycle;

struct LightCycle {
    int position;
    int color;
    int direction;
    bool alive;
    void (*update)(Game* game, LightCycle *player);
};

#endif
