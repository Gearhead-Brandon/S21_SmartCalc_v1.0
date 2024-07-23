/*!
        @file
        @brief Исходный файл с функциями создания графической части главного
   калькулятора
*/
#include "../s21_smart_calc.h"

/*!
    @brief Создание кнопок и подключение к ним стилей
*/
void create_buttons(calculator *widget) {
  widget->button[0] = gtk_button_new_with_label("0");
  widget->button[1] = gtk_button_new_with_label("1");
  widget->button[2] = gtk_button_new_with_label("2");
  widget->button[3] = gtk_button_new_with_label("3");
  widget->button[4] = gtk_button_new_with_label("4");
  widget->button[5] = gtk_button_new_with_label("5");
  widget->button[6] = gtk_button_new_with_label("6");
  widget->button[7] = gtk_button_new_with_label("7");
  widget->button[8] = gtk_button_new_with_label("8");
  widget->button[9] = gtk_button_new_with_label("9");
  widget->button[10] = gtk_button_new_with_label(".");
  widget->button[11] = gtk_button_new_with_label("*");
  widget->button[12] = gtk_button_new_with_label("+");
  widget->button[13] = gtk_button_new_with_label("-");
  widget->button[14] = gtk_button_new_with_label("=");

  for (int i = 0; i <= 14; i++)
    gtk_widget_add_css_class(widget->button[i], "button_regular");

  widget->button[15] = gtk_button_new_with_label("AC");
  gtk_widget_add_css_class(widget->button[15], "button_white");

  widget->button[16] = gtk_button_new_with_label("/");

  for (int i = 11; i <= 16; i == 14 ? i += 2 : i++)
    gtk_widget_add_css_class(widget->button[i], "button_orange");

  widget->button[17] = gtk_button_new_with_label("X VALUE");
  gtk_widget_add_css_class(widget->button[17], "button_x_value");

  gtk_widget_set_name(widget->button[17], "name_button_x_val");

  widget->button[18] = gtk_button_new_with_label("INPUT");
  gtk_widget_add_css_class(widget->button[18], "button_input");

  gtk_widget_set_name(widget->button[18], "name_button_input");

  widget->button[19] = gtk_button_new_with_label("(");
  widget->button[20] = gtk_button_new_with_label(")");
  widget->button[21] = gtk_button_new_with_label("sin");
  widget->button[22] = gtk_button_new_with_label("asin");
  widget->button[23] = gtk_button_new_with_label("cos");
  widget->button[24] = gtk_button_new_with_label("acos");
  widget->button[25] = gtk_button_new_with_label("tan");
  widget->button[26] = gtk_button_new_with_label("atan");
  widget->button[27] = gtk_button_new_with_label("ln");
  widget->button[28] = gtk_button_new_with_label("log");
  widget->button[29] = gtk_button_new_with_label("plot");
  widget->button[30] = gtk_button_new_with_label("sqrt");

  for (int i = 19; i <= 30; i++)
    gtk_widget_add_css_class(widget->button[i], "button_white");

  widget->button[31] = gtk_button_new_with_label("X");
  gtk_widget_add_css_class(widget->button[31], "button_regular");

  widget->button[32] = gtk_button_new_with_label("mod");
  gtk_widget_add_css_class(widget->button[32], "button_orange");
  gtk_widget_add_css_class(widget->button[32], "button_mod");

  widget->button[33] = gtk_button_new_with_label("^");
  gtk_widget_add_css_class(widget->button[33], "button_orange");
}

/*!
    @brief Прикрепление кнопок к сетке
*/
void attach_butons_to_grid(calculator *widget) {
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[18], 1, 1, 6,
                  1);  // INPUT
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[19], 1, 2, 1, 1);  // (
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[20], 2, 2, 1, 1);  // )
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[15], 3, 2, 1,
                  1);  // AC
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[21], 1, 3, 1,
                  1);  // sin
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[22], 2, 3, 1,
                  1);  // asin
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[23], 1, 4, 1,
                  1);  // cos
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[24], 2, 4, 1,
                  1);  // acos
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[25], 1, 5, 1,
                  1);  // tan
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[26], 2, 5, 1,
                  1);  // atan
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[27], 1, 6, 1,
                  1);  // ln
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[28], 2, 6, 1,
                  1);  // log
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[29], 1, 7, 1,
                  1);  // plot
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[30], 2, 7, 1,
                  1);  // sqrt
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[31], 3, 7, 1, 1);  // X
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[32], 4, 7, 1, 1);  // %
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[33], 5, 7, 1, 1);  // ^
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[0], 3, 6, 2, 1);   // 0
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[1], 3, 5, 1, 1);   // 1
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[2], 4, 5, 1, 1);   // 2
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[3], 5, 5, 1, 1);   // 3
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[4], 3, 4, 1, 1);   // 4
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[5], 4, 4, 1, 1);   // 5
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[6], 5, 4, 1, 1);   // 6
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[7], 3, 3, 1, 1);   // 7
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[8], 4, 3, 1, 1);   // 8
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[9], 5, 3, 1, 1);   // 9
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[10], 5, 6, 1, 1);  // .
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[11], 6, 6, 1, 1);  // +
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[12], 6, 5, 1, 1);  // -
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[13], 6, 4, 1, 1);  // *
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[14], 6, 3, 1, 1);  // /
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[16], 6, 7, 1, 1);  // =
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[17], 4, 2, 3,
                  1);  // x value
}

/*!
    @brief Подключение функций к кнопкам и назначение главной отрисовочной
   функции
*/
void connect_buttons(calculator *widget) {
  for (int i = 0; i < 34; i++) {
    if (i == 29) continue;
    g_signal_connect(widget->button[i], "clicked", G_CALLBACK(calculate),
                     widget);
  }

  g_signal_connect(widget->button[29], "clicked", G_CALLBACK(plot_button),
                   widget->graph.area);

  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(widget->graph.area), draw_cb,
                                 widget, NULL);
}