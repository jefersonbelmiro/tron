#include "core/player.h"

static void update(Game* game, LightCycle *player);
static int* get_allowed_directions(LightCycle *player);
static void input_player_direction(LightCycle *player, int keypress);

LightCycle* player_create(int position, int color, int direction)
{
    return light_cycle_create(position, color, direction, update);
}

void player_destroy(LightCycle* player)
{
    return light_cycle_destroy(player);
} 

static void update(Game* game, LightCycle* player)
{
    input_player_direction(player, game->input->key);

    int map_moves[4] = {-1, -game->board->width, 1, game->board->width};
    player->position += map_moves[player->direction]; 
}

static void input_player_direction(LightCycle *player, int keypress)
{
    int *directions = get_allowed_directions(player);
    int direction = player->direction;
    if (keypress == KEY_LEFT) direction = LEFT;
    if (keypress == KEY_RIGHT) direction = RIGHT;
    if (keypress == KEY_UP) direction = UP;
    if (keypress == KEY_DOWN) direction = DOWN;
    if (direction == directions[0] || direction == directions[1])  player->direction = direction;
}

static int *get_allowed_directions(LightCycle *player)
{
    int *directions = malloc(sizeof(int) * 2);
    switch(player->direction) {
        case UP:
        case DOWN:
            directions[0] = RIGHT;
            directions[1] = LEFT;
        break;
        case LEFT:
        case RIGHT:
            directions[0] = DOWN;
            directions[1] = UP;
        break;
    }
    return directions; 
}

