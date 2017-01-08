#include "common/array.h"

#define ARRAY_INIT_SIZE 4

void array_resize(void **data, int size, int* data_size)
{
    void **items = realloc(data, sizeof(void*) * size);
    if (!items) {
        printf("eror on realloc array\n");
        exit(1);
    }
    memset(items + *data_size, 0, size - *data_size);
    *data_size = size;
}

void** array_create(int size)
{
    void** data = calloc(size, sizeof(void*));
    return data;
}

void array_push(void** data, void* item, int* data_length, int* data_size)
{
    if (*data_length == *data_size) {
        array_resize(item, (*data_size) + ARRAY_INIT_SIZE, data_size);
    }
    data[(*data_length)++] = item;
}

void array_set(void** data, int index, void* item, int* data_length, int* data_size)
{
    if (index < 0) {
        return;
    }

    if (index >= *data_size) {
        array_resize(data, index + ARRAY_INIT_SIZE, data_size);
    }

    if (index >= *data_length) {
        *data_length = index + 1;
    }

    data[index] = item;
}

bool array_has(void** data, int index, int data_length)
{
    if (index < 0 || index > data_length) {
        return false;
    }
    return data[index] != NULL;
}

void* array_get(void** data, int index, int data_length)
{
    if (index >= 0 && index < data_length) {
        return data[index];
    }
    return NULL;
}

void array_splice(void** data, int index, int size, int* data_length)
{
    if (index < 0 || index >= *data_length) {
        return;
    }

    int i, length = *data_length;

    for (i = index; i < *data_length; i++) {
        if (i + size < *data_length) {
            data[i] = data[i + size];
            continue;
        }
        length--;
        data[i] = NULL;
    }

    *data_length = length;
}

void array_delete(void** data, int index, int* data_length)
{
    if (index < 0 || index >= *data_length) {
        return;
    }
    data[index] = NULL;
    (*data_length)--;
}

void array_destroy(void** data)
{
    free(data);
    data = NULL;
}
