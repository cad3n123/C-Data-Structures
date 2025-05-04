// Copyright 2025 Caden Crowson

#include "../include/vector.h"

#include <stdlib.h>
#include <string.h>

bool vectorInitialize(Vector *vector, size_t elementSize) {
    if (vector == NULL) return false;

    vector->capacity = 10;
    vector->start = malloc(vector->capacity * elementSize);
    if (vector->start == NULL) return false;

    vector->length = 0;
    vector->elementSize = elementSize;

    return true;
}

bool vectorPush(Vector *vector, const void *item) {
    if (vector->length == SIZE_MAX || vector->start == NULL ||
        (vector->length >= vector->capacity &&
         !vectorSetCapacity(vector, 2 * vector->capacity)))
        return false;

    char *dest = (char *)vector->start + vector->length++ * vector->elementSize;
    memcpy(dest, item, vector->elementSize);

    return true;
}

bool vectorPushMany(Vector *vector, const void *items, size_t amount) {
    if (SIZE_MAX - vector->length < amount) return false;
    size_t minimumCapacity = vector->length + amount;
    size_t newCapacity = vector->capacity;
    while (newCapacity < minimumCapacity) {
        if (newCapacity > SIZE_MAX / 2)
            newCapacity = minimumCapacity;
        else
            newCapacity *= 2;
    }
    if (vector->start == NULL ||
        (vector->capacity < minimumCapacity &&
         !vectorSetCapacity(vector, newCapacity)) ||
        items == NULL)
        return false;
    char *dest = (char *)vector->start + vector->length * vector->elementSize;
    memcpy(dest, items, amount * vector->elementSize);
    vector->length += amount;

    return true;
}

bool vectorSetCapacity(Vector *vector, size_t newCapacity) {
    if (vector->capacity >= newCapacity) return true;
    void *newStart = realloc(vector->start, newCapacity * vector->elementSize);
    if (newStart == NULL) return false;

    vector->start = newStart;
    vector->capacity = newCapacity;

    return true;
}

void *vectorPop(Vector *vector, void *out) {
    if (vector->length == 0 || vector->start == NULL) return NULL;
    void *source =
        (char *)vector->start + --vector->length * vector->elementSize;
    if (out != NULL) memcpy(out, source, vector->elementSize);
    return out;
}

void vectorFree(Vector *vector) {
    if (vector == NULL) return;

    vector->length = 0;
    vector->capacity = 0;
    vector->elementSize = 0;
    if (vector->start != NULL) {
        free(vector->start);
        vector->start = NULL;
    }
}

bool vectorAppend(Vector *destination, Vector *source) {
    if (destination == NULL || source == NULL || destination->start == NULL ||
        source->start == NULL ||
        destination->elementSize != source->elementSize ||
        destination->start == source->start)
        return false;

    if (SIZE_MAX - destination->length < source->length) return false;
    size_t newCapacity = destination->length + source->length;
    if (!vectorSetCapacity(destination, newCapacity)) return false;
    memcpy((char *)destination->start +
               destination->length * destination->elementSize,
           source->start, source->length * source->elementSize);
    destination->length += source->length;

    return true;
}

size_t vectorByteSize(Vector *vector) {
    return vector->length * vector->elementSize;
}
