#pragma once

#include "vector.h"
#include "my_string.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct BinaryTreeNode
{
    void *value;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    size_t count;
} BinaryTreeNode;

typedef struct BinarySearchTree
{
    BinaryTreeNode *root;
    size_t elementSize;
    int (*comparator)(const void *a, const void *b);
} BinarySearchTree;

bool binarySearchTreeInitialize(BinarySearchTree *tree, size_t elementSize, int (*comparator)(const void *a, const void *b));
bool binarySearchTreeInsert(BinarySearchTree *tree, const void *item);
void *binarySearchTreeSearch(const BinarySearchTree *tree, const void *item);
void *binarySearchTreeRemove(BinarySearchTree *tree, const void *item);
void binarySearchTreeFree(BinarySearchTree *tree);
void binarySearchTreeApply(BinarySearchTree *tree, void (*function)(void *element, size_t count));
BinarySearchTree *binarySearchTreeMap(BinarySearchTree *tree, void *(*function)(void *element, size_t count), int (*comparator)(const void *a, const void *b));
Vector *binarySearchTreeToVector(BinarySearchTree *tree);
String *binarySearchTreeToString(BinarySearchTree *tree, String (*elementToString)(const void *element));
