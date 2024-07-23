#include <check.h>

#include "../s21_smart_calc.h"

START_TEST(test_annuity_type) {
  calculator calc;
  calc.credit.amount = 100000;
  calc.credit.term = 24;
  calc.credit.rate = 10;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 4614.49, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 10747.8, 1e-1);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 110747.8, 1e-1);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 100000;
  calc.credit.term = 2;
  calc.credit.rate = 20;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 51253.44, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 2506.88, 1e-1);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 102506.88, 1e-1);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 500000;
  calc.credit.term = 60;
  calc.credit.rate = 30;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 16176.70, 1e-2);

  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 470601.9, 1e-1);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 970601.9, 1e-1);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 1000000;
  calc.credit.term = 12;
  calc.credit.rate = 15;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 90258.31, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 83099.72, 1e-1);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 1083099.72, 1e-1);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 666666;
  calc.credit.term = 120;  // 25
  calc.credit.rate = 90;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 50008.46, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 5334349.43, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 6001015.43, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 10000000;
  calc.credit.term = 300;  // 25
  calc.credit.rate = 20;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 167845.18, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 40353553.17, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 50353553.17, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 50000;
  calc.credit.term = 1;
  calc.credit.rate = 5;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 50208.33, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 208.33, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 50208.33, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 50000;
  calc.credit.term = 60;
  calc.credit.rate = 5;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 943.56, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 6613.70, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 56613.70, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 750000;
  calc.credit.term = 60;
  calc.credit.rate = 50;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 34203.56, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 1302213.37, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 2052213.37, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 300015;
  calc.credit.term = 12;
  calc.credit.rate = 10;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 26376.08, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 16498.02, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 316513.02, 1e-2);
  //////////////////////////////////////////////////////////////////////////////////
  calc.credit.amount = 200000;
  calc.credit.term = 24;
  calc.credit.rate = 25;
  calculate_annuity(&calc);
  ck_assert_double_eq_tol(calc.credit.res_mon_pay, 10674.30, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_inte_rest, 56183.30, 1e-2);
  ck_assert_double_eq_tol(calc.credit.res_debt_interest, 256183.30, 1e-2);
}
END_TEST

Suite *annuity_type(void) {
  Suite *suite = suite_create("annuity_type");
  TCase *test_case = tcase_create("case_annuity_type");

  tcase_add_test(test_case, test_annuity_type);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = annuity_type();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}