#include "../pol.h"

#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include <stdio.h>
#include <stdlib.h>

void initializeStack(Stack *stack, int size) {
  stack->data = (Token *)malloc(sizeof(Token) * size);
  stack->top = -1;
  stack->size = size;
}
void freeStack(Stack *stack) { free(stack->data); }

int isEmpty(Stack *stack) { return stack->top == -1; }

void push(Stack *stack, Token element) {
  if (stack->top == stack->size - 1) {
    return;
  }
  stack->data[++stack->top] = element;
}

Token pop(Stack *stack) {
  Token emptyToken;
  emptyToken.type = '\0';

  if (isEmpty(stack)) {
    return emptyToken;
  }
  return stack->data[stack->top--];
}

int isOperationOrBracket(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'm' ||
         c == 's' || c == 'c' || c == 'i' || c == 'o' || c == 't' || c == 'a' ||
         c == 'q' || c == 'l' || c == 'g' || c == '(' || c == ')';
}

int precedence(char oper) {
  if (oper == '+' || oper == '-') {
    return 1;
  } else if (oper == '*' || oper == '/') {
    return 2;
  } else if (oper == 'm') {
    return 3;
  } else if (oper == 'c' || oper == 's' || oper == 'i' || oper == 'o' ||
             oper == 't' || oper == 'a') {
    return 4;
  } else if (oper == 'l' || oper == 'g') {
    return 5;
  } else if (oper == 'q' || oper == '^') {
    return 6;
  } else if (oper == '(') {
    return 0;
  }
  return 0;
}

Token *toPostfixNotation(Token tokens[], int numTokens, int *n) {
  Stack stack;
  initializeStack(&stack, numTokens);
  int i;
  Token *postfix =
      (Token *)malloc(sizeof(Token) * (numTokens * 2));  // Достаточный размер
  int j = 0;
  for (i = 0; i < numTokens; ++i) {
    if (tokens[i].type == 'n' || tokens[i].type == 't') {
      postfix[j++] = tokens[i];
    } else if (tokens[i].type == 'o' || tokens[i].type == 'f') {
      if (tokens[i].oper == '(') {
        push(&stack, tokens[i]);
      } else if (tokens[i].oper == ')') {
        while (!isEmpty(&stack) && stack.data[stack.top].oper != '(') {
          postfix[j++] = pop(&stack);
        }
        if (!isEmpty(&stack) && stack.data[stack.top].oper == '(') {
          pop(&stack);  // Удаляем открывающую скобку из стека
        }
        // else {
        //   exit(EXIT_FAILURE);
        // }
      } else {
        while (!isEmpty(&stack) &&
               isOperationOrBracket(stack.data[stack.top].oper) &&
               (precedence(tokens[i].oper) <=
                precedence(stack.data[stack.top].oper))) {
          Token temp = pop(&stack);
          if (!(temp.oper == '(' || temp.oper == ')')) postfix[j++] = temp;
        }
        push(&stack, tokens[i]);
      }
    }
  }

  while (!isEmpty(&stack)) {
    Token temp = pop(&stack);
    postfix[j++] = temp;
  }
  *n = j;
  freeStack(&stack);
  return postfix;
}

double calculate(double operand1, double operand2, char oper, int *error) {
  switch (oper) {
    case '+':
      return operand1 + operand2;
    case '-':
      return operand1 - operand2;
    case '*':
      return operand1 * operand2;
    case '^':
      return pow(operand1, operand2);
    case 'm':
      if (operand2 != 0.0) {
        return fmod(operand1, operand2);
      } else {
        *error = ZERO_DIV;
        return 0;
      }
    case '/':
      if (operand2 != 0.0) {
        return operand1 / operand2;
      } else {
        *error = ZERO_DIV;
        return 0;
      }

      // default:
      //   exit(EXIT_FAILURE);
  }
  return 0;
}

