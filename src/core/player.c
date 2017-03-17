#include "core/player.h"

static void update(Game* game, LightCycle *player);

LightCycle* player_create(int position, int color, int direction)
{
    LightCycle* player = malloc(sizeof(LightCycle));
    player->position = position;
    player->color = color;
    player->direction = direction;
    player->alive = true;
    player->update = update;
    return player;
}

void player_destroy(LightCycle* player)
{
    free(player);
} 

static void update(Game* game, LightCycle* player)
{

}
