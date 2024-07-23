#include <check.h>

#include "../s21_smart_calc.h"

START_TEST(test_polish_notation_operators) {
  Queue queue = {NULL};
  double res = 0;
  char exp_0[6] = "2+3";
  int code = from_infix_to_postfix(exp_0, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 5, 1e-7);
  clear_queue(&queue);
  // ///////////////////////////////////////////////////////////////
  char exp_1[20] = "(1+2)*(+(-3)-(-4))";
  code = from_infix_to_postfix(exp_1, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 3, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_2[15] = "5-((-2)^2-3)";
  code = from_infix_to_postfix(exp_2, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 4, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_3[15] = "-2^(1+3)";
  code = from_infix_to_postfix(exp_3, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 16, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_4[15] = "2-(-3)+3";
  code = from_infix_to_postfix(exp_4, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 8, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_5[20] = "2-(((-3)+4)-5)+3";
  code = from_infix_to_postfix(exp_5, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 9, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_6[20] = "2-(((-3)+4)-5)+3";
  code = from_infix_to_postfix(exp_6, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 9, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_7[10] = "20/5";
  code = from_infix_to_postfix(exp_7, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 4, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_8[10] = "-2+2.4";
  code = from_infix_to_postfix(exp_8, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, -2 + 2.4, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_9[10] = "8562.";
  code = from_infix_to_postfix(exp_9, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 8562.0, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_10[10] = "2+2*3";
  code = from_infix_to_postfix(exp_10, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 8.0, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_11[10] = "1/2";
  code = from_infix_to_postfix(exp_11, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 1.0 / 2, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_12[15] = "((2+3)*2)*0";
  code = from_infix_to_postfix(exp_12, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 0, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_13[15] = "((2+3*x)*2)";
  char x_1[2] = "2";
  code = from_infix_to_postfix(exp_13, x_1, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, x_1, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 16, 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_14[15] = "((x*x*x)*2)";
  char x_2[2] = "2";
  code = from_infix_to_postfix(exp_14, x_2, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, x_2, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, 16, 1e-7);

  clear_queue(&queue);

  ///////////////////////////////////////////////////////////////
  char exp_15[23] = "(((x*x*x)*2)+100)mod 7";
  char x_3[2] = "2";
  code = from_infix_to_postfix(exp_15, x_3, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, x_3, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, fmod((((2 * 2 * 2) * 2) + 100), 7), 1e-7);

  clear_queue(&queue);

  ///////////////////////////////////////////////////////////////
  char exp_16[20] = "-(2+2*3)+4";
  code = from_infix_to_postfix(exp_16, NULL, &queue);
  // ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, -4, 1e-7);
}
END_TEST

START_TEST(test_polish_notation_functions) {
  Queue queue = {NULL};
  double res = 0;
  char exp_0[11] = "sin(100)";
  int code = from_infix_to_postfix(exp_0, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, sin(100.0), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_1[20] = "log(100)";
  code = from_infix_to_postfix(exp_1, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, log10(100), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_2[15] = "cos(1000)";
  res = 0;
  code = from_infix_to_postfix(exp_2, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, cos(1000), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_3[15] = "tan(100)";
  code = from_infix_to_postfix(exp_3, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, tan(100), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_4[15] = "acos(0.5)";
  code = from_infix_to_postfix(exp_4, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, acos(0.5), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_5[20] = "asin(0.5)";
  code = from_infix_to_postfix(exp_5, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, asin(0.5), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_6[12] = "atan(100)";
  code = from_infix_to_postfix(exp_6, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, atan(100), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_7[10] = "sqrt(625)";
  code = from_infix_to_postfix(exp_7, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, sqrt(625), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_8[10] = "log(2+2.4)";
  code = from_infix_to_postfix(exp_8, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, log10(2 + 2.4), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_9[10] = "ln(8562)";
  code = from_infix_to_postfix(exp_9, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, log(8562), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_10[20] = "sin(cos(2+2*10))";
  code = from_infix_to_postfix(exp_10, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, sin(cos(2 + 2 * 10)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_11[20] = "sqrt(36) * sqrt(25)";
  code = from_infix_to_postfix(exp_11, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, sqrt(36) * sqrt(25), 1e-7);

  clear_queue(&queue);
}
END_TEST

START_TEST(test_polish_notation_error_validation) {
  Queue queue = {NULL};
  char exp_0[7] = "sin()";
  double res1;
  int code = 0;
  code = from_infix_to_postfix(exp_0, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res1);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_1[20] = "2++4";
  code = from_infix_to_postfix(exp_1, NULL, &queue);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_2[15] = "(2+3";
  code = from_infix_to_postfix(exp_2, NULL, &queue);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_3[15] = "tan(100)";
  code = from_infix_to_postfix(exp_3, NULL, &queue);
  ck_assert_int_eq(code, 1);
  clear_queue(&queue);

  ///////////////////////////////////////////////////////////////
  char exp_4[15] = "acos(0.5.3)";
  code = from_infix_to_postfix(exp_4, NULL, &queue);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);

  ///////////////////////////////////////////////////////////////
  char exp_5[20] = "5(2+3)";
  code = from_infix_to_postfix(exp_5, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res1);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_6[12] = "atan(100)(";
  code = from_infix_to_postfix(exp_6, NULL, &queue);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_7[10] = "((3+6)*)";
  double res = 0;
  code = from_infix_to_postfix(exp_7, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_8[10] = "((3+6)*9)*";
  code = from_infix_to_postfix(exp_8, NULL, &queue);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_9[10] = "ln(3**2)";
  code = from_infix_to_postfix(exp_9, NULL, &queue);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);

  ///////////////////////////////////////////////////////////////
  char exp_10[10] = "sin(2*)";
  code = from_infix_to_postfix(exp_10, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_11[15] = "sqrtsqrt(36)";
  code = from_infix_to_postfix(exp_11, NULL, &queue);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_12[8] = "2+xx";
  double res3;
  code = from_infix_to_postfix(exp_12, "2", &queue);
  ck_assert_int_eq(code, 5);
  clear_queue(&queue);
}
END_TEST

START_TEST(test_polish_notation_error_calculus) {
  Queue queue = {NULL};
  double res = 0;
  char exp_0[13] = "sin(100)/0";
  int code = from_infix_to_postfix(exp_0, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_int_eq(s21_is_inf(res), s21_is_inf(INFINITY));
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_1[20] = "log(-100)";
  code = from_infix_to_postfix(exp_1, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_int_eq(s21_is_nan(res), s21_is_nan(log(-100)));
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_2[15] = "cos(1000)/0";
  code = from_infix_to_postfix(exp_2, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_int_eq(s21_is_inf(res), 1);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_3[15] = "tan(100)/0";
  code = from_infix_to_postfix(exp_3, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_int_eq(s21_is_inf(res), 1);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_4[15] = "acos(1.5)";
  code = from_infix_to_postfix(exp_4, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(acos(1.5)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_5[20] = "asin(-1.5)";
  code = from_infix_to_postfix(exp_5, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(asin(-1.5)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_6[15] = "atan(100)/0*0";
  code = from_infix_to_postfix(exp_6, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_int_eq(s21_is_nan(res), 1);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_7[12] = "sqrt(-625)";
  code = from_infix_to_postfix(exp_7, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(sqrt(-625)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_8[10] = "log(-10)";
  code = from_infix_to_postfix(exp_8, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(log10(-10)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_9[10] = "ln(-8562)";
  code = from_infix_to_postfix(exp_9, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(log(-8562)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_10[30] = "sin(cos(2+2*10))/log(26)";
  code = from_infix_to_postfix(exp_10, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_double_eq_tol(res, sin(cos(2 + 2 * 10)) / log10(26), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_11[20] = "sqrt(-36) * sqrt(0)";
  code = from_infix_to_postfix(exp_11, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(sqrt(-36) * sqrt(0)),
                          1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_12[20] = "ln(0)";
  code = from_infix_to_postfix(exp_12, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(log(0)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_13[20] = "log(0)";
  code = from_infix_to_postfix(exp_13, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(log10(0)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_14[15] = "acos(-1.5)";
  code = from_infix_to_postfix(exp_14, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(acos(-1.5)), 1e-7);
  clear_queue(&queue);
  ///////////////////////////////////////////////////////////////
  char exp_15[20] = "asin(1.5)";
  code = from_infix_to_postfix(exp_15, NULL, &queue);
  ck_assert_int_eq(code, 1);
  code = from_postfix_to_double(&queue, NULL, &res);
  ck_assert_int_eq(code, 5);
  ck_assert_double_eq_tol(s21_is_nan(res), s21_is_nan(asin(1.5)), 1e-7);

  clear_queue(&queue);
}
END_TEST

Suite *polish_notation(void) {
  Suite *suite = suite_create("polish_notation");
  TCase *test_case = tcase_create("case_polish_notation");

  tcase_add_test(test_case, test_polish_notation_operators);
  tcase_add_test(test_case, test_polish_notation_functions);
  tcase_add_test(test_case, test_polish_notation_error_validation);
  tcase_add_test(test_case, test_polish_notation_error_calculus);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = polish_notation();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}