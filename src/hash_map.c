// Copyright 2025 Caden Crowson

#include "../include/hash_map.h"

#include <stddef.h>
#include <stdlib.h>

#include "../include/binary_search_tree.h"

static size_t hash(char *key, size_t size, size_t tableSize) {
    if (key == NULL) return tableSize;
    size_t hashval = 0;
    for (; size > 0; size--) hashval = *key + (hashval << 5) - hashval;
    return hashval % tableSize;
}

static size_t compareHashMapBuckets() {}

bool hashMapInitialize(HashMap *map, size_t size, size_t keySize,
                       size_t valueSize,
                       int (*keyComparator)(const void *a, const void *b)) {
    if (map == NULL ||
        (map->buckets = malloc(size * sizeof(*map->buckets))) == NULL)
        return false;
    for (size_t i = 0; i < size; i++) {
        // binarySearchTreeInitialize(&map->buckets[i], sizeof(HashMapBucket),
        // );
    }
    map->keySize = keySize;
    map->valueSize = valueSize;
    map->keyComparator = keyComparator;
    map->size = size;
}
