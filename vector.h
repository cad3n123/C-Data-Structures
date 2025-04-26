#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct Vector
{
    void *start;
    size_t capacity;
    size_t length;
    size_t elementSize;
} Vector;

bool vectorInitialize(Vector *vector, size_t elementSize);
bool vectorPush(Vector *vector, void *item);
bool vectorPushMany(Vector *vector, const void *items, size_t amount);
bool vectorSetCapacity(Vector *vector, size_t newCapacity);
void *vectorPop(Vector *vector, void *out);
void vectorFree(Vector *vector);
bool vectorAppend(Vector *destination, Vector *source);
