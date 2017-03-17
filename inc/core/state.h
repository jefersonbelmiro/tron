#ifndef STATE_H
#define STATE_H

#include <stdlib.h>

// just for avoid circular dependency
typedef struct Game Game;
typedef struct State State;

struct State {
    void (*create)(Game* game);
    void (*destroy)(Game* game, State* state);
    void (*update)(Game* game);
    void (*draw)(Game* game);
};

State* state_create(void* create, void* update, void* draw, void* destroy);
void state_destroy(State* state);

#endif
