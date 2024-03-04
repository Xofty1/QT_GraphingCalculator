
#include "../parse.h"

int is_oper(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' ||
         c == ')';
}

/*
sin = s
cos = c
arcsin = i
arccos = o
tan = t
atan = a
sqrt = q
ln = l
log = g
mod = m
*/

int is_function(const char* str, char* c) {
  int res = 0;
  if (strcmp(str, "sin") == 0) {
    // strcpy(c, "s");
    *c = 's';
    res = 1;
  } else if (strcmp(str, "cos") == 0) {
    *c = 'c';
    res = 1;
  } else if (strcmp(str, "asin") == 0) {
    *c = 'i';
    res = 1;
  } else if (strcmp(str, "acos") == 0) {
    *c = 'o';
    res = 1;
  } else if (strcmp(str, "tan") == 0) {
    *c = 't';
    res = 1;
  } else if (strcmp(str, "atan") == 0) {
    *c = 'a';
    res = 1;
  } else if (strcmp(str, "sqrt") == 0) {
    *c = 'q';
    res = 1;
  } else if (strcmp(str, "ln") == 0) {
    *c = 'l';
    res = 1;
  } else if (strcmp(str, "log") == 0) {
    *c = 'g';
    res = 1;
  } else if (strcmp(str, "mod") == 0) {
    *c = 'm';
    res = 1;
  }
  return res;
}

Token* parse_expression(const char* expression, int* token_count) {
  Token* tokens = malloc(strlen(expression) * sizeof(Token) * 3);
  int i = 0;
  int token_index = 0;
  if (expression[0] == '-') {
    tokens[token_index].type = 'n';
    tokens[token_index].value = 0;
    token_index++;
    tokens[token_index].type = 'o';
    tokens[token_index].oper = '-';
    token_index++;
    i++;
  }
  while (expression[i] != '\0') {
    if (expression[i] == ' ') {
      i++;
      continue;
    }
    if (i > 0)
      if (expression[i] == '-' && expression[i - 1] == '(') {
        tokens[token_index].type = 'n';
        tokens[token_index].value = 0;
        token_index++;
        tokens[token_index].type = 'o';
        tokens[token_index].oper = '-';
        token_index++;
        i++;
      }

    // Если текущий символ - цифра
    if (isdigit(expression[i]) ||
        (expression[i] == '-' && (i == 0 || expression[i - 1] == '('))) {
      tokens[token_index].type = 'n';
      tokens[token_index].value = atof(expression + i);
      token_index++;
      while (isdigit(expression[i]) || expression[i] == '.') {
        i++;
      }
    } else if (is_oper(expression[i])) {
      tokens[token_index].type = 'o';
      tokens[token_index].oper = expression[i];
      token_index++;
      i++;
    } else if (isalpha(expression[i])) {
      // Если текущий символ - буква, то это может быть функция

      if (expression[i] == 'x') {
        tokens[token_index].type = 't';
        tokens[token_index].oper = 'x';
        token_index++;
        i++;
      } else {
        int func_start = i;
        while (isalpha(expression[i])) {
          i++;
        }
        int func_length = i - func_start;
        char* function_name = malloc(func_length + 1);
        strncpy(function_name, expression + func_start, func_length);
        function_name[func_length] = '\0';
        char c;
        if (is_function(function_name, &c)) {
          tokens[token_index].type = 'f';
          if (c == 'm') tokens[token_index].type = 'o';
          tokens[token_index].oper = c;
          token_index++;
        } else {
          free(tokens);
          free(function_name);
          return NULL;
        }
        free(function_name);
      }
    } else {
      free(tokens);
      return NULL;
    }
  }

  *token_count = token_index;
  return tokens;
}
