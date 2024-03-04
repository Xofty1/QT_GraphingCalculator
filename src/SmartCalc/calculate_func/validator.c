
#include "../validator.h"

bool isValidExpression(const char* expression, int is_x) {
  bool inNumber = false;
  int bracketCount = 0;
  size_t len = strlen(expression);
  bool valid = true;
  char prevOperator = '\0';
  if (isOperator(expression[0]) && expression[0] != '-')
    valid = false;
  else {
    for (int i = 0; i < (int)len; ++i) {
      if (valid == true) {
        char ch = expression[i];
        // проверка на пробелы внутри числа
        if (ch == ' ' && inNumber) {
          // Пропускаем все пробелы после первой цифры в числе
          while (expression[i + 1] == ' ' && expression[i + 1] != '\0') i++;
          // После пробелов должен идти разделитель числа или конец строки
          if (expression[i + 1] != '\0' &&
              (isdigit(expression[i + 1]) || expression[i + 1] == '.'))
            valid = false;
        }
        //////////////
        // проверка на валидный символ символ
        if (!isValidCharacter(ch)) {
          valid = false;  // Некорректный символ в выражении
        }
        /////////////
        // проверка на функцию из букв
        if (valid == false) {
          if (is_x == 0)
            valid = isFunction(expression, &i);
          else
            valid = (isFunction(expression, &i) || expression[i] == 'x');
          ch = expression[i];
          if (valid == true && inNumber) valid = false;
        }
        ///////////
        // проверка на скобочки
        if (isOpeningBracket(ch)) {
          bracketCount++;
        } else if (isClosingBracket(ch)) {
          bracketCount--;
        }
        ////////////
        if ((inNumber == false && ch == '.') ||
            (prevOperator == '.' && ((!isdigit(ch) || ch == '\0'))))
          valid = false;
        if ((isdigit(ch) && prevOperator == ')') ||
            (isdigit(prevOperator) && ch == '('))
          valid = false;
        if (isdigit(ch)) {
          inNumber = true;  // Начало числа (включая отрицательные числа)
        } else {
          inNumber = false;  // Конец числа
          if (isOperator(prevOperator)) {
            while (expression[i] == ' ') {
              i++;
            }
            if (isOperator(expression[i]) || expression[i] == ')') {
              valid = false;
            }
          } else if (prevOperator == '(') {
            while (expression[i] == ' ') {
              i++;
            }
            if ((isOperator(expression[i]) && expression[i] != '-') ||
                expression[i] == ')') {
              valid = false;
            }
          } else if (prevOperator == ')') {
            while (expression[i] == ' ') {
              i++;
            }
            if (isdigit(expression[i]) || isFunction(expression, &i) ||
                expression[i] == '(') {
              valid = false;
            }
          }
        }
        prevOperator = expression[i];
      }
    }
  }
  if (bracketCount != 0) {
    valid = false;  // Некорректное количество открывающих и закрывающих скобок
  }
  if (isOperator(expression[len - 1])) valid = false;
  return valid;
}

bool isValidCharacter(char ch) {
  return isdigit(ch) || isOperator(ch) || isOpeningBracket(ch) ||
         isClosingBracket(ch) || ch == ' ' || ch == '.';
}

bool isOpeningBracket(char ch) { return ch == '('; }

bool isClosingBracket(char ch) { return ch == ')'; }

bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

char* substring(const char* str, int start, int end) {
  if (start < 0 || end < 0 || start > end) {
    return NULL;
  }
  int sliceLength = end - start + 1;
  char* slice =
      (char*)malloc(sliceLength + 1);  // +1 для завершающего нулевого символа
  if (!slice) {
    return NULL;
  }
  strncpy(slice, str + start, sliceLength);
  slice[sliceLength] = '\0';  // Устанавливаем завершающий нулевой символ

  return slice;
}
bool isFunction(const char* str, int* i) {
  bool answer = false;
  char* substr2 = substring(str, *i, *i + 2);
  char* substr3 = substring(str, *i, *i + 3);
  char* substr4 = substring(str, *i, *i + 4);
  if ((strcmp(substr3, "sin(") == 0) || (strcmp(substr3, "cos(") == 0) ||
      (strcmp(substr3, "tan(") == 0) || (strcmp(substr3, "log(") == 0) ||
      (strcmp(substr3, "mod ") == 0)) {
    *i += 3;
    if ((strcmp(substr3, "mod ") == 0)) {
      while (str[*i] == ' ') (*i)++;
      if (isdigit(str[(*i)]))
        answer = true;
      else
        answer = false;
    } else {
      answer = true;
    }
  }

  if (strcmp(substr2, "ln(") == 0) {
    *i += 2;
    answer = true;
  }

  if ((strcmp(substr4, "acos(") == 0) || (strcmp(substr4, "asin(") == 0) ||
      (strcmp(substr4, "atan(") == 0) || (strcmp(substr4, "sqrt(") == 0)) {
    *i += 4;
    answer = true;
  }

  free(substr2);
  free(substr3);
  free(substr4);
  return answer;
}
