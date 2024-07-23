#include <check.h>

#include "../s21_smart_calc.h"

void add_rate_record(calculator *calc, double amount, double rate) {
  for (int i = 0, flag = 1; i < ROWS && flag; i++) {
    if (calc->deposit.mat_rate[i][0] == -1) {
      calc->deposit.mat_rate[i][0] = 1;
      calc->deposit.mat_rate[i][1] = amount;
      calc->deposit.mat_rate[i][2] = rate;
      flag = 0;
    }
  }
}

void clear_rate_list(int counter, calculator *calc) {
  int stop = 0;
  for (int i = 0; i < counter; i++) {
    calc->deposit.mat_rate[i][0] = -1;
    calc->deposit.mat_rate[i][1] = 0;
    calc->deposit.mat_rate[i][2] = 0;
  }
}

void add_repl_record(calculator *calc, double arr[6]) {
  for (int i = 0, flag = 1; i < ROWS && flag; i++) {
    if (calc->deposit.mat_repl[i][0] == -1) {
      calc->deposit.mat_repl[i][0] = arr[0];
      calc->deposit.mat_repl[i][1] = arr[1];
      calc->deposit.mat_repl[i][2] = arr[2];
      calc->deposit.mat_repl[i][3] = arr[3];
      calc->deposit.mat_repl[i][4] = arr[4];
      calc->deposit.mat_repl[i][5] = arr[5];
      calc->deposit.mat_repl[i][6] = arr[6];
      flag = 0;
    }
  }
}

void clear_repl_list(int counter, calculator *calc) {
  int stop = 0;
  for (int i = 0; i < counter; i++) {
    calc->deposit.mat_repl[i][0] = -1;
    calc->deposit.mat_repl[i][1] = 0;
    calc->deposit.mat_repl[i][2] = 0;
    calc->deposit.mat_repl[i][3] = 0;
    calc->deposit.mat_repl[i][4] = 0;
    calc->deposit.mat_repl[i][5] = -1;
    calc->deposit.mat_repl[i][6] = 0;
  }
}

START_TEST(test_deposit) {
  calculator calc;
  calculator_init(&calc);
  calc.deposit.amount = 100000;
  calc.deposit.term = 24;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = дней;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 657.53, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 100657.53, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 24;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 15;
  calc.deposit.all_term_type = дней;
  calc.deposit.periodicity_type = в_конце_срока;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 986.30, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 100986.30, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 6;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 15;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждую_неделю;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 7465.3, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 107465.3, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 6;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 5;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 2488.44, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 102488.44, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 9;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 5;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_квартал;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 3745.27, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 103745.27, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 1;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = лет;
  calc.deposit.periodicity_type = раз_в_полгода;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 10004.19, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 110004.19, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 122;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = дней;
  calc.deposit.periodicity_type = каждую_неделю;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 3337.53, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 103337.53, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 122;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = дней;
  calc.deposit.periodicity_type = каждую_неделю;
  calc.deposit.capytalization_type = 1;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 3390.59, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 103390.59, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 2;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = лет;
  calc.deposit.periodicity_type = раз_в_год;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 20000, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 120000.00, 1e-2);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 2;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_суммы;
  calc.deposit.rate = 10;
  add_rate_record(&calc, 10000, 15.0);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 2506.29, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 102506.29, 1e-2);
  clear_rate_list(2, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 2;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_суммы;
  calc.deposit.rate = 10;
  add_rate_record(&calc, 10000, 30.0);
  add_rate_record(&calc, 10000, 80.0);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 13366.9, 1e-1);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 113366.9, 1e-1);
  clear_rate_list(2, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 2;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_суммы;
  calc.deposit.rate = 10;
  add_rate_record(&calc, -110000, 5.0);
  add_rate_record(&calc, -10000, 10.0);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 835.50, 1e-1);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 100835.50, 1e-1);
  clear_rate_list(2, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 2;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_суммы;
  calc.deposit.rate = 10;
  add_rate_record(&calc, -110000, 0);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 0, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 100000, 1e-2);
  clear_rate_list(2, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 2;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_суммы;
  add_rate_record(&calc, -110000, 10);
  add_rate_record(&calc, 20, 5);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 835.50, 1e-1);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 100835.50, 1e-1);
  clear_rate_list(2, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 2;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_срока;
  calc.deposit.rate = 10;
  add_rate_record(&calc, 20, 10);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 1123, 1e-1);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 101123.00, 1e-1);
  clear_rate_list(2, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 2;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_срока;
  calc.deposit.rate = 10;
  add_rate_record(&calc, 20, 0);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 0, 1e-1);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 100000, 1e-1);
  clear_rate_list(2, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 6;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_срока;
  calc.deposit.rate = 10;
  add_rate_record(&calc, 20, 5);
  add_rate_record(&calc, 60, 10);
  add_rate_record(&calc, 120, 15);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 4728.12, 1e-1);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 104728.12, 1e-1);
  clear_rate_list(2, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 6;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_срока;
  calc.deposit.rate = 10;
  add_rate_record(&calc, -20, 5);
  add_rate_record(&calc, -60, 10);
  add_rate_record(&calc, -120, 15);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 7465.3, 1e-1);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 107465.3, 1e-1);
  clear_rate_list(3, &calc);
  reduction_initial_state(&calc);
  /////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 6;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = от_срока;
  calc.deposit.rate = 10;
  add_rate_record(&calc, -20, 5);
  add_rate_record(&calc, 60, 10);
  add_rate_record(&calc, -120, 15);
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = каждый_день;
  calc.deposit.capytalization_type = 0;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 5798.56, 1e-1);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 105798.56, 1e-1);
  clear_rate_list(3, &calc);
  reduction_initial_state(&calc);
}
END_TEST

