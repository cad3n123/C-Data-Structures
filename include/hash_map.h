// Copyright 2025 Caden Crowson

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "../include/hash_map.h"

typedef struct HashMapBucket {
    void *key;
    void *value;
} HashMapBucket;

typedef struct HashMap {
    size_t size;
    size_t keySize;
    size_t valueSize;
    HashMap *buckets;
    int (*keyComparator)(const void *a, const void *b);
} HashMap;

bool hashMapInitialize(HashMap *map, size_t size, size_t keySize,
                       size_t valueSize,
                       int (*keyComparator)(const void *a, const void *b));
bool hashMapInsert(HashMap *map, const void *key, const void *value);
