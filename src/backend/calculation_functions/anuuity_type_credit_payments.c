/*!
        @file
        @brief Исходный файл с функциями вычисления аннуитетных платежей по
   кредиту
*/
#include "../../s21_smart_calc.h"

/*!
    @brief Вычисление платежей и процентов по кредиту
*/
void calculate_annuity(calculator *calc) {
  calc->credit.rate /= 100;
  calc->credit.res_mon_pay =
      calc->credit.amount * calc->credit.rate / 12.0 *
      pow(1 + calc->credit.rate / 12.0, calc->credit.term) /
      (pow(1.0 + calc->credit.rate / 12.0, calc->credit.term) - 1.0);

  calc->credit.res_inte_rest =
      calc->credit.res_mon_pay * calc->credit.term - calc->credit.amount;
  calc->credit.res_debt_interest =
      calc->credit.amount + calc->credit.res_inte_rest;
}