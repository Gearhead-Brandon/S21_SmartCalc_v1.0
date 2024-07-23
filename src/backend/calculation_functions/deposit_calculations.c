/*!
        @file
        @brief Исходный файл с функциями вычисления процентов по депозиту
*/
#include "../../s21_smart_calc.h"

/*!
    @brief Вычисление налога и процентов по депозиту
*/
void calculate_deposit(calculator *calc) {
  int days_counter = 0, error = 0, increase_point = 0, increase_date = 0, j = 0,
      rate_is_valid = 1, arr_counter = 0;

  switch (calc->deposit.all_term_type) {  // срок размещения
    case дней:
      days_counter = calc->deposit.term;
      split_date(calc, &calc->deposit.current_day, &calc->deposit.current_month,
                 &calc->deposit.current_year);
      break;
    case лет:
      // calc->deposit.term *= 12;
    case месяцев:
      if (calc->deposit.all_term_type == лет) calc->deposit.term *= 12;
      days_counter = get_total_days(calc);
      break;
  }

  calc->deposit.rate = calc->deposit.rate / 100;
  calc->deposit.res_inte_charges = 0;
  calc->deposit.count_l_a = 0;
  calc->deposit.res_taxes = 0;

  double daily_percent = 0, copy_begin_amount = calc->deposit.amount,
         buffer_capytal = 0;
  calc->deposit.lost_additions = (double *)malloc(sizeof(double));
  double *arr_repl_cuts = (double *)malloc(sizeof(double));

  if (calc->deposit.periodicity_type == в_конце_срока)
    calc->deposit.periodicity_type = каждый_день;

  processing_incorrect_replenishments(calc, calc->deposit.mat_repl,
                                      &arr_repl_cuts, &arr_counter, 0);

  processing_incorrect_replenishments(calc, calc->deposit.mat_cut,
                                      &arr_repl_cuts, &arr_counter, 1);

  calc->deposit.current_day++;

  flow_of_time(&calc->deposit.current_month, &calc->deposit.current_day,
               &calc->deposit.current_year);

  int copy_year = calc->deposit.current_year;

  increase_date = determine_refill_date(calc->deposit.current_month,
                                        calc->deposit.current_year,
                                        calc->deposit.periodicity_type);

  for (int i = 0; i < days_counter && !error; i++) {
    // printf("%c[%d;%dmDATE: %d.%d.%d %c[%dm\n",27,1,33,
    // calc->deposit.current_day, calc->deposit.current_month,
    // calc->deposit.current_year, 27, 0);

    increase_point++;

    j++;
    int leap_year = is_leap_year(calc->deposit.current_year);

    if (calc->deposit.rate_type == от_суммы)
      rate_is_valid = change_rate_on_amount(calc);

    if (calc->deposit.rate_type == от_срока)
      rate_is_valid = change_rate_on_term(calc, i);

    if (rate_is_valid) {
      daily_percent =
          calc->deposit.amount * (calc->deposit.rate / (leap_year ? 366 : 365));

      buffer_capytal += daily_percent;
    } else {
      daily_percent = 0;
      buffer_capytal = 0;
    }
    // printf("amount = (%lf) daily_percent = (%lf)\n", calc->deposit.amount,
    // daily_percent);

    switch (calc->deposit
                .periodicity_type) {  // периодичность платежа/капитализации
      case каждый_день:  // == в конце срока
        calc_periodity_types(calc, &increase_point, daily_percent,
                             &increase_date);
        break;
      case каждую_неделю:
        if (increase_point == 7)
          calc_periodity_types(calc, &increase_point, buffer_capytal,
                               &increase_date);
        break;
      case раз_в_месяц:
        if (increase_point == increase_date)
          calc_periodity_types(calc, &increase_point, buffer_capytal,
                               &increase_date);
        break;
      case раз_в_квартал:
        if (increase_point == increase_date)
          calc_periodity_types(calc, &increase_point, buffer_capytal,
                               &increase_date);
        break;
      case раз_в_полгода:
        if (increase_point == increase_date)
          calc_periodity_types(calc, &increase_point, buffer_capytal,
                               &increase_date);
        break;
      case раз_в_год:
        if (increase_point == increase_date)
          calc_periodity_types(calc, &increase_point, buffer_capytal,
                               &increase_date);
        break;
    }

    if (increase_point == 0) buffer_capytal = 0;

    replenishments_and_cuts(calc, calc->deposit.mat_repl, 0);
    replenishments_and_cuts(calc, calc->deposit.mat_cut, 1);

    calc->deposit.current_day++;
    flow_of_time(&calc->deposit.current_month, &calc->deposit.current_day,
                 &calc->deposit.current_year);

    if (calc->deposit.taxes_type &&
        copy_year < calc->deposit.current_year) {  // TAXE
      copy_year = calc->deposit.current_year;
      if (calc->deposit.temp_inte_charges > calc->deposit.taxe_free_amount) {
        double diff =
            calc->deposit.temp_inte_charges - calc->deposit.taxe_free_amount;
        calc->deposit.res_taxes += diff * 0.13;  // НДФЛ
      }
      calc->deposit.res_inte_charges += calc->deposit.temp_inte_charges;
      calc->deposit.temp_inte_charges = 0;
    }
  }

  if (calc->deposit.periodicity_type != каждый_день && increase_point != 0) {
    if (!calc->deposit.capytalization_type)
      calc->deposit.temp_inte_charges += buffer_capytal;
    else {
      calc->deposit.amount += buffer_capytal;
      calc->deposit.temp_inte_charges += buffer_capytal;
    }
  }

  if (calc->deposit.taxes_type) {
    if (calc->deposit.temp_inte_charges > calc->deposit.taxe_free_amount) {
      double diff =
          calc->deposit.temp_inte_charges - calc->deposit.taxe_free_amount;
      calc->deposit.res_taxes += diff * 0.13;  // НДФЛ
    }
    calc->deposit.res_inte_charges += calc->deposit.temp_inte_charges;
    calc->deposit.temp_inte_charges = 0;
  }

  if (arr_counter > 0) {
    for (int i = 0; i < arr_counter; i++)
      calc->deposit.amount += arr_repl_cuts[i];
  }

  free(arr_repl_cuts);

  for (int i = 0; i < calc->deposit.count_l_a; i++)
    calc->deposit.amount += calc->deposit.lost_additions[i];

  if (!calc->deposit.taxes_type)
    calc->deposit.res_inte_charges = calc->deposit.temp_inte_charges;

  if (calc->deposit.capytalization_type == 0) {
    calc->deposit.res_amount =
        calc->deposit.amount + calc->deposit.res_inte_charges;

  } else if (calc->deposit.capytalization_type == 1 &&
             calc->deposit.count_l_a > 0) {
    if (calc->deposit.amount - copy_begin_amount >= 0)
      calc->deposit.res_inte_charges = calc->deposit.amount - copy_begin_amount;

    calc->deposit.res_amount = calc->deposit.amount;
  } else if (calc->deposit.capytalization_type == 1 &&
             calc->deposit.count_l_a == 0)
    calc->deposit.res_amount = calc->deposit.amount;
}

