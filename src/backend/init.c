/*!
        @file
        @brief Исходный файл с функциями инициализации структуры и матрицы
*/
#include "../s21_smart_calc.h"

/*!
    @brief Инициализация статической матрицы
        @param rows Количество строк
        @param columns Количество столбцов
        @param array Матрица
*/
void init_matrix(int rows, int columns, double array[rows][columns]) {
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      if (j == 0 || j == 5)
        array[i][j] = -1;
      else
        array[i][j] = 0;
    }
}

/*!
    @brief Инициализация структуры
        @param calc Структура
*/
void calculator_init(calculator *calc) {
  calc->is_arithmetic = 0;
  calc->f_input_x = 0;
  calc->last_x = 0;
  calc->deposit.res_taxes = 0;
  calc->graph.status = 0;

  memset(calc->input_buffer, 0, 300);
  memset(calc->X_value, 0, 20);
  memset(calc->deposit.start_date, 0, 15);
  strcat(calc->X_value, "X VALUE");

  init_matrix(10, 3, calc->deposit.mat_rate);
  init_matrix(10, 7, calc->deposit.mat_repl);
  init_matrix(10, 7, calc->deposit.mat_cut);
}

/*!
    @brief Обнуление полей структуры используемых в вычеслениях депозитов
        @param calc Структура
*/
void reduction_initial_state(calculator *calc) {
  calc->deposit.temp_inte_charges = 0;
  calc->deposit.res_inte_charges = 0;
  calc->deposit.count_l_a = 0;
  calc->deposit.taxes_type = 0;
  calc->deposit.taxe = 0;
  memset(calc->deposit.start_date, 0, 25);
  free(calc->deposit.lost_additions);

  for (int i = 0; i < ROWS; i++) {
    calc->deposit.mat_repl[i][5] = -1.0;
    calc->deposit.mat_repl[i][6] = 0;

    calc->deposit.mat_cut[i][5] = -1.0;
    calc->deposit.mat_cut[i][6] = 0;
  }
}