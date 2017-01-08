#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>

typedef struct {
    int key;
} Input; 

Input* input_create();
void input_destroy(Input* input);

#endif
