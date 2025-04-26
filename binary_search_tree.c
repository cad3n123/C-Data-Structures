#include "binary_search_tree.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static bool binaryTreeNodeInitialize(BinaryTreeNode *node, const void *value, size_t count, size_t elementSize)
{
    if (node == NULL)
        return false;

    void *ownedValue = malloc(elementSize);
    if (ownedValue == NULL)
        return false;
    memcpy(ownedValue, value, elementSize);

    node->left = node->right = NULL;
    node->count = count;
    node->value = ownedValue;

    return true;
}

static BinaryTreeNode **chooseNode(BinaryTreeNode **node, const void *item, int comparisonResult)
{
    switch (comparisonResult)
    {
    case 1: // Greater
        return &(*node)->right;
    case 0: // Equal
        return node;
    case -1: // Less Than
        return &(*node)->left;
    default:
        return NULL;
    }
}

static BinaryTreeNode **binaryTreeNodeSearch(const BinarySearchTree *tree, const void *item)
{
    if (tree == NULL || tree->root == NULL || item == NULL)
        return NULL;

    BinaryTreeNode **result = &tree->root;
    while (!(result == NULL || *result == NULL))
    {
        int comparisonResult = tree->comparator(item, (*result)->value);
        if (comparisonResult == 0)
            return result;

        result = chooseNode(result, item, comparisonResult);
    }
    return NULL;
}

static void binaryTreeNodeFreeRecursive(BinaryTreeNode *node)
{
    if (node == NULL)
        return;
    binaryTreeNodeFreeRecursive(node->left);
    binaryTreeNodeFreeRecursive(node->right);
    free(node->value);
    free(node);
}

static void binaryTreeNodeApplyRecursive(BinaryTreeNode *node, void (*function)(void *element, size_t count))
{
    if (node == NULL || function == NULL)
        return;
    binaryTreeNodeApplyRecursive(node->left, function);
    function(node->value, node->count);
    binaryTreeNodeApplyRecursive(node->right, function);
}

static BinaryTreeNode *binaryTreeNodeMapRecursive(BinaryTreeNode *node, void *(*function)(void *element, size_t count), size_t elementSize)
{
    if (node == NULL || function == NULL)
        return NULL;

    BinaryTreeNode *result = malloc(sizeof *result);
    if (result == NULL)
        return NULL;
    binaryTreeNodeInitialize(result, function(node->value, node->count), node->count, elementSize);
    if (node->left == NULL)
        result->left = NULL;
    else
    {
        result->left = binaryTreeNodeMapRecursive(node->left, function, elementSize);
        if (result->left == NULL)
            return NULL;
    }
    if (node->right == NULL)
        result->right = NULL;
    else
    {
        result->right = binaryTreeNodeMapRecursive(node->right, function, elementSize);
        if (result->right == NULL)
            return NULL;
    }

    return result;
}

static Vector *binaryTreeNodeToVectorRecursive(BinaryTreeNode *node, size_t elementSize)
{
    Vector *vector = malloc(sizeof *vector);
    if (vector == NULL)
        return NULL;

    vectorInitialize(vector, elementSize);
    if (node->left != NULL)
    {
        Vector *left = binaryTreeNodeToVectorRecursive(node->left, elementSize);
        if (left == NULL)
        {
            free(vector);
            return NULL;
        }
        vectorPushMany(vector, left->start, left->length);
        vectorFree(left);
        free(left);
    }
    for (size_t i = 0; i < node->count; i++)
    {
        vectorPush(vector, node->value);
    }
    if (node->right != NULL)
    {
        Vector *right = binaryTreeNodeToVectorRecursive(node->right, elementSize);
        if (right == NULL)
        {
            vectorFree(vector);
            free(vector);
            return NULL;
        }
        vectorPushMany(vector, right->start, right->length);
        vectorFree(right);
        free(right);
    }
    return vector;
}

bool binarySearchTreeInitialize(BinarySearchTree *tree, size_t elementSize, int (*comparator)(const void *a, const void *b))
{
    if (tree == NULL)
        return false;

    tree->elementSize = elementSize;
    tree->comparator = comparator;
    tree->root = NULL;

    return true;
}

