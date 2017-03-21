#include "main.h"

int main(int argc, char* argv[])
{
    int width = 40;
    int height = 20;

    Board* board = board_create(width, height);
    Window* window = window_create(width, height);
    Input* input = input_create();
    Game* game = game_create(window, board, input);
    State* menu = menu_create();
    game_set_state(game, menu);
    game_start(game);

    return 0;
}
