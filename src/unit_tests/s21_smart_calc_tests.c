#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../polish.h"

#define MAX_SIZE_STACK 500
#define ESP 1e-7

START_TEST(test_sin) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "-sin(-2-3*1.55)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  double b = -2 - 3 * 1.55;
  double a = -sin(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_asin) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "-asin(0.5)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  double b = 0.5;
  float a = -asin(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_cos) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 2.1;
  int error = 0;
  strcpy(input, "cos(x*2.1)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  ck_assert_ldouble_eq_tol(end, cos(2.1 * 2.1), ESP);
}
END_TEST

START_TEST(test_acos) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "acos(0.5)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  double b = 0.5;
  double a = acos(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_tan) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "tan(2.1)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  double b = 2.1;
  double a = tan(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_atan) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "atan(2.1)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  double b = 2.1;
  ck_assert_ldouble_eq_tol(end, atan(b), ESP);
}
END_TEST

START_TEST(test_sqrt) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "sqrt(21)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  double b = 21;
  ck_assert_ldouble_eq_tol(end, sqrt(b), ESP);
}
END_TEST

START_TEST(test_log) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "log(2.1)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  double a = log10f(2.1);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_ln) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "ln(2.1)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  double a = log(2.1);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_mod) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "10m3+2");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  ck_assert_ldouble_eq_tol(end, 3.0, ESP);
}
END_TEST

START_TEST(test_pow) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "2^(3^4)");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  ck_assert_ldouble_eq_tol(end, pow(2, pow(3, 4)), ESP);
}
END_TEST

START_TEST(test_error) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "2*/+-0");
  convert_to_polish_record(input, output);
  calculate_value(output, x, &error);
  ck_assert_int_eq(error, SUF);
}
END_TEST

START_TEST(test_div_on_zero) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input, "2/0");
  convert_to_polish_record(input, output);
  double res = calculate_value(output, x, &error);
  ck_assert_double_eq(res, 1.0 / 0.0);
}
END_TEST

START_TEST(test_algorithm) {
  char input[MAX_SIZE_STACK];
  char output[MAX_SIZE_STACK];
  double x = 0;
  int error = 0;
  strcpy(input,
         "15/(7-(1 + "
         "1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
         "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))");
  convert_to_polish_record(input, output);
  double end = calculate_value(output, x, &error);
  ck_assert_ldouble_eq_tol(end, -30.0721649484536082, ESP);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("Core");
  TCase *tc = tcase_create("function");
  SRunner *sr = srunner_create(suite);
  suite_add_tcase(suite, tc);

  tcase_add_test(tc, test_algorithm);

  tcase_add_test(tc, test_div_on_zero);
  tcase_add_test(tc, test_error);
  tcase_add_test(tc, test_pow);
  tcase_add_test(tc, test_mod);
  tcase_add_test(tc, test_cos);
  tcase_add_test(tc, test_sin);
  tcase_add_test(tc, test_tan);
  tcase_add_test(tc, test_acos);
  tcase_add_test(tc, test_asin);
  tcase_add_test(tc, test_atan);
  tcase_add_test(tc, test_sqrt);
  tcase_add_test(tc, test_ln);
  tcase_add_test(tc, test_log);

  srunner_run_all(sr, CK_VERBOSE);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}