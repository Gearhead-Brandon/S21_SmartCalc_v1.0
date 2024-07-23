/*!
        @file
        @brief Исходный файл с функциями вычисления дифференцированных платежей
   по кредиту
*/
#include "../../s21_smart_calc.h"

/*!
    @brief Вычисление платежей и процентов по кредиту
*/
void calculate_differentiated(calculator *calc, char **out_pay) {
  calc->credit.rate /= 1200;
  double *amount_of_accrued_interest = (double *)malloc(sizeof(double));
  int current_month = 0;
  double copy_term = calc->credit.term;
  double real_month = 1;
  double ost_amount = calc->credit.amount;

  while (current_month < calc->credit.term) {
    amount_of_accrued_interest[current_month] =
        (ost_amount / copy_term) + (ost_amount * calc->credit.rate);

    ost_amount = calc->credit.amount * (1 - real_month / calc->credit.term);

    real_month++;
    copy_term--;
    current_month++;

    void *tmp = (double *)realloc(amount_of_accrued_interest,
                                  sizeof(double) * (current_month + 1));

    if (NULL == tmp)
      free(tmp);
    else
      amount_of_accrued_interest = tmp;
  }
  asprintf(out_pay, "%.2lf Руб ... %.2lf Руб", amount_of_accrued_interest[0],
           amount_of_accrued_interest[current_month - 1]);
  calc->credit.res_debt_interest = 0;
  for (int i = 0; i < current_month; i++)
    calc->credit.res_debt_interest += amount_of_accrued_interest[i];

  calc->credit.res_inte_rest =
      calc->credit.res_debt_interest - calc->credit.amount;
  free(amount_of_accrued_interest);
}