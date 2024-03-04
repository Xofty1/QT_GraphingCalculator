#ifndef POL_H
#define POL_H
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#define EPSILON 0.0000000000001
#define OK 0
#define ZERO_DIV 1
#define TRIGONOM_ERROR 2
#define BAD_ARGUMENT 3
#define INF 1.0 / 0.0
typedef struct {
  Token *data;
  int top;
  int size;
} Stack;

void initializeStack(Stack *stack, int size);
int isEmpty(Stack *stack);
void push(Stack *stack, Token element);
Token pop(Stack *stack);
int isOperatorOrBracket(char c);
int precedence(char oper);
Token *toPostfixNotation(Token tokens[], int numTokens, int *n);
double calculate(double operand1, double operand2, char oper, int *error);
double calculate_function(double operand, char oper, int measure, int *error,
                          int is_x);
double calculateExpression(Token *tokens, int numTokens, int measure,
                           int *error, double x);

#endif  // POL_H