/*!
    @brief Увелечение суммы или начисленных проценетов в зависимости от
   капитализации
        @param calc Структура
        @param point Счетчик дней
        @param num Сумма
        @param date_point День пополнения
*/
void calc_periodity_types(calculator *calc, int *point, double num,
                          int *date_point) {
  if (!calc->deposit.capytalization_type)  // !капитализация
    calc->deposit.temp_inte_charges += num;
  else {
    calc->deposit.amount += num;
    calc->deposit.temp_inte_charges += num;
  }
  if (calc->deposit.periodicity_type > 1)
    *date_point = determine_refill_date(calc->deposit.current_month,
                                        calc->deposit.current_year,
                                        calc->deposit.periodicity_type);
  *point = 0;
}

/*!
    @brief Запись в массив некорректных пополнений
        @param src Структура
        @param arr Массив
        @param n Счетчик
        @param i Счетчик
        @param flag Флаг пополнения/снятия
*/
void push_repl_to_arr(double src[10][7], double **arr, int *n, int i,
                      int flag) {
  double amount = flag ? -src[i][4] : src[i][4];
  (*arr)[*n] = amount;
  (*n)++;
  *arr = (double *)realloc(*arr, sizeof(double) * ((*n) + 1));
}

/*!
    @brief Проверка некорректных пополнений
        @param calc Структура
        @param src Матрица
        @param arr Массив некорректных пополнений
        @param n Счетчик массива некорректных пополнений
        @param flag Флаг пополнения/снятия
*/
void processing_incorrect_replenishments(calculator *calc, double src[10][7],
                                         double **arr, int *n, int flag) {
  int i = 0, stop = 0;

  for (; i < ROWS && !stop; i++) {
    if (src[i][0] > -1.0) {
      int code =
          correctness_of_the_second_date(calc, src[i][1], src[i][2], src[i][3]);
      if (code == -1 || code == 0) {
        push_repl_to_arr(src, arr, n, i, flag);

        int days = count_days(
            src[i][1], src[i][2], src[i][3], calc->deposit.current_month,
            calc->deposit.current_day, calc->deposit.current_year);
        int type = src[i][0], day = src[i][2], month = src[i][1],
            year = src[i][3];

        src[i][6] = determine_refill_point(month, year, type);
        if (code == 0) src[i][6] += 1;

        if (type > 0) {
          src[i][5] = 2;
          if (code == -1) {
            day++;
            flow_of_time(&month, &day, &year);
          }
          // printf("START month = %d\n", month);
          for (int m = 0; m < days - 1; m++) {
            if ((int)src[i][5] == (int)src[i][6]) {
              push_repl_to_arr(src, arr, n, i, flag);
              // printf("month2 = %d\n", month);
              src[i][6] = determine_refill_point(month, year, type);
              // printf("NEW COUNTER = %.0lf\n", src[i][6]);
              src[i][5] = 0;
            }
            src[i][5] += 1.0;
            day++;
            flow_of_time(&month, &day, &year);
          }
        }
      }
    } else
      stop = 1;
  }
}

