#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include "common/array.h"

typedef struct {
    void **items;
    int size;
    int length;
} IntArray ;

IntArray *int_array_create(int size);
void int_array_destroy(IntArray *data);
void int_array_clean(IntArray *data);
void int_array_push(IntArray *data, int item);
bool int_array_has(IntArray *data, int index);
void int_array_set(IntArray *data, int index, int item);
int int_array_get(IntArray *data, int index);
void int_array_delete(IntArray *data, int index);
void int_array_splice(IntArray *data, int index, int size);

#endif
