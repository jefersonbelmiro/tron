#ifndef LIGHT_CYCLE_H
#define LIGHT_CYCLE_H

#include "core/game.h"
#include "common/ptr_array.h"
#include <curses.h>

typedef struct LightCycle LightCycle;

enum LightCycleDirection {
    LEFT = 0, 
    UP = 1, 
    RIGHT = 2, 
    DOWN = 3
};

enum LightCycleColor {
    WHITE = COLOR_WHITE,
    BLUE = COLOR_BLUE,
    RED = COLOR_RED,
    GREEN = COLOR_GREEN,
    YELLOW = COLOR_YELLOW
};

struct LightCycle {
    int position;
    int color;
    int direction;
    bool alive;
    void (*update)(Game* game, LightCycle *player, PtrArray* players);
};

LightCycle* light_cycle_create(int position, int color, int direction, void* update);
void light_cycle_destroy(LightCycle* light_cycle);

#endif
