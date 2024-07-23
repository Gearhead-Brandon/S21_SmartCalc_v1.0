/*!
        @file
        @brief Исходный файл с функциями создания графика функций
*/
#include "../s21_smart_calc.h"

/*!
    @brief Валидация входных данных для графика функций
        @param str Строка
        @return Код ошибки
*/
int validate_graph_entry(char *str) {
  int size = strlen(str), code = 1;
  if (size == 0)
    code = 0;
  else {
    if (size == 1 && str[0] == '-') code = -1;

    for (int i = 0; i < size && code == 1; i++) {
      if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != ',' &&
          str[i] != '-')
        code = -1;
      if (size > 1 && str[i] == '-' && (str[i + 1] < '0' || str[i + 1] > '9'))
        code = -1;
    }
  }
  return code;
}

/*!
    @brief Отрисовка осей и сетки для графика функций
        @param cr тип контекста рисования библиотеки cairo
        @param width ширина окна
        @param height высота окна
        @param calc Структура с элементами графика
*/
void draw_grid_axes(cairo_t *cr, int width, int height, calculator *calc) {
  width = 500;
  height = 601;

  cairo_text_extents_t te;

  cairo_set_source_rgb(cr, 1, 1, 1);

  char *x_min_str =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->graph.entry_graph[0]));
  char *x_max_str =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->graph.entry_graph[1]));
  char *y_min_str =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->graph.entry_graph[2]));
  char *y_max_str =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->graph.entry_graph[3]));

  int code_1 = validate_graph_entry(x_min_str);
  int code_2 = validate_graph_entry(x_max_str);
  int code_3 = validate_graph_entry(y_min_str);
  int code_4 = validate_graph_entry(y_max_str);

  double x_min = -10, x_max = 10;
  double y_min = -10, y_max = 10;

  if ((code_1 == 0 || code_2 == 0 || code_3 == 0 || code_4 == 0) ||
      (code_1 == -1 || code_2 == -1 || code_3 == -1 || code_4 == -1)) {
    gtk_widget_set_visible(GTK_WIDGET(calc->graph.error_widget), 0);

    if (calc->graph.status > 0 &&
        (code_1 == -1 || code_2 == -1 || code_3 == -1 || code_4 == -1))
      gtk_widget_set_visible(GTK_WIDGET(calc->graph.error_widget), 1);

    x_min = -10;
    x_max = 10;

    y_min = -10;
    y_max = 10;

    gtk_entry_set_placeholder_text(GTK_ENTRY(calc->graph.entry_graph[0]),
                                   "MIN -10");
    gtk_entry_set_placeholder_text(GTK_ENTRY(calc->graph.entry_graph[1]),
                                   "MAX 10");
    gtk_entry_set_placeholder_text(GTK_ENTRY(calc->graph.entry_graph[2]),
                                   "MIN -10");
    gtk_entry_set_placeholder_text(GTK_ENTRY(calc->graph.entry_graph[3]),
                                   "MAX 10");

  } else if ((code_1 && code_2 && code_3 && code_4)) {
    gtk_widget_set_visible(GTK_WIDGET(calc->graph.error_widget), 0);
    x_min = atof(x_min_str);
    x_max = atof(x_max_str);
    y_min = atof(y_min_str);
    y_max = atof(y_max_str);

    gtk_entry_set_placeholder_text(GTK_ENTRY(calc->graph.entry_graph[0]),
                                   "MIN");
    gtk_entry_set_placeholder_text(GTK_ENTRY(calc->graph.entry_graph[1]),
                                   "MAX");
    gtk_entry_set_placeholder_text(GTK_ENTRY(calc->graph.entry_graph[2]),
                                   "MIN");
    gtk_entry_set_placeholder_text(GTK_ENTRY(calc->graph.entry_graph[3]),
                                   "MAX");
  }

  calc->graph.x_min = x_min;
  calc->graph.x_max = x_max;
  calc->graph.y_min = y_min;
  calc->graph.y_max = y_max;

  calc->graph.status++;
  double range_x = x_max - x_min;
  double range_y = y_max - y_min;

  double sum_x = x_min + x_max;
  double sum_y = y_min + y_max;

  double x_coordinates, x_ch;
  double y_coordinates, y_ch;

  /////////////////////// Y ////////////////////////

  x_coordinates = new_x(sum_x, range_x, sum_x, width);

  if (x_coordinates < 0) x_coordinates *= -1;
  cairo_move_to(cr, x_coordinates, 0);
  ;

  cairo_line_to(cr, x_coordinates, height);
  x_ch = x_coordinates;
  /////////////////////// X ////////////////////////

  y_coordinates = new_y(sum_y, range_y, sum_y, height);

  if (y_coordinates < 0) y_coordinates *= -1;

  cairo_move_to(cr, 0, y_coordinates);

  cairo_line_to(cr, width, y_coordinates);
  y_ch = y_coordinates;

  cairo_select_font_face(cr, "Georgia", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 13);

  cairo_text_extents(cr, "0", &te);
  cairo_move_to(cr, x_ch + 10, y_ch + 20);
  cairo_show_text(cr, "0");

  char *x_min_display, *x_max_display, *y_min_display, *y_max_display;

  asprintf(&x_min_display, "%.8g", x_min);
  asprintf(&x_max_display, "%.8g", x_max);
  asprintf(&y_min_display, "%.8g", y_min);
  asprintf(&y_max_display, "%.8g", y_max);

  cairo_text_extents(cr, x_min_display, &te);
  cairo_move_to(cr, 0 + 10, y_ch - 20);
  cairo_show_text(cr, x_min_display);

  cairo_text_extents(cr, x_max_display, &te);
  cairo_move_to(cr, width - 30, y_ch + 30);
  cairo_show_text(cr, x_max_display);

  cairo_text_extents(cr, y_min_display, &te);
  cairo_move_to(cr, x_ch + 10, height - 20);
  cairo_show_text(cr, y_min_display);

  cairo_text_extents(cr, y_max_display, &te);
  cairo_move_to(cr, x_ch - 40, 20);
  cairo_show_text(cr, y_max_display);

  cairo_stroke(cr);

  free(x_min_display);
  free(x_max_display);
  free(y_min_display);
  free(y_max_display);

  //////////////////////////////////////////////////////////////////

  cairo_set_source_rgb(cr, 1, 1, 1);

  cairo_move_to(cr, 1, 0);  // LEFT BORDER
  cairo_line_to(cr, 1, height);

  cairo_move_to(cr, 0, height - 1);  // BOTTOM BORDER
  cairo_line_to(cr, width, height - 1);

  cairo_set_line_width(cr, 2.2);
  cairo_stroke(cr);

  cairo_set_source_rgb(cr, 1, 1, 1);

  cairo_move_to(cr, width - 1, 0);  // RIGTH BORDER
  cairo_line_to(cr, width - 1, height);

  cairo_move_to(cr, 0, 1);  // TOP BORDER
  cairo_line_to(cr, width, 1);

  cairo_set_line_width(cr, 1.2);
  cairo_stroke(cr);
  /////////////////////////////////////////////////////////////////////////////////////////////////
  cairo_select_font_face(cr, "Georgia", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 17);

  cairo_text_extents(cr, "Y", &te);
  cairo_move_to(cr, x_ch + 10, 20);
  cairo_show_text(cr, "Y");

  cairo_text_extents(cr, "X", &te);
  cairo_move_to(cr, width - 20, y_ch - 10);
  cairo_show_text(cr, "X");

  //////////////////////////////////////////   GRID
  //////////////////////////////////////////
  double dashes[] = {
      3.0, /* ink */
      3.0, /* skip */
      3.0, /* ink */
      3.0  /* skip*/
  };

  int ndash = sizeof(dashes) / sizeof(dashes[0]);
  double offset = -50.0;

  cairo_set_dash(cr, dashes, ndash, offset);
  cairo_set_source_rgb(cr, 128, 128, 128);

  double step = (fabs(x_max) + fabs(x_min)) * 0.1, x;

  for (double i = x_min + step; i < x_max; i += step) {
    if (i == 0) continue;

    x = new_x(i, range_x, sum_x, width) * -1;
    cairo_move_to(cr, x, 0);
    cairo_line_to(cr, x, height);
  }
  double y;
  step = (fabs(y_max) + fabs(y_min)) * 0.1;
  for (double i = y_min + step; i < y_max; i += step) {
    if (i == 0) continue;

    y = new_y(i, range_y, sum_y, height) * -1;
    cairo_move_to(cr, 0, y);
    cairo_line_to(cr, width, y);
  }
  cairo_set_line_width(cr, 0.8);
  cairo_stroke(cr);

  cairo_set_dash(cr, dashes, 0, offset);
}

