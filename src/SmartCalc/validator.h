#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isValidExpression(const char *expression, int is_x);
bool isValidCharacter(char ch);
bool isOpeningBracket(char ch);
bool isClosingBracket(char ch);
bool isOperator(char ch);
bool isFunction(const char *str, int *i);

#endif  // VALIDATOR_H
