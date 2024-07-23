/*!
        @file
        @brief Исходный файл с функциями регулирования депозитного калькулятора
*/
#include "../s21_smart_calc.h"

/*!
    @brief Регулирование элементов депозитного калькулятора

        Валидация данных и вывод результата
*/
void calculus_deposit_payments(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  for (int i = 13; i > 9; i--)
    gtk_grid_remove_row(GTK_GRID(calc->deposit.grid), i);
  gtk_widget_set_visible(calc->deposit.error_widget, 0);

  calc->deposit.all_term_type =
      gtk_drop_down_get_selected(calc->deposit.drop_down_term);
  calc->deposit.rate_type =
      gtk_combo_box_get_active(GTK_COMBO_BOX(calc->deposit.drop_down_interest));
  calc->deposit.periodicity_type = gtk_combo_box_get_active(
      GTK_COMBO_BOX(calc->deposit.drop_down_periodity));
  calc->deposit.capytalization_type = gtk_check_button_get_active(
      GTK_CHECK_BUTTON(calc->deposit.check_button_cap));
  calc->deposit.taxes_type = gtk_check_button_get_active(
      GTK_CHECK_BUTTON(calc->deposit.check_button_taxes));

  int error = 0;
  char *amount =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[0]));
  char *all_term =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[1]));
  char *start_date =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[2]));
  char *rate =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[3]));

  if (!error &&
      (validate_credit(amount) == 0 || validity_check_dot(all_term) == 0 ||
       validity_date(start_date) == 0))
    error = 1;

  if (!error && validate_credit(rate) == 0 &&
      calc->deposit.rate_type == фиксированная)
    error = 1;

  if (!error && calc->deposit.rate_type > 0 && validate_rate_deposit(rate) == 0)
    error = 1;

  calc->deposit.amount = atof(amount);
  calc->deposit.term = atof(all_term);
  strcpy(calc->deposit.start_date, start_date);
  calc->deposit.rate = atof(rate);

  if (!error && (calc->deposit.amount == 0.0 || calc->deposit.term == 0.0 ||
                 ((calc->deposit.rate == 0.0 || calc->deposit.rate > 999) &&
                  calc->deposit.rate_type == фиксированная)))
    error = 1;

  if (!error && calc->deposit.taxes_type) {
    char *taxe =
        (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[9]));
    if (validate_credit(taxe) == 0)
      error = 1;
    else
      calc->deposit.taxe = atof(taxe);
    calc->deposit.taxe /= 100.0;
    calc->deposit.taxe_free_amount = calc->deposit.amount * calc->deposit.taxe;
  }

  if (!error && (calc->deposit.rate_type == от_суммы ||
                 calc->deposit.rate_type == от_срока))
    error = array_rate_is_empty(calc);

  if (!error) {
    calculate_deposit(calc);
    char *out_amount, *out_inte_charges, *out_taxes;

    asprintf(&out_inte_charges, "%.2lf", calc->deposit.res_inte_charges);
    asprintf(&out_amount, "%.2lf", calc->deposit.res_amount);
    asprintf(&out_taxes, "%.2lf", calc->deposit.res_taxes);

    GtkWidget *inte_charges_l = gtk_label_new("Начисленные проценты");
    gtk_widget_add_css_class(inte_charges_l, "output_result_deposit");
    gtk_widget_add_css_class(inte_charges_l, "output_deposit_pad_1");

    GtkWidget *amount_with_percent_l = gtk_label_new("Сумма вклада");
    gtk_widget_add_css_class(amount_with_percent_l, "output_result_deposit");
    gtk_widget_add_css_class(amount_with_percent_l, "output_deposit_pad_2");

    GtkWidget *taxe_l = gtk_label_new("Налог");
    gtk_widget_add_css_class(taxe_l, "output_result_deposit");
    gtk_widget_add_css_class(taxe_l, "output_deposit_pad_3");

    GtkWidget *interest_charges_res = gtk_label_new(out_inte_charges);
    gtk_widget_add_css_class(interest_charges_res, "view_credit");
    gtk_widget_add_css_class(interest_charges_res, "monthly_payment_output");

    GtkWidget *amount_res = gtk_label_new(out_amount);
    gtk_widget_add_css_class(amount_res, "view_credit");
    gtk_widget_add_css_class(amount_res, "monthly_payment_output");

    GtkWidget *taxes_res = gtk_label_new(out_taxes);
    gtk_widget_add_css_class(taxes_res, "view_credit");
    gtk_widget_add_css_class(taxes_res, "monthly_payment_output");

    GtkWidget *VOID = gtk_label_new(" ");

    gtk_grid_attach(GTK_GRID(calc->deposit.grid), inte_charges_l, 0, 10, 1, 1);
    gtk_grid_attach(GTK_GRID(calc->deposit.grid), interest_charges_res, 1, 10,
                    2, 1);

    gtk_grid_attach(GTK_GRID(calc->deposit.grid), amount_with_percent_l, 0, 11,
                    1, 1);
    gtk_grid_attach(GTK_GRID(calc->deposit.grid), amount_res, 1, 11, 2, 1);

    gtk_grid_attach(GTK_GRID(calc->deposit.grid), taxe_l, 0, 12, 1, 1);
    gtk_grid_attach(GTK_GRID(calc->deposit.grid), taxes_res, 1, 12, 2, 1);

    gtk_grid_attach(GTK_GRID(calc->deposit.grid), VOID, 0, 13, 2, 1);

    free(out_inte_charges);
    free(out_amount);
    free(out_taxes);
    reduction_initial_state(calc);
  } else
    gtk_widget_set_visible(calc->deposit.error_widget, 1);
}

/*!
    @brief Проверка на пустоту матрицв ставок
*/
int array_rate_is_empty(calculator *calc) {
  return calc->deposit.mat_rate[0][0] == 1.0 ? 0 : 1;
}