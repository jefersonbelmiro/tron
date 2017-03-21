#include "core/ai.h"
#include "core/negamax.h"

static void update(Game* game, LightCycle *ai, PtrArray* players);

LightCycle* ai_create(int position, int color, int direction)
{
    return light_cycle_create(position, color, direction, update);
}

void ai_destroy(LightCycle* ai)
{
    return light_cycle_destroy(ai); 
}

static void update(Game* game, LightCycle *ai, PtrArray* players)
{
    int best_move = negamax(
        game->board->map, 
        game->board->width, 
        game->board->height, 
        ai->position, 
        ((LightCycle *) ptr_array_get(players, 0))->position, 
        ai->direction
    );

    int map_moves[4] = {-1, -game->board->width, 1, game->board->width};
    ai->direction = best_move;
    ai->position += map_moves[ai->direction]; 

    if (game->board->map[ai->position]) {
        ai->alive = false;
    }
}
