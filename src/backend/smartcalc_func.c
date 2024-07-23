/*!
        @file
        @brief Исходный файл с функциями регулирования обычного калькулятора
*/
#include "../s21_smart_calc.h"

/*!
    @brief Регулирование элементов обычного калькулятора

        Валидация поступающих данных и вывод результата
*/
void calculate(GtkButton *button, calculator *calc) {
  gchar *text = (char *)gtk_button_get_label(button);
  int write = 1, error = 0;
  char *button_name = (char *)gtk_widget_get_name(GTK_WIDGET(button));

  if (text[0] == 'X') text[0] = 'x';

  if (!strcmp(button_name, "name_button_x_val")) {  // button x vakue
    write = 0;
    memset(calc->X_value, 0, 20);
    calc->f_input_x = 1;
  }

  if (!strcmp(button_name, "name_button_input")) {  // button input
    write = 0;
    calc->f_input_x = 0;
  }

  if (text[0] == 'A' && write)  // AC
    erase_expression(calc, &write);

  if (text[0] == '=' && write) {
    if (strcmp(gtk_button_get_label(GTK_BUTTON(calc->button[18])), "INPUT") !=
        0)
      solve_expression(calc, &error);
    write = 0;
  }

  char last_char_input =
      calc->input_buffer[strlen(calc->input_buffer) == 0
                             ? 0
                             : strlen(calc->input_buffer) - 1];

  if (((text[0] >= '0' && text[0] <= '9') || text[0] == '.' ||
       text[0] == '-') &&
      calc->f_input_x && write)  // X INPUT
    input_X(calc, text);

  int dont_check = 0;

  if ((text[0] >= 'a' && text[0] <= 'z') && text[0] != 'x' &&
      !calc->f_input_x && write)  // FUNCTION INPUT
    function_input(calc, text, last_char_input);
  else if ((!calc->is_arithmetic || symbol_not_arithmetic(text[0])) &&
           !calc->f_input_x && write)  // NUMBERS AND OPERATIONS INPUT
    entering_numbers_and_operations(calc, text, &dont_check, last_char_input);

  calc->is_arithmetic = symbol_arithmetic(text[0]);

  if (strlen(calc->input_buffer) > 256) {
    if (error == 0) write = 0;
    error = error == 0 ? 1 : 0;
  }

  if (write) add_to_buffer(calc, text, &dont_check);

  if (error) error_output(calc);
}

/*!
    @brief Ввод функций
        @param calc Структура
        @param text Вводимая функция
        @param last_char_input Последний символ
*/
void function_input(calculator *calc, char *text, char last_char_input) {
  int input = 1;

  if ((text[0] != 'm' &&
       calc->input_buffer[0] == 0) /*|| symbol_arithmetic(last_char_input)*/
      || last_char_input == '(')
    strcat(calc->input_buffer, text);
  else {
    last_char_input == '.' && text[0] != 'm' ? strcat(calc->input_buffer, "0")
                                             : NULL;
    strcat(calc->input_buffer,
           text[0] != 'm' && !symbol_arithmetic(last_char_input) ? "*" : "");
    text[0] == 'm' ? strcat(calc->input_buffer, " ") : NULL;

    if ((text[0] == 'm' && last_char_input == 0))
      input = 0;
    else
      strcat(calc->input_buffer, text);
  }
  strcat(calc->input_buffer, (input && text[0] != 'm') ? "(" : " ");
}

/*!
    @brief Ввод чисел и арифметических операций
        @param calc Структура
        @param text Вводимые данные
        @param dont_check Флаг проверки
        @param last_char_input Последний символ
*/
void entering_numbers_and_operations(calculator *calc, char *text,
                                     int *dont_check, char last_char_input) {
  int input = 1;

  if ((last_char_input == 'x' || last_char_input == ')') &&
      symbol_not_arithmetic(text[0]) && text[0] != 'x' && text[0] != ')')
    strcat(calc->input_buffer, "*");

  if (text[0] == 'x' && symbol_not_arithmetic(last_char_input) &&
      last_char_input != '(' && last_char_input != '.')
    strcat(calc->input_buffer, "*");

  if (text[0] == '(' && (last_char_input >= '0' && last_char_input <= '9'))
    strcat(calc->input_buffer, "*");

  if (text[0] == '.' &&
      (last_char_input < '0' || last_char_input > '9')) {  // +/()/f .
    strcat(calc->input_buffer, "0");
    last_char_input = '0';
  }

  if (last_char_input == '.' && !(text[0] >= '0' && text[0] <= '9') &&
      !symbol_arithmetic(text[0]) && text[0] != ')')
    strcat(calc->input_buffer, "0*");

  if ((text[0] == ')' || symbol_arithmetic(text[0])) && last_char_input == '.')
    strcat(calc->input_buffer, "0");

  if (is_arithmetic(text[0]) && !(text[0] == '+' || text[0] == '-') &&
      calc->input_buffer[0] == 0 && text[0] != '(') {
    input = 0;
    *dont_check = 1;
  }

  if (symbol_arithmetic(text[0]) && last_char_input == ' ') input = 0;

  input == 1 ? strcat(calc->input_buffer, text) : NULL;
}

