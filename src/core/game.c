#include "core/game.h"

void static tick(Game* game);

Game*
game_create(window, board, input, state)
Window* window;
Board* board;
Input* input;
State* state;
{
    Game* game = malloc(sizeof(Game));
    game->window = window;
    game->board = board;
    game->input = input;
    game->state = state;
    return game;
}

void game_destroy(Game* game)
{
    board_destroy(game->board);
    window_destroy(game->window);
    free(game);
}

void game_set_state(Game* game, State* state)
{
    game->state = state;
}

void game_start(Game* game)
{
    tick(game);
}

void static tick(Game* game)
{
    do {
        game->state->update(game);
        game->state->draw(game);
        usleep(FPS);
    } while (true);
}
