#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void** array_create(int size);
void array_destroy(void** data);
void array_resize(void **data, int size, int* data_size);
void array_push(void** data, void* item, int* data_length, int* data_size);
void array_set(void** data, int index, void* item, int* data_length, int* data_size);
void* array_get(void** data, int index, int data_length);
void array_delete(void** data, int index, int* data_length);
void array_splice(void** data, int index, int size, int* data_length);
bool array_has(void** data, int index, int data_length);

#endif
