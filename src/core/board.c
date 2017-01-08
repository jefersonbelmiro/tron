#include "core/board.h"

Board* board_create(int width, int height)
{
    Board* board = malloc(sizeof(Board));
    board->width = width;
    board->height = height;
    board->length = width * height;
    board->map = malloc(sizeof(int) * board->length);

    return board;
}

void board_destroy(Board* board)
{
    free(board);
}
