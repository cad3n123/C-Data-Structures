#include "string.h"
#include "vector.h"
#include <string.h>

bool stringInitialize(String *string)
{
    return vectorInitialize(string, sizeof(char));
}

bool stringPush(String *string, char c)
{
    return vectorPush(string, &c);
}

bool stringPushMany(String *string, const char *chars)
{
    if (string->length != 0)
        (void)stringPop(string);
    return vectorPushMany(string, chars, strlen(chars) + 1);
}

char stringPop(String *string)
{
    char out;
    vectorPop(string, (void *)&out);
    return out;
}

void stringFree(String *string)
{
    vectorFree(string);
}

bool stringAppend(String *destination, String *source)
{
    return vectorAppend(destination, source);
}