/*!
    @brief Добавление к математическому выражению
        @param calc Структура
        @param text Вводимые данные
*/
void add_to_buffer(calculator *calc, char *text, int *dont_check) {
  if (!dont_check) calc->is_arithmetic = symbol_arithmetic(text[0]);

  if (!calc->f_input_x)
    gtk_button_set_label(GTK_BUTTON(calc->button[18]),
                         calc->input_buffer);  // INPUT FIELD
  else
    gtk_button_set_label(GTK_BUTTON(calc->button[17]),
                         calc->X_value);  // X FIELD
}

/*!
    @brief Ввод значения X
        @param calc Структура
        @param text Вводимые данные
*/
void input_X(calculator *calc, char *text) {
  int input = 1;

  if ((text[0] == '.' && calc->last_x == '.')) input = 0;

  if (text[0] == '.' && !((calc->last_x >= '0' && calc->last_x <= '9')) &&
      calc->last_x != 0 && calc->last_x != '.')
    strcat(calc->X_value, "0");

  if (text[0] == '.' && calc->last_x == 0) strcat(calc->X_value, "0");

  if (strlen(calc->X_value) < 30)
    input == 1 ? strcat(calc->X_value, text) : NULL;

  calc->last_x = text[0];
}

/*!
    @brief Решение выражения
        @param calc Структура
        @param error Флаг ошибки
*/
void solve_expression(calculator *calc, int *error) {
  double res = 0;

  if (calc->input_buffer[0] == 0) strcpy(calc->input_buffer, "0.0");

  strcpy(calc->X_value,
         (!strcmp(calc->X_value, "X VALUE") ? "0.0" : calc->X_value));

  Queue queue = {NULL};
  int size = strlen(calc->input_buffer);
  int size_x = strlen(calc->X_value);

  for (int i = 0; i < size_x; i++)
    if (calc->X_value[i] == '.') calc->X_value[i] = ',';

  for (int i = 0; i < size; i++)
    if (calc->input_buffer[i] == '.') calc->input_buffer[i] = ',';

  int code = from_infix_to_postfix(calc->input_buffer, calc->X_value, &queue);
  if (code != 5) code = from_postfix_to_double(&queue, calc->X_value, &res);

  clear_queue(&queue);
  if (code == 5) *error = 1;
  char *output_result;
  if (res != 0)
    asprintf(&output_result, "%.16lg", res);
  else
    asprintf(&output_result, "0.");

  calculator_init(calc);
  strcpy(calc->input_buffer, output_result);

  if (strlen(output_result) <= 256 && !(*error)) {
    from_comma_to_dot(output_result);
    gtk_button_set_label(GTK_BUTTON(calc->button[18]), output_result);
  } else
    *error = 1;

  free(output_result);
}

/*!
    @brief Обнуление выражения
        @param calc Структура
        @param write Флаг записи
*/
void erase_expression(calculator *calc, int *write) {
  memset(calc->input_buffer, 0, 256);
  memset(calc->X_value, 0, 20);
  gtk_button_set_label(GTK_BUTTON(calc->button[18]), "INPUT");
  gtk_button_set_label(GTK_BUTTON(calc->button[17]), "X VALUE");
  calc->f_input_x = 0;
  calc->is_arithmetic = 0;
  calc->last_x = 0;
  *write = 0;
}

/*!
    @brief Проверка на арифметические операции
        @param str Символ
*/
int symbol_arithmetic(char str) {
  return str == '+' || str == '-' || str == '/' || str == '*' || str == '^' ||
         str == '%';
}

/*!
    @brief Проверка на не арифметический символ
        @param str Символ
*/
int symbol_not_arithmetic(char str) {
  return (str >= '0' && str <= '9') || (str >= 'a' && str <= 'z') ||
         (str == '(' || str == ')') || str == 'X' || str == '.';
}

/*!
    @brief Замена точек на запятые
        @param str Строка
*/
void from_comma_to_dot(char *str) {
  int size = strlen(str);
  for (int i = 0; i < size; i++)
    if (str[i] == ',') str[i] = '.';
}

/*!
    @brief Ввывод ошибки
*/
void error_output(calculator *calc) {
  memset(calc->input_buffer, 0, 256);
  memset(calc->X_value, 0, 20);
  gtk_window_set_default_size(GTK_WINDOW(calc->window), 100, 100);
  gtk_button_set_label(GTK_BUTTON(calc->button[18]), "ERROR");
  gtk_button_set_label(GTK_BUTTON(calc->button[17]), "X VALUE");
}