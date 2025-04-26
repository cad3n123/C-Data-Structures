#pragma once

#include "vector.h"

typedef Vector String;

bool stringInitialize(String *string);
String stringFromCString(const char *chars);
bool stringPush(String *string, char c);
bool stringPushMany(String *string, const char *chars);
char stringPop(String *string);
void stringFree(String *string);
bool stringAppend(String *destination, String *source);
String stringToString(String *string);
String vectorToString(Vector *vector, String (*elementToString)(const void *element));
char *stringToCString(String *string);