bool binarySearchTreeInsert(BinarySearchTree *tree, const void *item)
{
    if (tree == NULL || item == NULL || tree->comparator == NULL)
        return false;
    if (tree->root == NULL)
    {
        tree->root = malloc(sizeof *tree->root);
        if (tree->root == NULL)
            return false;
        if (!binaryTreeNodeInitialize(tree->root, item, 1, tree->elementSize))
        {
            free(tree->root);
            return false;
        }

        return true;
    }
    BinaryTreeNode *node = tree->root;
    while (true)
    {
        int comparisonResult = tree->comparator(item, node->value);
        BinaryTreeNode **childNodePtr = chooseNode(&node, item, comparisonResult);
        if (childNodePtr == NULL)
            return false;
        BinaryTreeNode *childNode = *childNodePtr;
        if (childNode == node)
        {
            node->count++;
            break;
        }
        if (childNode == NULL)
        {
            *childNodePtr = malloc(sizeof **childNodePtr);
            BinaryTreeNode *newChild = *childNodePtr;

            if (newChild == NULL)
                return false;

            if (!binaryTreeNodeInitialize(newChild, item, 1, tree->elementSize))
            {
                free(newChild);
                return false;
            }
            break;
        }
        node = childNode;
    };
    return true;
}

void *binarySearchTreeSearch(const BinarySearchTree *tree, const void *item)
{
    BinaryTreeNode **result = binaryTreeNodeSearch(tree, item);
    if (result == NULL || *result == NULL)
        return NULL;
    return (*result)->value;
}

void *binarySearchTreeRemove(BinarySearchTree *tree, const void *item)
{
    if (tree == NULL || tree->root == NULL || item == NULL)
        return NULL;

    BinaryTreeNode **nodeToRemove = binaryTreeNodeSearch(tree, item);
    if (nodeToRemove == NULL || *nodeToRemove == NULL)
        return NULL;
    if ((*nodeToRemove)->count > 1)
    {
        (*nodeToRemove)->count--;
        return (*nodeToRemove)->value;
    }
    BinaryTreeNode *resultNode = *nodeToRemove;
    if ((*nodeToRemove)->right == NULL)
    {
        *nodeToRemove = resultNode->left;
        void *result = resultNode->value;
        free(resultNode);
        return result;
    }

    BinaryTreeNode **nextBiggest = &(*nodeToRemove)->right;
    while ((*nextBiggest)->left != NULL)
        nextBiggest = &(*nextBiggest)->left;

    BinaryTreeNode *nextBiggestNode = *nextBiggest;

    void *result = resultNode->value;
    resultNode->value = nextBiggestNode->value;
    resultNode->count = nextBiggestNode->count;
    *nextBiggest = nextBiggestNode->right;
    free(nextBiggestNode);
    return result;
}

void binarySearchTreeFree(BinarySearchTree *tree)
{
    if (tree == NULL)
        return;
    binaryTreeNodeFreeRecursive(tree->root);
    tree->elementSize = 0;
    tree->comparator = NULL;
    tree->root = NULL;
}

void binarySearchTreeApply(BinarySearchTree *tree, void (*function)(void *element, size_t count))
{
    if (tree == NULL || function == NULL)
        return;
    binaryTreeNodeApplyRecursive(tree->root, function);
}

Vector *binarySearchTreeToVector(BinarySearchTree *tree)
{
    return binaryTreeNodeToVectorRecursive(tree->root, tree->elementSize);
}

String *binarySearchTreeToString(BinarySearchTree *tree, String (*elementToString)(const void *element))
{
    Vector *vector = binarySearchTreeToVector(tree);
    if (vector == NULL)
        return NULL;
    String *result = malloc(sizeof *result);
    if (result == NULL)
        return NULL;
    String stackResult = vectorToString(vector, elementToString);
    vectorFree(vector);
    free(vector);
    memcpy(result, &stackResult, sizeof(String));
    return result;
}

BinarySearchTree *binarySearchTreeMap(BinarySearchTree *tree, void *(*function)(void *element, size_t count), int (*comparator)(const void *a, const void *b))
{
    if (tree == NULL || function == NULL)
        return NULL;
    BinarySearchTree *result = malloc(sizeof *result);
    if (result == NULL)
        return NULL;
    binarySearchTreeInitialize(result, tree->elementSize, comparator);
    if (tree->root != NULL)
    {
        result->root = binaryTreeNodeMapRecursive(tree->root, function, result->elementSize);
        if (result->root == NULL)
            return NULL;
    }

    return result;
}
