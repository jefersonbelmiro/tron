#include "core/player.h"

static void update(Game* game, LightCycle *player, PtrArray* players);
static void input_direction(LightCycle *player, int keypress);

LightCycle* player_create(int position, int color, int direction)
{
    return light_cycle_create(position, color, direction, update);
}

void player_destroy(LightCycle* player)
{
    return light_cycle_destroy(player);
} 

static void update(Game* game, LightCycle* player, PtrArray* players)
{
    input_direction(player, game->input->key);

    int map_moves[4] = {-1, -game->board->width, 1, game->board->width};
    player->position += map_moves[player->direction]; 

    if (game->board->map[player->position]) {
        player->alive = false;
    }
}

static void input_direction(LightCycle *player, int keypress)
{
    switch(player->direction) {
        case UP:
        case DOWN:
            if (keypress == KEY_LEFT) player->direction = LEFT;
            if (keypress == KEY_RIGHT) player->direction = RIGHT;
            break;
        case LEFT:
        case RIGHT:
            if (keypress == KEY_DOWN) player->direction = DOWN;
            if (keypress == KEY_UP) player->direction = UP;
            break;
    }
}

