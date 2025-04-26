#pragma once

#include "vector.h"

typedef Vector String;

bool stringInitialize(String *string);
bool stringPush(String *string, char c);
bool stringPushMany(String *string, const char *chars);
char stringPop(String *string);
void stringFree(String *string);
bool stringAppend(String *destination, String *source);
