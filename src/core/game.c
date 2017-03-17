#include "core/game.h"

static void tick(Game* game);
static void quit(Game* game);               
static void process_next_state(Game* game);

Game* game_create(Window* window, Board* board, Input* input, State* state) 
{
    Game* game = malloc(sizeof(Game));
    game->window = window;
    game->board = board;
    game->input = input;
    game->state = state;
    game->next_state = NULL;
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
    game->next_state = state;
}

void game_start(Game* game)
{
    board_create_bound(game->board);
    tick(game);
}

void static tick(Game* game)
{
    do {

        if (game->next_state) {
            process_next_state(game);
        }

        input_update(game->input);

        if (game->input->key == 'q' || game->input->key == 'Q') {
            quit(game);
        }

        if (game->state->update) {
            game->state->update(game);
        }

        if (game->state->draw) {
            game->state->draw(game);
        }

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

void static process_next_state(Game* game)
{
    if (game->state->destroy) {
        game->state->destroy(game, game->state);
    }

    game->state = game->next_state;
    game->next_state = NULL;

    if (game->state->create) {
        game->state->create(game);
    } 
}
