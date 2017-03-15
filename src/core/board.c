#include "core/board.h"
#include "core/window.h"

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
    free(board->map);
    free(board);
}

void board_create_bound(Board* board)
{
    enum draw { 
        WALL = '#', 
        EMPTY = ' ',
        BOUND_CORNER = '+',    
        BOUND_LINE_VERTICAL = '|',
        BOUND_LINE_HORIZONTAL = '-'
    };

    for (int y = 0; y < board->height; y++) {
        board->map[y * board->width] = BOUND_LINE_VERTICAL; 
        board->map[board->width - 1 + y * board->width] = BOUND_LINE_VERTICAL; 
    }
    for (int x = 0; x < board->width; x++) {
       board->map[x + 0 * board->width] = BOUND_LINE_HORIZONTAL;
       board->map[x + (board->height - 1) * board->width] = BOUND_LINE_HORIZONTAL;
    }
    board->map[board->width - 1] = BOUND_CORNER;
    board->map[board->length - 1] = BOUND_CORNER;
    board->map[0] = BOUND_CORNER;
    board->map[(board->height-1) * board->width] = BOUND_CORNER;
}

void board_draw(Board* board)
{
    int id, x, y;

    for (id = 0; id < board->length; id++) {

        x = id % board->width;
        y = (int) id/board->width;
        if (board->map[id]) {
            window_draw_char(x, y, board->map[id]);
        }
    }
}
