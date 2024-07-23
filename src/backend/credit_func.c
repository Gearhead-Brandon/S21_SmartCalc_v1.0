/*!
        @file
        @brief Исходный файл с функциями регулирования кредитного калькулятора
*/
#include "../s21_smart_calc.h"

/*!
    @brief Регулирование элементов кредитного калькулятора

        Валидация данных и вывод результата
*/
void calculus_credit_payments(GtkButton *button, calculator *calc) {
  for (int i = 9; i > 6; i--)
    gtk_grid_remove_row(GTK_GRID(calc->credit.grid), i);

  gtk_widget_set_visible(GTK_WIDGET(button), 1);

  int annuity_type = gtk_check_button_get_active(
      GTK_CHECK_BUTTON(calc->credit.check_button[0]));

  int year_type = gtk_check_button_get_active(
      GTK_CHECK_BUTTON(calc->credit.check_button[2]));

  char *amount =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->credit.entry[0]));
  char *term =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->credit.entry[1]));
  char *rate =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->credit.entry[2]));

  int error = 0;

  if (validate_credit(amount) == 0 || validity_check_dot(term) == 0 ||
      validate_credit(rate) == 0)
    error = 1;

  calc->credit.amount = atof(amount);
  calc->credit.term = atof(term);
  calc->credit.rate = atof(rate);

  if (calc->credit.amount == 0 || calc->credit.term == 0 ||
      calc->credit.rate == 0)
    error = 1;
  calc->credit.term *= (year_type == 1) ? 12 : 1;

  if (!error) {
    char *out_pay, *out_rest, *out_debt_inte;

    if (annuity_type) calculate_annuity(calc);

    if (!annuity_type) calculate_differentiated(calc, &out_pay);

    if (annuity_type) asprintf(&out_pay, "%.2lf", calc->credit.res_mon_pay);

    asprintf(&out_rest, "%.2lf", calc->credit.res_inte_rest);
    asprintf(&out_debt_inte, "%.2lf", calc->credit.res_debt_interest);

    GtkWidget *monthly_payment = gtk_label_new("Ежемесячный платеж");
    gtk_widget_add_css_class(monthly_payment, "view_credit");
    gtk_widget_add_css_class(monthly_payment, "monthly_payment");

    GtkWidget *monthly_payment_output = gtk_label_new(out_pay);
    gtk_widget_add_css_class(monthly_payment_output, "view_credit");
    gtk_widget_add_css_class(monthly_payment_output, "monthly_payment_output");

    GtkWidget *interest_charges = gtk_label_new("Начисленные проценты");
    gtk_widget_add_css_class(interest_charges, "view_credit");
    gtk_widget_add_css_class(interest_charges, "interest_charges");

    GtkWidget *interest_charges_output = gtk_label_new(out_rest);
    gtk_widget_add_css_class(interest_charges_output, "view_credit");
    gtk_widget_add_css_class(interest_charges_output, "monthly_payment_output");

    GtkWidget *debt_plus_interest = gtk_label_new("Долг + проценты");
    gtk_widget_add_css_class(debt_plus_interest, "view_credit");
    gtk_widget_add_css_class(debt_plus_interest, "debt_plus_interest");

    GtkWidget *debt_plus_interest_output = gtk_label_new(out_debt_inte);
    gtk_widget_add_css_class(debt_plus_interest_output, "view_credit");
    gtk_widget_add_css_class(debt_plus_interest_output,
                             "monthly_payment_output");

    gtk_grid_attach(GTK_GRID(calc->credit.grid), monthly_payment, 0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(calc->credit.grid), interest_charges, 0, 8, 1, 1);
    gtk_grid_attach(GTK_GRID(calc->credit.grid), debt_plus_interest, 0, 9, 1,
                    1);
    gtk_grid_attach(GTK_GRID(calc->credit.grid), monthly_payment_output, 1, 7,
                    2, 1);
    gtk_grid_attach(GTK_GRID(calc->credit.grid), interest_charges_output, 1, 8,
                    2, 1);
    gtk_grid_attach(GTK_GRID(calc->credit.grid), debt_plus_interest_output, 1,
                    9, 2, 1);

    free(out_pay);
    free(out_rest);
    free(out_debt_inte);
  } else {
    GtkWidget *error = gtk_label_new("Error");
    gtk_widget_add_css_class(error, "error_credit");
    gtk_grid_attach(GTK_GRID(calc->credit.grid), error, 1, 7, 1, 1);
  }
}