#include "core/game.h"

void static tick(Game* game);
void static quit(Game* game);

Game* game_create(Window* window, Board* board, Input* input, State* state) 
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
    board_create_bound(game->board);
    tick(game);
}

void static tick(Game* game)
{
    do {

        input_update(game->input);

        if (game->input->key == 'q' || game->input->key == 'Q') {
            quit(game);
        }

        game->state->update(game);
        game->state->draw(game);

        window_refresh();
        window_clear();

        usleep(FPS);

    } while (true);
}

void static quit(Game* game)
{
    game_destroy(game);
    exit(0);
}
