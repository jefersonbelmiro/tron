#include "state/menu.h"
#include "state/play.h"
#include "core/window.h"
#include "core/board.h"
#include "core/game.h"
#include <curses.h>

static void update(Game* game);
static void draw(Game* game);
static void draw_menu(Game* game);

State* menu_create()
{
    State* menu = malloc(sizeof(State));
    menu->update = update;
    menu->draw = draw;
    return menu;
}

void menu_destroy(State* menu)
{
    free(menu);
}

static void update(Game* game)
{
    if (game->input->key == KEY_ENTER || game->input->key == 10) {

        menu_destroy(game->state);
        game->state = play_create();
    }
}

static void draw(Game* game)
{
    board_draw(game->board);
    draw_menu(game);
}

static void draw_menu(Game* game)
{
    int center_x = game->board->width/2;

    window_draw_string(center_x - 14, 1, " _____   ___    ___    _  _ ");
    window_draw_string(center_x - 14, 2, "|_   _| | _ \\  / _ \\  | \\| |");
    window_draw_string(center_x - 14, 3, "  | |   |   / | (_) | | .` |");
    window_draw_string(center_x - 14, 4, "  |_|   |_|_\\  \\___/  |_|\\_|");
    window_draw_string(center_x - 14, 6, "PRESS 'ENTER' TO START/RESTART"); 
    window_draw_string(center_x - 2, 8, "OR"); 
    window_draw_string(center_x - 7, 10, "'Q' TO QUIT"); 
}
