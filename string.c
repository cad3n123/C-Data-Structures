#include "string.h"
#include "vector.h"
#include <string.h>

bool stringInitialize(String *string)
{
    return vectorInitialize(string, sizeof(char));
}

String stringFromCString(const char *chars)
{
    String result;
    stringInitialize(&result);
    stringPushMany(&result, chars);
    return result;
}

bool stringPush(String *string, char c)
{
    if (string->length > 0)
        string->length--;
    if (!vectorPush(string, &c))
        return false;
    char nullChar = '\0';
    return vectorPush(string, &nullChar);
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

String vectorToString(Vector *vector, String (*elementToString)(const void *element))
{
    String result = stringFromCString("[ ");

    size_t byteSize = vectorByteSize(vector);
    for (size_t i = 0; i < byteSize; i += vector->elementSize)
    {
        String elementAsString = elementToString((char *)vector->start + i);
        stringPushMany(&result, elementAsString.start);
        stringFree(&elementAsString);
        if (i + vector->elementSize != byteSize)
        {
            stringPushMany(&result, ", ");
        }
    }
    stringPushMany(&result, " ]");

    return result;
}

String stringToString(String *string)
{
    String result;
    stringInitialize(&result);
    stringPush(&result, '\"');
    stringPushMany(&result, string->start);
    stringPush(&result, '\"');
    return result;
}
