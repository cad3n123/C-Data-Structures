// Copyright 2025 Caden Crowson

#include <stdio.h>

#include "../include/binary_search_tree.h"
#include "../include/linked_list.h"
#include "../include/my_string.h"
#include "../include/vector.h"

typedef struct Package {
    String message;
} Package;

int compareInt(const void *a, const void *b);
String intToString(const void *i);
void doubleInt(void *element, size_t count);

int main() {
    BinarySearchTree bst;
    binarySearchTreeInitialize(&bst, sizeof(int), compareInt);
    int item = 1;
    binarySearchTreeInsert(&bst, &item);
    item = 3;
    binarySearchTreeInsert(&bst, &item);
    item = -1;
    binarySearchTreeInsert(&bst, &item);
    binarySearchTreeApply(&bst, doubleInt);
    binarySearchTreeInsert(&bst, &item);
    binarySearchTreeInsert(&bst, &item);
    binarySearchTreeInsert(&bst, &item);
    binarySearchTreeInsert(&bst, &item);
    binarySearchTreeInsert(&bst, &item);
    binarySearchTreeInsert(&bst, &item);
    binarySearchTreeInsert(&bst, &item);
    printf("%s\n",
           stringToCString(binarySearchTreeToString(&bst, intToString)));

    item = 6;
    binarySearchTreeRemove(&bst, &item);
    printf("%s\n",
           stringToCString(binarySearchTreeToString(&bst, intToString)));

    item = -1;
    binarySearchTreeRemove(&bst, &item);
    binarySearchTreeRemove(&bst, &item);
    printf("%s\n",
           stringToCString(binarySearchTreeToString(&bst, intToString)));

    return 0;
}

int compareInt(const void *a, const void *b) {
    int intA = *(const int *)a;
    int intB = *(const int *)b;
    return (intA > intB) - (intA < intB);
}
String intToString(const void *i) {
    const int *intPtr = (const int *)i;
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", *intPtr);
    return stringFromCString(buffer);
}
void doubleInt(void *element, size_t count) {
    int *intPtr = (int *)element;
    (*intPtr) *= 2;
}
