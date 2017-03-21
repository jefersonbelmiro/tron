#include "state/play.h"
#include "core/window.h"
#include "core/board.h"
#include "core/player.h"
#include "core/ai.h"
#include "core/game.h"
#include "common/ptr_array.h"
#include <curses.h>

static void create(Game* game);
static void update(Game* game);
static void draw(Game* game);
static void destroy(Game* game, State* play);
static void draw_game_over(Game* game);
static void restart(Game* game);

static PtrArray* players;
static int survivors = 0;
static bool game_over = false;
                                          
State* play_create()
{
    return state_create(create, update, draw, destroy);
}

static void create(Game* game)
{
    window_clear();

    players = ptr_array_create(2);

    int player_pos = 1 * game->board->width;
    LightCycle* player = player_create(player_pos, BLUE, RIGHT);

    int ai_pos = (game->board->width - 2) + (game->board->height - 2) * game->board->width;
    LightCycle* ai = ai_create(ai_pos, RED, LEFT);

    ptr_array_push(players, player);
    ptr_array_push(players, ai);
}

static void destroy(Game* game, State* play)
{
    ptr_array_destroy(players);
    state_destroy(play);
}

static void update(Game* game)
{
    if (game_over) {

        //restart
        if (game->input->key == KEY_ENTER || game->input->key == 10) {
            restart(game);
        }

        return;
    }

    LightCycle* player;
    survivors = 0;

    for (int player_index = 0; player_index < players->length; player_index++) {

        player = ptr_array_get(players, player_index);

        if (!player->alive) {

            game->board->map[player->position] = '#' | COLOR_PAIR(WHITE); 
            continue;
        }

        survivors++;

        player->update(game, player, players);
        game->board->map[player->position] = '#' | COLOR_PAIR(player->color); 
    }

    if (survivors <= 1) {
        game_over = true;
    }
}

static void draw(Game* game)
{
    board_draw(game->board);

    if (game_over) {
        draw_game_over(game);
    } 
}

static void draw_game_over(Game* game)
{
    char *text = " YOU LOST ";
    if (((LightCycle *) ptr_array_get(players, 0))->alive) {
        text = " YOU WON ";
    }
    int x = (game->board->width / 2) - strlen(text)/2;
    attron(COLOR_PAIR(COLOR_WHITE));
    window_draw_string(x, 0, text); 
    attroff(COLOR_PAIR(COLOR_WHITE));
}

static void restart(Game* game)
{
    for (int player_index = 0; player_index < players->length; player_index++) {
        LightCycle* player = ptr_array_get(players, player_index);
        light_cycle_destroy(player);
    }

    board_clear(game->board);
    board_create_bound(game->board);

    game_over = false;
    create(game);
}
