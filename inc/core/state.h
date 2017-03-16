#ifndef STATE_H
#define STATE_H

#include <stdlib.h>

// just for avoid circular dependency
typedef struct Game Game;

typedef struct {
    void (*preload)(Game* game);
    void (*update)(Game* game);
    void (*draw)(Game* game);
} State;

#endif
