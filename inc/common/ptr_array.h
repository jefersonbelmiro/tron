#ifndef PTR_ARRAY_H
#define PTR_ARRAY_H

#include "common/array.h"

typedef struct {
    void **items;
    int size;
    int length;
} PtrArray ;

PtrArray *ptr_array_create(int size);
void ptr_array_destroy(PtrArray *data);
void ptr_array_clean(PtrArray *data);
void ptr_array_push(PtrArray *data, void* item);
bool ptr_array_has(PtrArray *data, int index);
void ptr_array_set(PtrArray *data, int index, void* item);
void* ptr_array_get(PtrArray *data, int index);
void ptr_array_delete(PtrArray *data, int index);
void ptr_array_splice(PtrArray *data, int index, int size);

#endif
