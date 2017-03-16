#include "state/play.h"
#include "core/window.h"
#include "core/board.h"
#include <curses.h>
#include "core/game.h"

static void preload(Game* game);
static void update(Game* game);
static void draw(Game* game);

State* play_create()
{
    State* play = malloc(sizeof(State));
    play->preload = preload;
    play->update = update;
    play->draw = draw;
    return play;
}

void play_destroy(State* play)
{
    free(play);
}

static void preload(Game* game)
{
}

static void update(Game* game)
{
    if (game->input->key == KEY_ENTER || game->input->key == 10) {
        // restart 
    }
}

static void draw(Game* game)
{
    board_draw(game->board);

    static int count = 0;
    count++;
    char buf[100];
    sprintf(buf, "play.c: %d | [%dx%d]", count, game->board->width, game->board->height);
    window_draw_string(1, game->board->height-1, buf);
}
