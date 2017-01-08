#ifndef STATE_H
#define STATE_H

#include <stdlib.h>

typedef struct Game Game;

typedef struct {
    void (*update)(Game* game);
    void (*draw)(Game* game);
} State; 

#endif