START_TEST(test_deposit_taxe) {
  calculator calc;
  calculator_init(&calc);
  calc.deposit.amount = 1000000;
  calc.deposit.term = 3;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 40;
  calc.deposit.all_term_type = лет;
  calc.deposit.periodicity_type = каждую_неделю;
  calc.deposit.capytalization_type = 0;
  calc.deposit.taxes_type = 1;
  calc.deposit.taxe = 15 / 100.0;
  calc.deposit.taxe_free_amount = calc.deposit.amount * calc.deposit.taxe;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 1200000, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 2200000.00, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_taxes, 89521.9, 1e-1);
  reduction_initial_state(&calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 1000000;
  calc.deposit.term = 3;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 40;
  calc.deposit.all_term_type = лет;
  calc.deposit.periodicity_type = каждую_неделю;
  calc.deposit.capytalization_type = 1;
  calc.deposit.taxes_type = 1;
  calc.deposit.taxe = 15 / 100.0;
  calc.deposit.taxe_free_amount = calc.deposit.amount * calc.deposit.taxe;
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 2304985.09, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 3304985.09, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_taxes, 232952.46, 1e-1);
  reduction_initial_state(&calc);
}
END_TEST

START_TEST(test_deposit_replenishment) {
  calculator calc;
  calculator_init(&calc);
  calc.deposit.amount = 100000;
  calc.deposit.term = 3;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 40;
  calc.deposit.all_term_type = лет;
  calc.deposit.periodicity_type = каждую_неделю;
  calc.deposit.capytalization_type = 0;
  double arr[7] = {_разовое, 11, 20, 2023, 20000, -1, 0};
  add_repl_record(&calc, arr);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 143671.23, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 263671.23, 1e-2);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 12;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 0;
  double arr2[7] = {_раз_в_месяц, 11, 20, 2023, 20000, -1, 0};
  add_repl_record(&calc, arr2);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 22048.68, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 362048.68, 1e-2);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 12;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 0;
  double arr3[7] = {_раз_в_месяц, 1, 20, 2023, 20000, -1, 0};
  add_repl_record(&calc, arr3);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 22048.68, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 562048.68, 1e-2);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 12;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 0;
  double arr4[7] = {_раз_в_месяц, 1, 20, 2023, -20000, -1, 0};
  add_repl_record(&calc, arr4);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 2074.45, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, -337925.45, 1e-1);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 12;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 1;
  double arr5[7] = {_раз_в_месяц, 1, 20, 2023, -20000, -1, 0};
  add_repl_record(&calc, arr5);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 2250.53, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, -337749.49, 1e-1);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 12;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 0;
  double arr6[7] = {_раз_в_месяц, 11, 5, 2023, 20000, -1, 0};
  add_repl_record(&calc, arr6);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 21031.90, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 381031.90, 1e-1);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 12;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 0;
  double arr7[7] = {_разовое, 11, 5, 2023, 20000, -1, 0};
  add_repl_record(&calc, arr7);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 10004.2, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, 130004.2, 1e-1);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 12;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 0;
  double arr8[7] = {_раз_в_месяц, 11, 5, 2022, -20000, -1, 0};
  add_repl_record(&calc, arr8);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 2495.61, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, -397504.46, 1e-1);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
  ////////////////////////////////////////////////////////////////////////////////
  calc.deposit.amount = 100000;
  calc.deposit.term = 12;
  strcpy(calc.deposit.start_date, "11/5/2023");
  calc.deposit.rate_type = фиксированная;
  calc.deposit.rate = 10;
  calc.deposit.all_term_type = месяцев;
  calc.deposit.periodicity_type = раз_в_месяц;
  calc.deposit.capytalization_type = 0;
  double arr9[7] = {_разовое, 11, 6, 2023, -120000, -1, 0};
  add_repl_record(&calc, arr9);
  calculate_deposit(&calc);
  ck_assert_double_eq_tol(calc.deposit.res_inte_charges, 10004.2, 1e-2);
  ck_assert_double_eq_tol(calc.deposit.res_amount, -9995.81, 1e-1);
  reduction_initial_state(&calc);
  clear_repl_list(1, &calc);
}
END_TEST

Suite *deposit_test(void) {
  Suite *suite = suite_create("deposit_test");
  TCase *test_case = tcase_create("case_deposit_test");

  tcase_add_test(test_case, test_deposit);
  tcase_add_test(test_case, test_deposit_taxe);
  tcase_add_test(test_case, test_deposit_replenishment);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = deposit_test();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}