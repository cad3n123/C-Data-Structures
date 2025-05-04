// Copyright 2025 Caden Crowson

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "../include/my_string.h"

// All items pushed into the list are deep-copied.
// The caller retains ownership of the original item passed to PushBack.
// Memory for each node's value is automatically freed on PopFront or Free.

typedef struct LinkedListNode LinkedListNode;

typedef struct LinkedList {
    LinkedListNode *start;
    LinkedListNode *end;
    size_t elementSize;
} LinkedList;

struct LinkedListNode {
    void *value;
    LinkedListNode *next;
};

bool linkedListInitialize(LinkedList *linkedList, size_t elementSize);
bool linkedListPushBack(LinkedList *linkedList, const void *item);
bool linkedListPopFront(LinkedList *linkedList, void *const out);
void linkedListFree(LinkedList *linkedList);
size_t linkedListByteSize(LinkedList *linkedList);
String linkedListToString(LinkedList *linkedList,
                          String (*elementToString)(const void *element));
