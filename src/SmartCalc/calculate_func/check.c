#include <check.h>
#include <string.h>

// #include "deposit.h"
// #include "credit.h"
#include <math.h>

#include "../parse.h"
#include "../pol.h"
#include "../validator.h"
// funcs
START_TEST(s21_additional) {
  char expression[3] = "2+3";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);
  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  double result = calculateExpression(g, new_token_coutn, 0, &error, 0);
  ck_assert_double_eq(result, 2 + 3);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_error) {
  char expression_1[20] = "2+3a";
  ck_assert_int_eq(isValidExpression(expression_1, 0), 0);

  char expression_2[20] = "2+3.(1+1)";
  ck_assert_int_eq(isValidExpression(expression_2, 0), 0);
  char expression_3[20] = "*2+()(3";
  ck_assert_int_eq(isValidExpression(expression_3, 0), 0);

  char expression_4[20] = "()(";
  ck_assert_int_eq(isValidExpression(expression_4, 0), 0);
  char expression_5[20] = "5 mod a";
  ck_assert_int_eq(isValidExpression(expression_5, 0), 0);
  char expression_6[20] = "(  89 - p.)";
  ck_assert_int_eq(isValidExpression(expression_6, 0), 0);
  char expression_7[20] = "9 ++0";
  ck_assert_int_eq(isValidExpression(expression_7, 0), 0);
}
END_TEST

START_TEST(s21_func) {
  char expression[20] = "cos(sin(sqrt(5)))";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  char expression_2[20] = "asin(5 mod 4)";

  ck_assert_int_eq(isValidExpression(expression_2, 0), 1);
}
END_TEST

START_TEST(s21_func_2) {
  char expression[40] = "cos(sin(sqrt(-5)))  +   78 9";

  ck_assert_int_eq(isValidExpression(expression, 0), 0);
}
END_TEST

START_TEST(s21_func_3) {
  char expression[40] = "cos(sin(sqrt(-5)))  +   78.9*x";

  ck_assert_int_eq(isValidExpression(expression, 1), 1);
}
END_TEST

START_TEST(s21_func_4) {
  char expression[40] = "sqrt(5)+78.9*(4-(-9))";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  double result = calculateExpression(g, new_token_coutn, 0, &error, 0);
  double correct_result = sqrt(5) + 78.9 * (4 - (-9));
  ck_assert_double_eq(result, correct_result);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_5) {
  char expression[40] = "cos(sqrt(5))";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  double result = calculateExpression(g, new_token_coutn, 1, &error, 0);
  double correct_result = cos(sqrt(5));
  ck_assert_double_eq(result, correct_result);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_6) {
  char expression[40] = "ln(sqrt(-5))";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  calculateExpression(g, new_token_coutn, 1, &error, 0);
  ck_assert_int_eq(error, BAD_ARGUMENT);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_7) {
  char expression[40] = "sin(log(7 mod 2))";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);
  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  double result = calculateExpression(g, new_token_coutn, 1, &error, 0);
  double correct_result = sin(log(7 % 2));
  ck_assert_double_eq(result, correct_result);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_8) {
  char expression[40] = "7/0";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  calculateExpression(g, new_token_coutn, 1, &error, 0);
  ck_assert_int_eq(error, ZERO_DIV);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_9) {
  char expression[40] = "acos(100)";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  calculateExpression(g, new_token_coutn, 1, &error, 0);
  ck_assert_int_eq(error, TRIGONOM_ERROR);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_10) {
  char expression[40] = "-9+tan(atan(100))";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  double result = calculateExpression(g, new_token_coutn, 1, &error, 0);
  double correct_result = -9 + tan(atan(100));
  ck_assert_double_eq(result, correct_result);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_11) {
  char expression[40] = "asin(0.1)";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  double result = calculateExpression(g, new_token_coutn, 1, &error, 0);
  double correct_result = asin(0.1);
  ck_assert_double_eq(result, correct_result);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_12) {
  char expression[40] = "7 mod 0";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  calculateExpression(g, new_token_coutn, 1, &error, 0);

  ck_assert_double_eq(error, ZERO_DIV);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_13) {
  char expression[40] = "log(-2^3)";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;

  calculateExpression(g, new_token_coutn, 1, &error, 0);
  ck_assert_int_eq(error, BAD_ARGUMENT);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_14) {
  char expression[40] = "log(2^3)";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  double result = calculateExpression(g, new_token_coutn, 1, &error, 0);
  double correct_result = log10(pow(2, 3));
  ck_assert_double_eq(result, correct_result);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_15) {
  char expression[40] = "ln(2^3)";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;
  double result = calculateExpression(g, new_token_coutn, 1, &error, 0);
  double correct_result = log(pow(2, 3));
  ck_assert_double_eq(result, correct_result);
  free(tokens);
  free(g);
}
END_TEST

START_TEST(s21_func_16) {
  char expression[40] = "7/9+ln(-9)";

  ck_assert_int_eq(isValidExpression(expression, 0), 1);

  int token_count;
  Token* tokens = parse_expression(expression, &token_count);
  int new_token_coutn = 0;
  Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
  int error = OK;

  calculateExpression(g, new_token_coutn, 1, &error, 0);
  ck_assert_int_eq(error, BAD_ARGUMENT);
  free(tokens);
  free(g);
}
END_TEST

int main(void) {
  Suite* s1 = suite_create("s21_smartcalc");
  TCase* test_case_1 = tcase_create("s21_smartcalc");
  SRunner* sr = srunner_create(s1);
  int ERR;

  suite_add_tcase(s1, test_case_1);
  // FUNCS
  tcase_add_test(test_case_1, s21_additional);
  tcase_add_test(test_case_1, s21_error);
  tcase_add_test(test_case_1, s21_func);
  tcase_add_test(test_case_1, s21_func_2);
  tcase_add_test(test_case_1, s21_func_3);
  tcase_add_test(test_case_1, s21_func_4);
  tcase_add_test(test_case_1, s21_func_5);
  tcase_add_test(test_case_1, s21_func_6);
  tcase_add_test(test_case_1, s21_func_7);
  tcase_add_test(test_case_1, s21_func_8);
  tcase_add_test(test_case_1, s21_func_9);
  tcase_add_test(test_case_1, s21_func_10);
  tcase_add_test(test_case_1, s21_func_11);
  tcase_add_test(test_case_1, s21_func_12);
  tcase_add_test(test_case_1, s21_func_13);
  tcase_add_test(test_case_1, s21_func_14);
  tcase_add_test(test_case_1, s21_func_15);
  tcase_add_test(test_case_1, s21_func_16);
  // tcase_add_test(test_case_1, s21_func_17);
  srunner_run_all(sr, CK_ENV);
  ERR = srunner_ntests_failed(sr);

  srunner_free(sr);
  return ERR == 0 ? 0 : 1;
}