/*!
    @brief Определение колтичества дней пополнения
        @param month Месяц
        @param year Год
        @param type Тип
        @return Количество дней
*/
int determine_refill_date(int month, int year, int type) {
  int days = 0, months[6] = {0, 0, 1, 3, 6, 12};

  int counter = months[type];

  for (int i = 0; i < counter; i++) {
    days += days_in_month(month, year);
    month++;
    increase_in_months(&month, &year);
  }

  return days;
}

/*!
    @brief Обработчик пополнений и снятий
        @param calc Структура
        @param arr Матрица
        @param flag Флаг пополнения/снятия
*/
void replenishments_and_cuts(calculator *calc, double arr[10][7], int flag) {
  int stop = 0;

  if (arr[0][0] >= 0)
    for (int i = 0; i < ROWS && !stop; i++) {
      if ((int)arr[i][0] == -1) continue;

      calc_replenishments(calc, arr, i, flag);
    }
}

/*!
    @brief Сбор потерянных пополнений/снятий
        @param calc Структура
        @param amount Сумма
*/
void collect_lost_additions(calculator *calc, double amount) {
  calc->deposit.lost_additions[calc->deposit.count_l_a] = amount;
  calc->deposit.count_l_a++;
  calc->deposit.lost_additions =
      (double *)realloc(calc->deposit.lost_additions,
                        sizeof(double) * ((calc->deposit.count_l_a) + 1));
}

/*!
    @brief Расчет пополнений/снятий
        @param calc Структура
        @param arr Матрица
        @param i Индекс
        @param flag Флаг пополнения/снятия
*/
void calc_replenishments(calculator *calc, double arr[10][7], int i, int flag) {
  int day1 = calc->deposit.current_day;
  int month1 = calc->deposit.current_month;
  int year1 = calc->deposit.current_year;
  double amount = 0;
  int day2 = arr[i][2];
  int month2 = arr[i][1];
  int year2 = arr[i][3];

  if ((year1 == year2 && month1 == month2 && day1 == day2)) {
    if (arr[i][5] == -1.0) {
      amount = flag ? -arr[i][4] : arr[i][4];

      if (calc->deposit.amount + amount >= 0) {
        calc->deposit.amount += amount;
      } else
        collect_lost_additions(calc, amount);

      if ((int)arr[i][0] > 0) {
        arr[i][5] = 0;
        arr[i][6] = determine_refill_point(month2, year2, arr[i][0]);
      }
    }
  }

  if ((int)arr[i][5] == arr[i][6]) {
    amount = flag ? -arr[i][4] : arr[i][4];

    if (calc->deposit.amount + amount >= 0) {
      calc->deposit.amount += amount;
    } else
      collect_lost_additions(calc, amount);

    arr[i][5] = 0;
    arr[i][6] = determine_refill_point(month1, year1, arr[i][0]);
  }

  if ((int)arr[i][5] >= 0) arr[i][5] += 1;
}

