#include "core/state.h"

State* state_create(void* create, void* update, void* draw, void* destroy)
{
    State* state = malloc(sizeof(State));
    state->create = create;
    state->update = update;
    state->draw = draw;
    state->destroy = destroy;
    return state;
}

void state_destroy(State* state)
{
    free(state);
}