double calculate_function(double operand, char oper, int measure, int *error,
                          int is_x) {
  double res = 0;
  switch (oper) {
    case 'c':
      if (measure == 0) operand *= M_PI / 180.0;
      res = cos(operand);
      if (res < EPSILON && res > -EPSILON) res = 0;
      break;
    case 's':
      if (measure == 0) operand *= M_PI / 180.0;
      res = sin(operand);
      if (res < EPSILON && res > -EPSILON) res = 0;
      break;
    case 'i':
      if (measure == 0) operand *= M_PI / 180.0;
      if ((operand < -1 || operand > 1) && is_x == 1) {
        if (operand < -1) res = -INF;
        if (operand > 1) res = INF;
      } else if ((operand < -1 || operand > 1) && is_x == 0) {
        *error = TRIGONOM_ERROR;

      } else {
        res = asin(operand);
      }
      break;

    case 'o':

      if (measure == 0) operand *= M_PI / 180.0;
      if ((operand < -1 || operand > 1) && is_x == 1) {
        if (operand < -1) res = -INF;
        if (operand > 1) res = INF;
      } else if ((operand < -1 || operand > 1) && is_x == 0) {
        *error = TRIGONOM_ERROR;
      } else {
        res = acos(operand);
      }
      break;
    case 't':
      if (measure == 0) operand *= M_PI / 180.0;
      if ((cos(operand) < EPSILON && cos(operand) > -EPSILON) && is_x == 1) {
        if (cos(operand) < EPSILON) res = INF;
        if (cos(operand) > -EPSILON) res = -INF;
      } else if ((cos(operand) < EPSILON && cos(operand) > -EPSILON) &&
                 is_x == 0) {
        *error = TRIGONOM_ERROR;
      } else {
        res = tan(operand);
      }
      break;
    case 'a':
      if (measure == 0) operand *= M_PI / 180.0;
      res = atan(operand);
      break;
    case 'q':
      if (operand < 0 && is_x == 1) {
        res = INF;
      } else if (operand < 0 && is_x == 0) {
        *error = BAD_ARGUMENT;
      } else {
        res = sqrt(operand);
      }
      break;

    case 'l':
      if (operand <= 0 && is_x == 1) {
        res = INF;
      } else if (operand <= 0 && is_x == 0) {
        *error = BAD_ARGUMENT;
      } else {
        res = log(operand);
      }
      break;

    case 'g':
      if (operand <= 0 && is_x == 1) {
        res = INF;
      } else if (operand <= 0 && is_x == 0) {
        *error = BAD_ARGUMENT;

      } else {
        res = log10(operand);
      }
      break;
      // default:
      //   exit(EXIT_FAILURE);
  }
  return res;
}

double calculateExpression(Token *tokens, int numTokens, int measure,
                           int *error, double x) {
  // 0 - все ок
  // 1 - деление на 0
  // 2 - ошибка в тригонометрической функции
  Stack stack;
  int is_x = 0;
  int flag_exit = 0;
  initializeStack(&stack, numTokens);
  for (int i = 0; i < numTokens && flag_exit == 0; ++i) {
    if (*error == 0) {
      if (tokens[i].type == 'n' || tokens[i].type == 't') {
        push(&stack, tokens[i]);
      } else if (tokens[i].type == 'o') {
        Token operand2 = pop(&stack);
        if (operand2.type == 't') {
          operand2.value = x;
          is_x = 1;
        }
        Token operand1 = pop(&stack);
        if (operand1.type == 't') {
          operand1.value = x;
          is_x = 1;
        }
        Token result;
        result.type = 'n';
        result.value =
            calculate(operand1.value, operand2.value, tokens[i].oper, error);
        push(&stack, result);
      } else if (tokens[i].type == 'f') {
        Token operand = pop(&stack);
        if (operand.type == 't') {
          operand.value = x;
          is_x = 1;
        }
        Token result;
        result.type = 'n';
        result.value = calculate_function(operand.value, tokens[i].oper,
                                          measure, error, is_x);
        if (is_x && (result.value == INF || result.value == -INF)) {
          flag_exit = 1;
        }
        push(&stack, result);
      }
      // else {
      //   exit(EXIT_FAILURE);
      // }
    }
  }

  Token res_token = pop(&stack);
  double res = res_token.value;
  if (res_token.type == 't') res = x;
  freeStack(&stack);
  return res;
}