/*!
    @brief Определение колтичества дней до пополнения для пополнений и снятий
        @param month Месяц
        @param year Год
        @param type Тип пополнения/снятия
        @return Количество дней
*/
int determine_refill_point(int month, int year, int type) {
  int days = 0, months[6] = {0, 1, 2, 3, 6, 12};

  int counter = months[type];

  for (int i = 0; i < counter; i++) {
    days += days_in_month(month, year);
    month++;
    increase_in_months(&month, &year);
  }

  return days;
}

/*!
    @brief Изменение ставки от периода
        @param calc Структура
        @param point день именения ставки
        @return Код ошибки
*/
int change_rate_on_term(calculator *calc, int point) {
  int code = 0, stop = 0, iteration = 0;
  double day = 0;

  for (int i = 0; i < ROWS && !stop; i++) {
    if (calc->deposit.mat_rate[i][0] == 1.0) {
      int flag = 0;
      if (point >= calc->deposit.mat_rate[i][1]) {
        if (iteration == 0) flag = 1;

        if (iteration > 0 &&
            ((day >= 0 && day <= calc->deposit.mat_rate[i][1]) ||
             (day < 0 && day >= calc->deposit.mat_rate[i][1]) ||
             (day < 0 && calc->deposit.mat_rate[i][1] >= 0)))
          flag = 1;

        if (iteration > 0 && (day < 0 && calc->deposit.mat_rate[i][1] >= 0 &&
                              day <= calc->deposit.mat_rate[i][1]))
          flag = 1;

        if (flag) {
          calc->deposit.rate = calc->deposit.mat_rate[i][2] / 100;
          day = calc->deposit.mat_rate[i][1];
        }
        code = 1;
        iteration++;
      }
    } else
      stop = 1;
  }

  if (calc->deposit.rate == 0.0) code = 0;

  return code;
}

/*!
    @brief Изменение ставки от суммы
        @param calc Структура
        @return Код ошибки
*/
int change_rate_on_amount(calculator *calc) {
  int code = 0, stop = 0, iteration = 0;
  double amount = 0;

  for (int i = 0; i < ROWS && !stop; i++) {
    if (calc->deposit.mat_rate[i][0] == 1.0 &&
        calc->deposit.amount >= calc->deposit.mat_rate[i][1]) {
      int flag = 0;

      if (iteration == 0) {
        flag = 1;
      }
      if (iteration > 0 &&
          ((amount >= 0 && amount <= calc->deposit.mat_rate[i][1]) ||
           (amount < 0 && amount >= calc->deposit.mat_rate[i][1])))
        flag = 1;

      if (iteration > 0 && (amount < 0 && calc->deposit.mat_rate[i][1] >= 0 &&
                            amount <= calc->deposit.mat_rate[i][1]))
        flag = 1;

      if (flag) {
        calc->deposit.rate = calc->deposit.mat_rate[i][2] / 100.0;
        amount = calc->deposit.mat_rate[i][1];
      }

      code = 1;
      iteration++;
    } else
      stop = 1;
  }
  if (calc->deposit.rate == 0.0) code = 0;

  return code;
}

/*!
    @brief Проверка, является ли год високосным
        @param year Год
        @return Булево значение
*/
int is_leap_year(int year) {
  if (year % 4 == 0)
    return 1;
  else
    return 0;
}

