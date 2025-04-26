#include "vector.h"
#include "string.h"
#include <stdio.h>

int main()
{
    String string;
    stringInitialize(&string);
    stringPushMany(&string, "Hello, World!");

    printf("%s", string.start);

    return 0;
}