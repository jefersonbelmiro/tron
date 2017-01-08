#include "core/input.h"

Input* input_create()
{
    Input* input = malloc(sizeof(Input));
    return input;
}

void input_destroy(Input* input)
{
    free(input);
}