/*!
    @brief Определние количества дней в месяце
        @param month Месяц
        @param year Год
        @return Количество дней
*/
int days_in_month(int month, int year) {
  int days = 0;

  switch (month) {
    case 1:   // Январь
    case 3:   // Март
    case 5:   // Май
    case 7:   // Июль
    case 8:   // Август
    case 10:  // Октябрь
    case 12:  // Декабрь
      days = 31;
      break;
    case 4:   // Апрель
    case 6:   // Июнь
    case 9:   // Сентябрь
    case 11:  // Ноябрь
      days = 30;
      break;
    case 2:  // Февраль
      if (is_leap_year(year))
        days = 29;  // Високосный год
      else
        days = 28;

      break;
  }

  return days;
}

/*!
    @brief Разбиение даты на месяц, день и год
        @param calc Структура
        @param day День
        @param month Месяц
        @param year Год
*/
void split_date(calculator *calc, int *day, int *month, int *year) {
  char *str = strtok(calc->deposit.start_date, "/");
  int num = atoi(str);
  calc->deposit.current_month = num;
  *month = num;

  str = strtok(NULL, "/");
  num = atoi(str);
  calc->deposit.current_day = num;
  *day = num;

  str = strtok(NULL, "/");
  num = atoi(str);
  calc->deposit.current_year = num;
  *year = num;
}

/*!
    @brief Сколько дней содержат один или несколько месяцев
        @param calc Структура
        @return Количество дней
*/
int get_total_days(calculator *calc) {
  int total_days = 0;

  int current_day = 0;
  int current_month = 0;
  int current_year = 0;

  split_date(calc, &current_day, &current_month, &current_year);

  int num_months = calc->deposit.term;
  for (int i = 0; i < num_months; i++) {
    int days_in_current_month = days_in_month(current_month, current_year);
    total_days += days_in_current_month;

    // Переход к следующему месяцу
    current_month++;
    if (current_month > 12) {
      current_month = 1;
      current_year++;
    }
  }
  return total_days;
}

/*!
    @brief Изменение даты в зависимости от дня, месяца и года
        @param month Месяц
        @param day День
        @param year Год
*/
void flow_of_time(int *month, int *day, int *year) {
  if (*day > days_in_month(*month, *year)) {
    (*day) = 1;
    (*month)++;

    if ((*month) > 12) {
      (*month) = 1;

      (*year)++;
    }
  }
}

/*!
    @brief Изменение года в зависимости от месяца
        @param month Месяц
        @param year Год
*/
void increase_in_months(int *month, int *year) {
  if (*month > 12) {
    *month = 1;
    (*year)++;
  }
}

/*!
    @brief Больше ли вторая дата первой
        @param calc Структура
        @param month2 Месяц
        @param day2 День
        @param year2 Год
        @return Код проверки
*/
int correctness_of_the_second_date(calculator *calc, int month2, int day2,
                                   int year2) {
  int code = 1;

  if (year2 < calc->deposit.current_year ||
      (year2 == calc->deposit.current_year &&
       month2 < calc->deposit.current_month) ||
      (year2 == calc->deposit.current_year &&
       month2 == calc->deposit.current_month &&
       day2 < calc->deposit.current_day))
    code = -1;
  if (calc->deposit.current_day == day2 &&
      calc->deposit.current_month == month2 &&
      calc->deposit.current_year == year2)
    code = 0;

  return code;
}

/*!
    @brief Считает количество дней между двумя датами
        @param month1 Месяц
        @param day1 День
        @param year1 Год
        @param month2 Месяц
        @param day2 День
        @param year2 Год
        @return Количество дней
*/
int count_days(int month1, int day1, int year1, int month2, int day2,
               int year2) {
  int total_days = 0;

  // Проверка на правильность порядка дат
  // if (year2 < year1 || (year2 == year1 && month2 < month1) || (year2 == year1
  // && month2 == month1 && day2 < day1)) {
  //     printf("Ошибка: Некорректный порядок дат\n");
  //     return -1;  // Возвращаем -1, чтобы обозначить ошибку
  // }

  while (year1 != year2 || month1 != month2 || day1 != day2) {
    total_days++;

    day1++;

    flow_of_time(&month1, &day1, &year1);
  }

  return total_days;
}