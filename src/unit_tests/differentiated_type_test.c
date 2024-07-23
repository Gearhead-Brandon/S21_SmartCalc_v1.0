#include <check.h>

#include "../s21_smart_calc.h"

START_TEST(test_differentiated_type) {
  calculator *calc;
  char *str;

  calc->credit.amount = 100000;
  calc->credit.term = 24;
  calc->credit.rate = 10;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "5000.00 Руб ... 4201.39 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 10416.67, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 110416.67, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 100000;
  calc->credit.term = 2;
  calc->credit.rate = 20;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "51666.67 Руб ... 50833.33 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 2500.00, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 102500.00, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 500000;
  calc->credit.term = 60;
  calc->credit.rate = 30;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "20833.33 Руб ... 8541.67 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 381250.00, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 881250.00, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 1000000;
  calc->credit.term = 12;
  calc->credit.rate = 15;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "95833.33 Руб ... 84375.00 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 81250.00, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 1081250.00, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 666666;
  calc->credit.term = 120;
  calc->credit.rate = 90;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "55555.50 Руб ... 5972.22 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 3024996.97, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 3691662.97, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 10000000;
  calc->credit.term = 300;  // 25
  calc->credit.rate = 20;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "200000.00 Руб ... 33888.89 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 25083333.33, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 35083333.33, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 50000;
  calc->credit.term = 1;
  calc->credit.rate = 5;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "50208.33 Руб ... 50208.33 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 208.33, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 50208.33, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 50000;
  calc->credit.term = 60;
  calc->credit.rate = 5;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "1041.67 Руб ... 836.81 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 6354.17, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 56354.17, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 750000;
  calc->credit.term = 60;
  calc->credit.rate = 50;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "43750.00 Руб ... 13020.83 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 953125.00, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 1703125.00, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 300015;
  calc->credit.term = 12;
  calc->credit.rate = 10;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "27501.38 Руб ... 25209.59 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 16250.81, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 316265.81, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc->credit.amount = 200000;
  calc->credit.term = 24;
  calc->credit.rate = 25;
  calculate_differentiated(calc, &str);
  ck_assert_str_eq(str, "12500.00 Руб ... 8506.94 Руб");
  ck_assert_double_eq_tol(calc->credit.res_inte_rest, 52083.33, 1e-2);
  ck_assert_double_eq_tol(calc->credit.res_debt_interest, 252083.33, 1e-2);

  free(str);
}
END_TEST

Suite *differentiated_type(void) {
  Suite *suite = suite_create("differentiated_type");
  TCase *test_case = tcase_create("case_differentiated_type");

  tcase_add_test(test_case, test_differentiated_type);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = differentiated_type();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}