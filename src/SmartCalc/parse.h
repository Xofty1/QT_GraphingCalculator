#ifndef PARSE_H
#define PARSE_H
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  char type;     // 'n' для чисел, 'o' для операторов
  double value;  // значение числа (если тип 'n')
  char oper;     // оператор (если тип 'o')
} Token;
Token* parse_expression(const char* expression, int* token_count);
int is_function(const char* str, char* c);
int is_oper(char c);

#endif  // PARSE_H
