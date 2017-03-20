#include "core/light_cycle.h"

LightCycle* light_cycle_create(int position, int color, int direction, void* update)
{
    LightCycle* light_cycle = malloc(sizeof(LightCycle));
    light_cycle->position = position;
    light_cycle->color = color;
    light_cycle->direction = direction;
    light_cycle->alive = true;
    light_cycle->update = update;
    return light_cycle;
}

void light_cycle_destroy(LightCycle* light_cycle)
{
    free(light_cycle);
}
