#include "common/int_array.h"

static void int_array_init(IntArray *data, int size)
{
    data->size = size;
    data->length = 0;
    data->items = array_create(size);
}

static void* int_to_ptr(int item)
{
    return (void*) (long int) item;
}

static int ptr_to_int(void* item)
{
    return (int) (long int) item;
}

IntArray *int_array_create(int size)
{
    IntArray* data = malloc(sizeof(IntArray));
    int_array_init(data, size);
    return data;
}

void int_array_destroy(IntArray *data)
{
    array_destroy(data->items);
}

void int_array_clean(IntArray *data)
{
    int_array_destroy(data);
    int_array_init(data, data->size);
}

void int_array_push(IntArray *data, int item)
{
    array_push(data->items, int_to_ptr(item), &data->length, &data->size);
}

bool int_array_has(IntArray *data, int index)
{
    return array_has(data->items, index, data->length);
}

void int_array_set(IntArray *data, int index, int item)
{
    array_set(data->items, index, int_to_ptr(item), &data->length, &data->size);
}

int int_array_get(IntArray *data, int index)
{
    return ptr_to_int(array_get(data->items, index, data->length));
}

void int_array_delete(IntArray *data, int index)
{
    array_delete(data->items, index, &data->length);
}

void int_array_splice(IntArray *data, int index, int size)
{
    array_splice(data->items, index, size, &data->length);
}