/*!
    @brief Преобразование координаты оси X в координаты окна
        @param x координата x
        @param range диапазон минимального и максимального значения
        @param sum сумма значений
        @param width ширина окна
*/
double new_x(double x, double range, double sum, double width) {
  return -((width * x / range) + (width / 2) * (1 + sum / range));
}

/*!
    @brief Преобразование координаты оси Y в координаты окна
        @param y координата y
        @param range диапазон минимального и максимального значения
        @param sum сумма значений
        @param height высота окна
*/
double new_y(double y, double range, double sum, double height) {
  return ((height / range) * y + -(height / 2) * (1 + sum / range));
}

/*!
    @brief Функция отрисовки графика функций
        @param area область рисования
        @param cr тип контекста рисования библиотеки cairo
        @param width ширина окна
        @param height высота окна
        @param calc Структура с вводными данными
*/
void plot(GtkDrawingArea *area, cairo_t *cr, int width, int height,
          calculator *calc) {
  const char *label = gtk_button_get_label(GTK_BUTTON(calc->button[18]));

  if (strcmp(label, "INPUT")) {
    char *x_sym = strstr(calc->input_buffer, "x");
    int have_x = x_sym == NULL ? 0 : 1;

    width = 500;
    height = 601;

    cairo_set_source_rgb(cr, 1, 1, 0);

    double range_x = calc->graph.x_max - calc->graph.x_min;
    double range_y = calc->graph.y_max - calc->graph.y_min;
    double sum_x = calc->graph.x_min + calc->graph.x_max;
    double sum_y = calc->graph.y_min + calc->graph.y_max;

    double true_x = calc->graph.x_min, y_coordinates = 0,
           var = calc->graph.y_max * 3.5, copy_coord = 0, x_coordinates = 0,
           step = 0.001, res = 0;

    Queue queue = {NULL};

    char copy_input[300] = {0};
    strcpy(copy_input, calc->input_buffer);

    for (int i = 0; copy_input[i] != '\0'; i++)
      if (copy_input[i] == '.') copy_input[i] = ',';

    int code_1, code_2,
        error = from_infix_to_postfix(copy_input, "0,5", &queue);

    if (error != 5) {
      code_1 = from_postfix_to_double(&queue, "0,5", &res);
      code_2 = from_postfix_to_double(&queue, "-0,5", &res);
      error = (code_1 == 1 || code_2 == 1) ? 1 : error;
    }

    clear_queue(&queue);

    if (!have_x && error != 5) {
      if (s21_is_inf(res) == 0 && s21_is_nan(res) == 0) {
        for (; true_x <= calc->graph.x_max; true_x += step) {
          y_coordinates = res;
          x_coordinates = new_x(true_x, range_x, sum_x, width) * -1;
          y_coordinates = new_y(y_coordinates, range_y, sum_y, height) * -1;
          cairo_line_to(cr, x_coordinates, y_coordinates);
          cairo_move_to(cr, x_coordinates, y_coordinates);
        }
      }
    } else if (have_x && error != 5) {
      int flag = 0, iter = 0;

      char copy_input[300] = {0};
      strcpy(copy_input, calc->input_buffer);
      Queue queue = {NULL};

      for (int i = 0; copy_input[i] != '\0'; i++)
        if (copy_input[i] == '.') copy_input[i] = ',';

      from_infix_to_postfix(copy_input, calc->X_value, &queue);

      for (; true_x <= calc->graph.x_max; true_x += step) {
        from_postfix_to_result(&queue, true_x, &y_coordinates);

        if (s21_is_nan(y_coordinates) || s21_is_inf(y_coordinates))
          flag = 1;
        else
          flag = 0;

        if (!flag) {
          x_coordinates = new_x(true_x, range_x, sum_x, width) * -1;

          y_coordinates = new_y(y_coordinates, range_y, sum_y, height) * -1;
          int flag2 = 0;

          if (fabs(y_coordinates - copy_coord) >= var && iter > 0) flag2 = 1;

          if (!flag2) {
            if (y_coordinates <= 600) {
              cairo_line_to(cr, x_coordinates, y_coordinates);
              cairo_move_to(cr, x_coordinates, y_coordinates);
            }
          } else
            cairo_move_to(cr, x_coordinates, y_coordinates);

          copy_coord = y_coordinates;
          flag = 0;
        }

        iter++;
      }

      clear_queue(&queue);
    }

    cairo_set_line_width(cr, 1.5);
    cairo_stroke(cr);

    gtk_widget_queue_draw(GTK_WIDGET(area));
  }
}

