#include "common/ptr_array.h"

static void ptr_array_init(PtrArray *data, int size)
{
    data->size = size;
    data->length = 0;
    data->items = array_create(size);
}

PtrArray *ptr_array_create(int size)
{
    PtrArray* data = malloc(sizeof(PtrArray));
    ptr_array_init(data, size);
    return data;
}

void ptr_array_destroy(PtrArray *data)
{
    array_destroy(data->items);
}

void ptr_array_clean(PtrArray *data)
{
    ptr_array_destroy(data);
    ptr_array_init(data, data->size);
}

void ptr_array_push(PtrArray *data, void* item)
{
    array_push(data->items, item, &data->length, &data->size);
}

bool ptr_array_has(PtrArray *data, int index)
{
    return array_has(data->items, index, data->length);
}

void ptr_array_set(PtrArray *data, int index, void* item)
{
    array_set(data->items, index, item, &data->length, &data->size);
}

void* ptr_array_get(PtrArray *data, int index)
{
    return array_get(data->items, index, data->length);
}

void ptr_array_delete(PtrArray *data, int index)
{
    array_delete(data->items, index, &data->length);
}

void ptr_array_splice(PtrArray *data, int index, int size)
{
    array_splice(data->items, index, size, &data->length);
}
