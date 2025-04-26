#include "linked_list.h"
#include "string.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool linkedListInitialize(LinkedList *linkedList, size_t elementSize)
{
    if (linkedList == NULL)
        return false;

    memset(linkedList, 0, sizeof *linkedList);
    linkedList->elementSize = elementSize;

    return true;
}

bool linkedListPushBack(LinkedList *linkedList, const void *item)
{
    if (linkedList == NULL || item == NULL)
        return false;

    LinkedListNode *node = malloc(sizeof *node);
    if (node == NULL)
        return false;

    node->value = malloc(linkedList->elementSize);
    if (node->value == NULL)
    {
        free(node);
        return false;
    }

    memcpy(node->value, item, linkedList->elementSize);
    node->next = NULL;

    if (linkedList->end == NULL)
        linkedList->start = node;
    else
        linkedList->end->next = node;
    linkedList->end = node;

    return true;
}

bool linkedListPopFront(LinkedList *linkedList, void *const out)
{
    if (linkedList == NULL || linkedList->start == NULL)
        return false;
    LinkedListNode *start = linkedList->start;

    if (out != NULL)
        memcpy(out, start->value, linkedList->elementSize);
    if (linkedList->start == linkedList->end)
        linkedList->end = NULL;
    linkedList->start = linkedList->start->next;

    free(start->value);
    free(start);
    return true;
}

void linkedListFree(LinkedList *linkedList)
{
    while (linkedListPopFront(linkedList, NULL))
        ;

    linkedList->elementSize = 0;
}

String linkedListToString(LinkedList *linkedList, String (*elementToString)(const void *element))
{
    String result = stringFromCString("[ ");

    LinkedListNode *node = linkedList->start;

    while (node != NULL)
    {
        String elementAsString = elementToString(&node->value);
        stringPushMany(&result, elementAsString.start);
        stringFree(&elementAsString);
        node = node->next;
        if (node != NULL)
            stringPushMany(&result, ", ");
    }

    stringPushMany(&result, " ]");

    return result;
}
