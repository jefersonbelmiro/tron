#include "core/input.h"
#include <curses.h>

Input* input_create()
{
    Input* input = malloc(sizeof(Input));
    return input;
}

void input_update(Input* input)
{
    input->key = getch();
}

void input_destroy(Input* input)
{
    free(input);
}
