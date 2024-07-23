/*!
        @file
        @brief Исходный файл с функциями вычисления скобочных выражения
*/
#include "../../s21_smart_calc.h"

/* char rules2[20][60] = {

                       // arrow

       { "   0 ! + - * / ( ) sin cos tan asin acos atan log sqrt ln" },
//с    { "   ! 4 1 1 1 1 1 5   1                                   " },
//т    { "   + 2 2 2 1 1 1 2                                       " },
//е    { "   - 2 2 2 1 1 1 2                                       " },
//к    { "   * 2 2 2 2 2 1 2                                       " },
       { "   / 2 2 2 2 2 1 2                                       " },
       { "   ( 5 1 1 1 1 1 3                                       " },
       { " sin 2                                                   " },
       { " cos 2                                                   " },
       { " tan 2                                                   " },
       { "asin 2                                                   " },
       { "acos 2                                                   " },
       { "atan 2                                                   " },
       { " log 2                                                   " },
       { "sqrt 2                                                   " },
       { "  ln 2                                                   " }
};

// sin - a | cos - b | tan - c | asin - d | acos - e | atan - f | log - g | sqrt
- h | ln - i

// 1 - функция на стрелке помещается в стек, переход к следующей функции на
стрелке

// 2 - вытаскиваем функции из стека и добавляем ее в очередь. Остаемся на том же
символе на стрелке

// 3 - функция на стрелке и в верхняя функция в стеке уничтожаются, переход к
следующему символу на стрелке

// 4 - Конец программы. Постфиксная запись создана

// 5 - Произошла ошибка. Изначальная формула была некорректно сбалансирована


char instructions[18][20] = {

       { "0!+-DM()abcdefghi%^" },
//с    { "!4111115           " },
//т    { "+2221112           " },
//е    { "-2221112           " },
//к    { "*2222212           " },
       { "/2222212           " },
       { "(5111113           " },
       { "a                  " },
       { "b                  " },
       { "c                  " },
       { "d                  " },
       { "e                  " },
       { "f                  " },
       { "g                  " },
       { "h                  " },
       { "i                  " },
       { "%                  " },
       { "^                  " },
};
*/

/*!
    @brief Получение варианта действия со стеком и очередью
    @param last Последний элемент занесенный в стек
    @param current Текущий элемент передающийся из строки
    @return Вариант действия
*/
int get_instruction(char *last, char *current) {
  char instructions[18][20] = {
      /* INPUT */
      ///**/
      {"0!+-*/()abcdefghi%^"},  // 0
      {"!411111511111111111"},  // 1
      {"+222111211111111121"},  // 2
      {"-222111211111111121"},  // 3
      {"*222221211111111121"},  // 4
      {"/222221211111111121"},  // 5
      {"(511111311111111111"},  // 6
      {"a2222212         22"},  // 7
      {"b2222212         22"},  // 8
      {"c2222212         22"},  // 9
      {"d2222212         22"},  // 10
      {"e2222212         22"},  // 11
      {"f2222212         22"},  // 12
      {"g2222212         22"},  // 13
      {"h2222212         22"},  // 14
      {"i2222212         22"},  // 15
      {"%222221211111111121"},  // 16
      {"^222221222222222221"}   // 17 // ^^(2)
  };

  int row = get_index(last);
  row = (row >= 7) ? row - 1 : row;
  int column = get_index(current);

  return (row == -1 || column == -1) ? -1 : instructions[row][column] - '0';
}

/*!
    @brief Поиск индекса функции
    @param operation строка
    @return индекс
*/
int get_index(char *operation) {
  char functions[19][5] = {

      {"!"},     // 1
      {"+"},     // 2
      {"-"},     // 3
      {"*"},     // 4
      {"/"},     // 5
      {"("},     // 6
      {")"},     // 7
      {"sin"},   // 8
      {"cos"},   // 9
      {"tan"},   // 10
      {"asin"},  // 11
      {"acos"},  // 12
      {"atan"},  // 13
      {"log"},   // 14
      {"sqrt"},  // 15
      {"ln"},    // 16
      {"%"},     // 17
      {"^"},     // 18

  };

  int stop = 0, i = 0;
  for (; i < 19 && !stop; i++)
    if (!strcmp(operation, functions[i])) stop = 1;

  int code = i;
  if (!stop) code = -1;

  return code;
}

/*!
    @brief Проверка на то , является ли символ арифметическим
    @param sym Символ
    @return булево значение
*/
int is_arithmetic(char sym) {
  return sym == '+' || sym == '-' || sym == '/' || sym == '*' || sym == '^' ||
         sym == '%' || sym == '(' || sym == ')';
}

