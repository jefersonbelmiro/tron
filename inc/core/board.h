#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>

typedef struct {

    // sizes
    int width, height, length;

    // allow directions to move
    int moves[4];

    // 2d map store in single dimensional array
    int* map;

} Board;

Board* board_create(int width, int height);
void board_destroy(Board* board);

#endif
