#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "core/window.h"
#include "core/board.h"
#include "core/input.h"
#include "state/menu.h"

#define SECOND 1000000
#define FPS SECOND / 10

// just for avoid circular dependency
typedef struct Game Game;

struct Game {
    Window* window;
    Board* board;
    Input* input;
    State* state;
};

Game* game_create(Window* window, Board* board, Input* input, State* state);
void game_destroy(Game* game);
void game_start(Game* game);
void game_tick(Game* game);
void game_set_state(Game* game, State* state);

#endif
