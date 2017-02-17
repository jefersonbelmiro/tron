#include "core/board.h"

Board* board_create(int width, int height)
{
    Board* board = malloc(sizeof(Board));
    board->width = width;
    board->height = height;
    board->length = width * height;
    board->map = calloc(board->length, sizeof(int));

    return board;
}

void board_destroy(Board* board)
{
    /* free(board->map); */
    free(board);
}
