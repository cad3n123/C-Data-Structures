#include "vector.h"
#include "string.h"
#include "linked_list.h"
#include "binary_search_tree.h"
#include <stdio.h>

typedef struct Package
{
    String message;
} Package;

int main()
{
    LinkedList packages;
    linkedListInitialize(&packages, sizeof(Package));
    linkedListPushBack(&packages, &(Package){stringFromCString("Hello from person 1")});
    linkedListPushBack(&packages, &(Package){stringFromCString("Hello from person 2")});
    linkedListPushBack(&packages, &(Package){stringFromCString("Hello from person 3")});

    Package package;
    while (linkedListPopFront(&packages, &package))
    {
        printf("%s\n", package.message.start);
    }

    return 0;
}