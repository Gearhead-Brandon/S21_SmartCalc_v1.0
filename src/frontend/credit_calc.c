/*!
        @file
        @brief Исходный файл с функциями создания графической части кредитного
   калькулятора
*/
#include "../s21_smart_calc.h"

/*!
    @brief Создание графической части кредитного калькулятора
        @param button Кнопка вызывающая функцию
        @param calc Структура с элементами кредитного калькулятора
*/
void create_credit_calc(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  gtk_window_set_title(GTK_WINDOW(calc->window), "Credit calculator");

  GtkWidget *amount_of_credit = gtk_label_new("Сумма кредита");
  gtk_widget_add_css_class(amount_of_credit, "view_credit");
  gtk_widget_add_css_class(amount_of_credit, "view_credit_pad1");

  GtkWidget *credit_term = gtk_label_new("Срок кредита");
  gtk_widget_add_css_class(credit_term, "view_credit");
  gtk_widget_add_css_class(credit_term, "view_credit_pad2");

  GtkWidget *interest_rate = gtk_label_new("Процентная ставка");
  gtk_widget_add_css_class(interest_rate, "view_credit");
  gtk_widget_add_css_class(interest_rate, "view_credit_pad3");

  GtkWidget *monthly_payment_types = gtk_label_new("Типы ежемесячных платежей");
  gtk_widget_add_css_class(monthly_payment_types, "view_credit");
  gtk_widget_add_css_class(monthly_payment_types, "type_payment");
  /////////////////////////////////////////////////////////////////////////////////////////////
  calc->credit.check_button[0] = gtk_check_button_new_with_label("Аннуитетный");
  gtk_widget_add_css_class(calc->credit.check_button[0], "check_button_annui");
  calc->credit.check_button[1] =
      gtk_check_button_new_with_label("Дифференцированный");
  gtk_widget_add_css_class(calc->credit.check_button[1], "check_button_annui");

  gtk_check_button_set_active(GTK_CHECK_BUTTON(calc->credit.check_button[0]),
                              1);

  calc->credit.check_button[2] = gtk_check_button_new_with_label("Годы");
  gtk_widget_add_css_class(calc->credit.check_button[2], "check_button_annui");
  gtk_widget_add_css_class(calc->credit.check_button[2],
                           "check_button_annui_p");
  calc->credit.check_button[3] = gtk_check_button_new_with_label("Месяцы");
  gtk_widget_add_css_class(calc->credit.check_button[3], "check_button_annui");
  gtk_widget_add_css_class(calc->credit.check_button[2],
                           "check_button_annui_p");

  gtk_check_button_set_active(GTK_CHECK_BUTTON(calc->credit.check_button[2]),
                              1);

  gtk_check_button_set_group(GTK_CHECK_BUTTON(calc->credit.check_button[0]),
                             GTK_CHECK_BUTTON(calc->credit.check_button[1]));
  gtk_check_button_set_group(GTK_CHECK_BUTTON(calc->credit.check_button[2]),
                             GTK_CHECK_BUTTON(calc->credit.check_button[3]));
  /////////////////////////////////////////////////////////////////////////////////////////////

  calc->credit.entry[0] = gtk_entry_new();  // amount
  calc->credit.entry[1] = gtk_entry_new();  // term
  calc->credit.entry[2] = gtk_entry_new();  // rate
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->credit.entry[0]), "INPUT");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->credit.entry[1]), "INPUT");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->credit.entry[2]), "INPUT");

  /////////////////////////////////////////////////////////////////////////////////////////////
  GtkWidget *calculate_credit = gtk_button_new_with_label("Рассчитать");
  gtk_widget_add_css_class(calculate_credit, "calculate_credit");

  calc->credit.grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(calc->credit.grid), 5);
  gtk_widget_add_css_class(GTK_WIDGET(calc->credit.grid), "grid_credit");

  gtk_grid_attach(GTK_GRID(calc->credit.grid), amount_of_credit, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->credit.grid), credit_term, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->credit.grid), interest_rate, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->credit.grid), monthly_payment_types, 0, 4, 1,
                  1);

  gtk_grid_attach(GTK_GRID(calc->credit.grid), calc->credit.entry[0], 1, 0, 2,
                  1);

  gtk_grid_attach(GTK_GRID(calc->credit.grid), calc->credit.check_button[2], 1,
                  2, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->credit.grid), calc->credit.check_button[3], 2,
                  2, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->credit.grid), calc->credit.entry[1], 1, 1, 2,
                  1);
  gtk_grid_attach(GTK_GRID(calc->credit.grid), calc->credit.entry[2], 1, 3, 2,
                  1);

  gtk_grid_attach(GTK_GRID(calc->credit.grid), calc->credit.check_button[0], 1,
                  4, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->credit.grid), calc->credit.check_button[1], 1,
                  5, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->credit.grid), calculate_credit, 1, 6, 1, 1);

  gtk_window_set_child(GTK_WINDOW(calc->window), calc->credit.grid);
  gtk_widget_set_size_request(calc->window, 200, 200);

  g_signal_connect(calculate_credit, "clicked",
                   G_CALLBACK(calculus_credit_payments), calc);
}