/*!
    @brief Проверка выражения на соотвествие инфиксной нотации
    @param str Строка
    @param have_x Флаг наличия x
    @return Код ошибки
*/
int validity_check(char *str, int *have_x) {
  int size = strlen(str), code = 0, arithmetic = 0;

  if (size == 0) code = 1;

  for (int i = 0; i < size && !code; i++) {
    if (str[i] == ' ') continue;
    if (str[i] == 'x') *have_x = 1;

    if (str[i] == 'x' && (str[i + 1] >= 'a' && str[i + 1] <= 'z')) code = 1;

    if (!((str[i] >= '0' && str[i] <= '9') ||
          (str[i] >= 'a' && str[i] <= 'z') || is_arithmetic(str[i]) ||
          str[i] == '.' || str[i] == ','))
      code = 1;

    if (str[i] == '(' && i == size - 1) code = 1;

    if (is_arithmetic(str[i])) {
      if ((arithmetic || i == size - 1) && (str[i] != '(' && str[i] != ')'))
        code = 1;
      if (i > 0 && (str[i - 1] == '(') && (str[i] != '-' && str[i] != '+') &&
          (str[i] != '(' && str[i] != ')'))
        code = 1;
      if (str[i] != '(' && str[i] != ')')
        arithmetic = 1;
      else
        arithmetic = 0;

    } else
      arithmetic = 0;
  }

  return code == 1 ? 5 : 1;
}