/*!
    @brief Реализация вычисления выражения в постфиксной нотации
    @param queue очередь с выражением в постфиксной нотации
    @param x переменная X
    @param result переменная для записи результата
    @return код ошибки

        @details Отличается от функции from_infix_to_double тем, что в
        данной функции переменная X является типом double, сделанной
        специально для отрисовки графика функции
*/
int from_postfix_to_result(Queue *queue, double x, double *result) {
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
            if (value_1[0] == 'x' || value_1[1] == 'x')
              arr[i] = x;
            else
              arr[i] = atof(value_1);

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

          if (value_1[0] == 'x' || value_1[1] == 'x')
            arr[0] = x;
          else
            arr[0] = atof(value_1);

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

    if (temp[0] == 'x' || temp[1] == 'x')
      *result = x;
    else
      *result = atof(temp);

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
    @brief Кнопка вызова функции отрисовки графика функций
        @param button Кнопка вызывающая функцию
        @param area область рисования
        @param data Структура с вводными данными
*/
void plot_button(GtkButton *button, GtkDrawingArea *area,
                 G_GNUC_UNUSED gpointer data) {
  gtk_widget_set_visible(GTK_WIDGET(button), TRUE); FALSE;
  gtk_widget_queue_draw(GTK_WIDGET(area));
}

/*!
    @brief Главная отрисовочная функция
        @param area область рисования
        @param cr тип контекста рисования библиотеки cairo
        @param width ширина окна
        @param height высота окна
        @param data Структура с вводными данными
*/
void draw_cb(GtkDrawingArea *area, cairo_t *cr, int width, int height,
             gpointer data) {
  gtk_widget_set_visible(GTK_WIDGET(area), 1);
  calculator *calc = (calculator *)data;

  draw_grid_axes(cr, width, height, calc);

  plot(area, cr, width, height, calc);
}