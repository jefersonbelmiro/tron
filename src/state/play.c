#include "state/play.h"
#include "core/window.h"
#include "core/board.h"
#include "core/player.h"
#include "core/game.h"
#include "common/ptr_array.h"
#include <curses.h>

static void create(Game* game);
static void update(Game* game);
static void draw(Game* game);
static void destroy(Game* game, State* play);

PtrArray* players;
                                          
State* play_create()
{
    return state_create(create, update, draw, destroy);
}

static void create(Game* game)
{
    players = ptr_array_create(2);
}

static void destroy(Game* game, State* play)
{
    ptr_array_destroy(players);
    state_destroy(play);
}

static void update(Game* game)
{
    if (game->input->key == KEY_ENTER || game->input->key == 10) {
        // restart 
    }

    // update players
}

static void draw(Game* game)
{
    board_draw(game->board);

    // draw players

    static int count = 0;
    count++;
    char buf[100];
    sprintf(buf, "play.c: %d | [%dx%d]", count, game->board->width, game->board->height);
    window_draw_string(3, 0, buf);

}