/*!
    @brief Проверка числа в строке на корректность
    @param str Строка
    @return Код ошибки
*/
int validity_check_x(char *str) {
  int size = strlen(str), dot = 0, code = 0, not_zero = 0;
  int i = 0;
  for (; i < size && code == 0; i++) {
    if ((i == 0 || i == 1) && !not_zero)
      if (str[i] >= '1' && str[i] <= '9') not_zero = 1;

    if (!not_zero && str[i] == '0' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
      code = 5;

    if (str[i] == '.' || str[i] == ',') {
      dot++;
      not_zero = 1;
    }
  }

  if (dot > 1) code = 5;

  return code;
}

/*!
    @brief Перевод выражения из инфиксной нотации в постфиксную в очередь
    @param str Математическое выражение в строке
    @param x переменная X
    @param queue Очередь для записи в нее
    @warning Нельзя подавать непроинициализированную очередь
    @return Код ошибки
*/
int from_infix_to_postfix(char *str, char *x, Queue *queue) {
  int stop = 0, error = 0, have_x = 0, rigth_parathenesis = 0, number = 1,
      exe = 0;

  int check = 0;
  check = validity_check(str, &have_x);

  if (have_x) have_x = validity_check_x(x);

  if (check == 5 || have_x == 5) error = 1;

  strcat(str, "!");
  int size = strlen(str);
  Node *stack = list_create();
  push(&stack, "!");

  for (int i = 0; (str[i] == '!' || i < size) && (!error && !stop); i++) {
    if (str[i] == ' ') continue;

    if (rigth_parathenesis && str[i] == '(') number -= 1;

    if (rigth_parathenesis && str[i] == ')') {
      number += 1;
      exe = number == 0 ? 1 : 0;
    } else if (number == 0)
      exe = 1;

    if (exe == 1) {
      i--;
      str[i] = ')';
      rigth_parathenesis = 0;
      number = 1;
      exe = 0;
    }

    char num[100] = {0};
    int j = 0;

    if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'x' || str[i] == '-' ||
        str[i] == '+') {
      if ((((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == 'x') &&
           (str[i - 1] == '(' || i == 0) && (str[i] == '-' || str[i] == '+')))
        num[j++] = str[i++];

      while ((str[i] >= '0' && str[i] <= '9') || str[i] == ',' ||
             str[i] == '.' || str[i] == 'x')
        num[j++] = str[i++];

      int size_num = strlen(num);

      error = validity_check_x(num);

      if (size_num > 1 || str[i] == ' ') i--;

      if (num[0] != 'x' && size_num > 0) {
        int code = validity_check_x(num);
        if (code == 5) error = 1;
      }

      j = 0;
      if (size_num > 0) enqueue(queue, num);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////

    if ((str[i] < '0' || str[i] > '9' || str[i] == '!') && str[i] != ',' &&
        str[i] != '.' && str[i] != 'x') {
      if (((i == 0 || str[i - 1] == '(') && (str[i] == '-' || str[i] == '+'))) {
        char zero[2] = "0", left_parathenesis[2] = "(";
        push(&stack, left_parathenesis);
        enqueue(queue, zero);
        rigth_parathenesis = 1;
        number = 0;
      }

      char current[4] = {0};
      char *peek = peek_stack(stack);
      current[0] = str[i];

      while (str[i] >= 'a' && str[i] <= 'z') current[j++] = str[i++];

      if (current[0] == 'm' && current[1] == 'o') strcpy(current, "%");

      if (strlen(current) > 1) i--;

      int instruction = get_instruction(peek, current);

      if (instruction == 1) push(&stack, current);

      if (instruction == 2 || instruction == 3) {
        char *in = pop(&stack);
        if (instruction == 2) {
          i -= strlen(current);
          enqueue(queue, in);
        }
        free(in);
      }

      if (instruction == 4) stop = 1;

      if (instruction == 5 || instruction == -1) error = 1;
    }
  }
  int code = 1;

  if (error) code = 5;

  clear_stack(&stack);

  return code;
}

/*!
    @brief Реализация вычисления выражения в постфиксной нотации
    @param queue очередь с выражением в постфиксной нотации
    @param x переменная X
    @param result переменная для записи результата
    @return код ошибки
*/
int from_postfix_to_double(Queue *queue, char *x, double *result) {
  
  Node *stack = list_create();
  int stop = 0;
  Node *copy_queue = queue->head;

  while (copy_queue != NULL && !stop) {
    char var[100] = {0};
    strcpy(var, copy_queue->data);
    stop = 0;

    if (((var[0] >= '0' && var[0] <= '9') ||
         (var[1] >= '0' && var[1] <= '9')) ||
        (var[0] == 'x' || var[1] == 'x'))
      push(&stack, var);
    else {
      char *res;
      double arr[2] = {0}, num = 0;

      if (strlen(var) == 1) {
        for (int i = 0; i < 2 && !stop; i++) {
          if (is_empty_stack(stack))
            stop = 1;
          else {
            char *value_1 = pop(&stack);
            arr[i] =
                atof((value_1[0] == 'x' || value_1[1] == 'x') ? x : value_1);

            if (value_1[1] == 'x')
              arr[i] = value_1[0] == '-' ? -arr[i] : arr[i];

            free(value_1);
          }
        }
        if (!stop)
          num = calc_two_double(arr, var);
        else
          num = arr[0];
      }

      if (strlen(var) > 1) {
        if (is_empty_stack(stack))
          stop = 1;
        else {
          char *value_1 = pop(&stack);
          arr[0] = atof((value_1[0] == 'x' || value_1[1] == 'x') ? x : value_1);

          if (value_1[1] == 'x') arr[0] = value_1[0] == '-' ? -arr[0] : arr[0];

          free(value_1);
          num = calc_func_double(arr, var);
        }
      }

      asprintf(&res, "%.9lf", num);
      push(&stack, res);
      free(res);
    }

    copy_queue = copy_queue->next;
  }
  *result = 0;
  if (!stop) {
    char *temp = pop(&stack);
    *result = atof((temp[0] == 'x' || temp[1] == 'x') ? x : temp);

    if (temp[1] == 'x') *result *= temp[0] == '-' ? -1 : 1;

    free(temp);

    if (*result == INFINITY || *result == -INFINITY || (*result != *result))
      stop = 1;
  }

  if (!is_empty_stack(stack)) stop = 1;

  clear_stack(&stack);
  return stop ? 5 : 1;
}

/*!
    @brief Берет два числп из массива и выполняет операцию
    @param arr массив из двух чисел
    @param operation операция
    @return результат
*/
double calc_two_double(double *arr, char *operation) {
  double res = 0;
  if (!strcmp(operation, "+"))
    res = arr[1] + arr[0];
  else if (!strcmp(operation, "-"))
    res = arr[1] - arr[0];
  else if (!strcmp(operation, "*"))
    res = arr[1] * arr[0];
  else if (!strcmp(operation, "/"))
    res = arr[1] / arr[0];
  else if (!strcmp(operation, "%"))
    res = fmod(arr[1], arr[0]);
  else if (!strcmp(operation, "^"))
    res = pow(arr[1], arr[0]);

  return res;
}

/*!
    @brief Берет два число из массива и выполняет операцию
    @param arr массив из двух чисел
    @param operation операция
    @return результат
*/
double calc_func_double(double *arr, char *operation) {
  double res = 0;

  if (!strcmp(operation, "sin"))
    res = sin(arr[0]);
  else if (!strcmp(operation, "cos"))
    res = cos(arr[0]);
  else if (!strcmp(operation, "tan"))
    res = tan(arr[0]);
  else if (!strcmp(operation, "asin"))
    res = asin(arr[0]);
  else if (!strcmp(operation, "acos"))
    res = acos(arr[0]);
  else if (!strcmp(operation, "atan"))
    res = atan(arr[0]);
  else if (!strcmp(operation, "log"))
    res = log10(arr[0]);
  else if (!strcmp(operation, "sqrt"))
    res = sqrt(arr[0]);
  else if (!strcmp(operation, "ln"))
    res = log(arr[0]);

  return res;
}