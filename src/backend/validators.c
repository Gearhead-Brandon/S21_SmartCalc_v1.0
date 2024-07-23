/*!
        @file
        @brief Исходный файл с функциями-валидаторами
*/
#include "../s21_smart_calc.h"

/*!
    @brief Функция валидации строки
        @param str Строка
        @return Код ошибки

        Проверяет на то, есть ли в строке что-то кроме цифр и точки.
*/
int validate_credit(char *str) {
  int size = strlen(str), code = 1, dot = 0;
  if (size == 0) code = 0;
  for (int i = 0; i < size && code; i++) {
    if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != ',')
      code = 0;

    if ((str[i] == '.' || str[i] == ',')) dot++;

    if (dot > 1) code = 0;

    if (str[i] == '.') str[i] = ',';
  }
  return code;
}

/*!
    @brief Функция валидации строки
        @param str Строка
        @return Код ошибки

        Проверяет на то, есть ли в строке что-то кроме цифр, плюса, минуса или
   точки.
*/
int validate_rate_deposit(char *str) {
  int size = strlen(str), code = 1, dot = 0;
  if (size == 0) code = 0;

  int i = 0;

  if (i == 0 && (str[i] == '.' || str[i] == ',')) code = 0;
  if (i < size && (str[i] == '.' || str[i] == ',') &&
      (str[i + 1] < '0' || str[i + 1] > '9'))
    code = 0;

  for (; i < size && code; i++) {
    if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != ',' &&
        str[i] != '+' && str[i] != '-')
      code = 0;

    if (i == 0 && (str[i] == '+' || str[i] == '-') &&
        (str[i + 1] < '0' || str[i + 1] > '9'))
      code = 0;

    if ((str[i] == '.' || str[i] == ',')) dot++;

    if (dot > 1) code = 0;

    if (str[i] == '.') str[i] = ',';
  }
  return code;
}

/*!
    @brief Функция валидации даты в строке
        @param str Строка
        @return Код ошибки
*/
int validity_date(char *str) {
  int size = strlen(str), code = 1, slash = 0, j = 0;
  char month[3], day[3], year[5];
  if (size == 0) code = 0;
  for (int i = 0; i < size && code; i++) {
    if ((str[i] < '0' || str[i] > '9') && str[i] != '/') code = 0;

    if (str[i] == '/') {
      slash++;
      // if(slash > 0)
      //     i++;
      j = 0;
      continue;
    }

    if (slash == 0)
      month[j++] = str[i];
    else if (slash == 1)
      day[j++] = str[i];
    else if (slash == 2)
      year[j++] = str[i];

    if (i == 0 && str[i] == '/') code = 0;

    if (str[i] == '/' && str[i + 1] == '/') code = 0;
  }
  if (slash != 2)
    code = 0;
  else {
    int months_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dayi = atoi(day);
    int monthi = atoi(month);
    int yeari = atoi(year);

    if (((dayi > 31 || dayi == 0) || (monthi > 12 || monthi == 0))) code = 0;

    if (dayi > months_days[monthi - 1] && monthi != 2) code = 0;

    if (monthi == 2 && ((yeari % 4 != 0 && dayi > 28) || dayi > 29)) code = 0;
  }

  return code;
}

/*!
    @brief Функция валидации строки, проверяющая есть ли что-то кроме цифр в
   строке
        @param str Строка
        @return Код ошибки
*/
int validity_check_dot(char *str) {
  int size = strlen(str), code = 1;
  if (size == 0) code = 0;
  for (int i = 0; i < size && code; i++)
    if ((str[i] < '0' || str[i] > '9')) code = 0;

  return code;
}