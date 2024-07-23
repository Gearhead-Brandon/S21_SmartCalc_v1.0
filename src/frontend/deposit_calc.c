/*!
        @file
        @brief Исходный файл с функциями создания графической части депозитного
   калькулятора
*/
#include "../s21_smart_calc.h"

/*!
    @brief Создание графической части депозитного калькулятора
*/
void create_deposit_calc(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  gtk_window_set_title(GTK_WINDOW(calc->window), "Deposit calculator");
  GtkWidget *scr = gtk_scrolled_window_new();
  gtk_window_set_child(GTK_WINDOW(calc->window), scr);

  GtkWidget *black_label1 = gtk_label_new("");

  GtkWidget *amount_of_deposit = gtk_label_new("Сумма вклада");
  gtk_widget_add_css_class(amount_of_deposit, "view_deposit");
  gtk_widget_add_css_class(amount_of_deposit, "view_deposit_pad1");

  GtkWidget *placement_period = gtk_label_new("Срок размещения");
  gtk_widget_add_css_class(placement_period, "view_deposit");

  GtkWidget *start_of_term = gtk_label_new("Начало срока");
  gtk_widget_add_css_class(start_of_term, "view_deposit");
  gtk_widget_add_css_class(start_of_term, "view_deposit_pad3");

  GtkWidget *interest_rate = gtk_label_new("Процентная ставка");
  gtk_widget_add_css_class(interest_rate, "view_deposit");
  gtk_widget_add_css_class(interest_rate, "view_deposit_pad4");

  GtkWidget *replenishment = gtk_label_new("Пополнения");
  gtk_widget_add_css_class(replenishment, "view_deposit");
  gtk_widget_add_css_class(replenishment, "view_deposit_pad5");

  calc->deposit.periodicity_label = gtk_label_new("Периодичность выплат");
  gtk_widget_add_css_class(calc->deposit.periodicity_label, "periodicity_view");

  calc->deposit.add_rate = gtk_button_new_with_label("Add");
  gtk_widget_add_css_class(calc->deposit.add_rate, "button_add_rate");
  g_signal_connect(calc->deposit.add_rate, "clicked",
                   G_CALLBACK(add_rate_button), calc);

  calc->deposit.remove_rate = gtk_button_new_with_label("Remove");
  gtk_widget_add_css_class(calc->deposit.remove_rate, "button_rem_rate");
  g_signal_connect(calc->deposit.remove_rate, "clicked",
                   G_CALLBACK(rem_rate_button), calc);

  GtkWidget *add_repl = gtk_button_new_with_label("Add");
  gtk_widget_add_css_class(add_repl, "button_add_rate");
  g_signal_connect(add_repl, "clicked", G_CALLBACK(add_repl_button), calc);

  GtkWidget *rem_repl = gtk_button_new_with_label("Remove");
  gtk_widget_add_css_class(rem_repl, "button_rem_rate");
  g_signal_connect(rem_repl, "clicked", G_CALLBACK(rem_repl_button), calc);

  GtkWidget *cut = gtk_label_new("Снятия");
  gtk_widget_add_css_class(cut, "view_deposit");
  gtk_widget_add_css_class(cut, "view_deposit_pad6");

  GtkWidget *add_cut = gtk_button_new_with_label("Add");
  gtk_widget_add_css_class(add_cut, "button_add_rate");
  g_signal_connect(add_cut, "clicked", G_CALLBACK(add_cut_button), calc);

  GtkWidget *rem_cut = gtk_button_new_with_label("Remove");
  gtk_widget_add_css_class(rem_cut, "button_rem_rate");
  g_signal_connect(rem_cut, "clicked", G_CALLBACK(rem_cut_button), calc);

  GtkWidget *solve = gtk_button_new_with_label("Рассчитать");
  gtk_widget_add_css_class(solve, "button_solve");

  calc->deposit.show_list_rate = gtk_button_new_with_label("Show");
  gtk_widget_add_css_class(calc->deposit.show_list_rate, "show_list_rate");
  g_signal_connect(calc->deposit.show_list_rate, "clicked",
                   G_CALLBACK(show_list_rate), calc);

  GtkWidget *show_list_replehishment = gtk_button_new_with_label("Show");
  gtk_widget_add_css_class(show_list_replehishment, "show_list_rate");
  g_signal_connect(show_list_replehishment, "clicked",
                   G_CALLBACK(show_list_repl), calc);

  GtkWidget *show_list_cut = gtk_button_new_with_label("Show");
  gtk_widget_add_css_class(show_list_cut, "show_list_rate");
  g_signal_connect(show_list_cut, "clicked", G_CALLBACK(show_list_cuts), calc);

  calc->deposit.error_widget = gtk_label_new("Error");
  gtk_widget_add_css_class(calc->deposit.error_widget, "error_deposit");

  ///////////////////////////////////////////////////////////////////////////////////////////////
  char *array[4] = {"дней", "месяцев", "лет"};
  calc->deposit.drop_down_term =
      (GtkDropDown *)gtk_drop_down_new_from_strings((const char *const *)array);
  gtk_widget_add_css_class(GTK_WIDGET(calc->deposit.drop_down_term),
                           "drop_down_period");
  gtk_widget_set_size_request(GTK_WIDGET(calc->deposit.drop_down_term), 180, 1);

  char *array2[7] = {"Разовое",       "Раз в месяц",   "Раз в 2 месяца",
                     "Раз в квартал", "Раз в полгода", "Раз в год"};
  calc->deposit.drop_down_replenishment =
      (GtkDropDown *)gtk_drop_down_new_from_strings(
          (const char *const *)array2);
  calc->deposit.drop_down_cut = (GtkDropDown *)gtk_drop_down_new_from_strings(
      (const char *const *)array2);

  calc->deposit.drop_down_interest = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_interest), "Фиксированная");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_interest), "Зависит от суммы");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_interest), "Зависит от срока");
  gtk_combo_box_set_active(GTK_COMBO_BOX(calc->deposit.drop_down_interest), 0);
  g_signal_connect(calc->deposit.drop_down_interest, "changed",
                   G_CALLBACK(toggled_interest_deposit), calc);

  calc->deposit.drop_down_periodity = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), "Каждый день");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), "каждую неделю");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), "раз в месяц");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), "раз в квартал");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), "раз в полгода");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), "раз в год");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), "в конце срока");
  gtk_combo_box_set_active(GTK_COMBO_BOX(calc->deposit.drop_down_periodity), 0);
  /////////////////////////////////////////////////////////////////////////////////////////////////
  calc->deposit.check_button_cap =
      gtk_check_button_new_with_label("Капитализация процентов");
  gtk_widget_add_css_class(calc->deposit.check_button_cap, "check_button_cap");
  g_signal_connect(calc->deposit.check_button_cap, "toggled",
                   G_CALLBACK(toggled_periodicity_deposit), calc);

  calc->deposit.check_button_taxes = gtk_check_button_new_with_label("Налог");
  gtk_widget_add_css_class(calc->deposit.check_button_taxes,
                           "check_button_cap");
  g_signal_connect(calc->deposit.check_button_taxes, "toggled",
                   G_CALLBACK(toggled_taxes_deposit), calc);

  /////////////////////////////////////////////////////////////////////////////////////////////////

  calc->deposit.entry[0] = gtk_entry_new();  // Сумма вклада
  calc->deposit.entry[1] = gtk_entry_new();  // Срок размещения
  calc->deposit.entry[2] = gtk_entry_new();  // Начало срока m/d/
  calc->deposit.entry[3] = gtk_entry_new();  // Ставка
  calc->deposit.entry[8] = gtk_entry_new();  // сумма ставки

  calc->deposit.entry[4] = gtk_entry_new();  // дата пополнения
  calc->deposit.entry[5] = gtk_entry_new();  // сумма пополнения
  calc->deposit.entry[6] = gtk_entry_new();  // дата снятия
  calc->deposit.entry[7] = gtk_entry_new();  // сумма снятия
  calc->deposit.entry[9] = gtk_entry_new();  // налог
  for (int i = 3; i < 10; i++)
    gtk_widget_add_css_class(GTK_WIDGET(calc->deposit.entry[i]),
                             "entry_deposit_interest_amount");

  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[0]), "Input...");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[1]), "Input...");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[2]),
                                 "mm/dd/yyyy");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[3]),
                                 "Input...%");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[8]), "Сумма");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[4]),
                                 "mm/dd/yyyy");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[5]), "Сумма");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[6]),
                                 "mm/dd/yyyy");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[7]), "Сумма");
  gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[9]), "Input...");

  /////////////////////////////////////////////////////////////////////////////////////////////////

  calc->deposit.grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(calc->deposit.grid), 10);
  gtk_widget_add_css_class(GTK_WIDGET(calc->deposit.grid), "grid_deposit");

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), amount_of_deposit, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), interest_rate, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), placement_period, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), start_of_term, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.add_rate, 4, 3, 1,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.remove_rate, 5, 3,
                  1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), black_label1, 0, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.periodicity_label,
                  0, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), replenishment, 0, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), cut, 0, 7, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.show_list_rate, 6,
                  3, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), show_list_replehishment, 6, 6,
                  1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), show_list_cut, 6, 7, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), add_repl, 4, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), rem_repl, 5, 6, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), add_cut, 4, 7, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), rem_cut, 5, 7, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), solve, 1, 9, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.check_button_cap,
                  1, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid),
                  calc->deposit.check_button_taxes, 1, 8, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[0], 1, 0, 2,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[1], 1, 1, 1,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[2], 1, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[3], 2, 3, 1,
                  1);  // rate
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[8], 3, 3, 1,
                  1);  // rate 23

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[4], 2, 6, 1,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[5], 3, 6, 1,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[6], 2, 7, 1,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[7], 3, 7, 1,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.entry[9], 2, 8, 1,
                  1);

  gtk_grid_attach(GTK_GRID(calc->deposit.grid),
                  GTK_WIDGET(calc->deposit.drop_down_term), 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid),
                  GTK_WIDGET(calc->deposit.drop_down_interest), 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid),
                  calc->deposit.drop_down_periodity, 1, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid),
                  GTK_WIDGET(calc->deposit.drop_down_replenishment), 1, 6, 1,
                  1);
  gtk_grid_attach(GTK_GRID(calc->deposit.grid),
                  GTK_WIDGET(calc->deposit.drop_down_cut), 1, 7, 1, 1);

  gtk_grid_attach(GTK_GRID(calc->deposit.grid), calc->deposit.error_widget, 2,
                  9, 1, 1);

  g_signal_connect(solve, "clicked", G_CALLBACK(calculus_deposit_payments),
                   calc);
  gtk_widget_set_size_request(calc->window, 200, 200);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  gtk_widget_set_visible(calc->deposit.entry[8], 0);
  gtk_widget_set_visible(calc->deposit.entry[9], 0);
  gtk_widget_set_visible(calc->deposit.add_rate, 0);
  gtk_widget_set_visible(calc->deposit.remove_rate, 0);
  gtk_widget_set_visible(calc->deposit.show_list_rate, 0);
  gtk_widget_set_visible(calc->deposit.error_widget, 0);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), calc->deposit.grid);
}

/*!
    @brief Смена названия виджета периодичности от кнопки капитализации
*/
void toggled_periodicity_deposit(GtkWidget *check_button, calculator *calc) {
  int active = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button));
  if (active) {
    gtk_label_set_label(GTK_LABEL(calc->deposit.periodicity_label),
                        "Перидичность капитализации");
    gtk_widget_remove_css_class(GTK_WIDGET(calc->deposit.periodicity_label),
                                "view_deposit");
    gtk_widget_add_css_class(GTK_WIDGET(calc->deposit.periodicity_label),
                             "peroidicity_cap");
    gtk_combo_box_text_remove(
        GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), 6);
  } else {
    gtk_label_set_label(GTK_LABEL(calc->deposit.periodicity_label),
                        "Перидичность выплат");
    gtk_widget_remove_css_class(GTK_WIDGET(calc->deposit.periodicity_label),
                                "peroidicity_cap");
    gtk_widget_add_css_class(GTK_WIDGET(calc->deposit.periodicity_label),
                             "periodicity_view");
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(calc->deposit.drop_down_periodity), "в конце срока");
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(calc->deposit.drop_down_periodity), 0);
}

/*!
    @brief Смена отображения строчки ввода процента от кнопки типа ставки
*/
void toggled_interest_deposit(GtkWidget *check_button, calculator *calc) {
  int active = gtk_combo_box_get_active(GTK_COMBO_BOX(check_button));
  if (active < 1) {
    gtk_widget_set_visible(calc->deposit.entry[8], 0);
    gtk_widget_set_visible(calc->deposit.add_rate, 0);
    gtk_widget_set_visible(calc->deposit.remove_rate, 0);
    gtk_widget_set_visible(calc->deposit.show_list_rate, 0);
  } else {
    if (active == 1)
      gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[8]),
                                     "Сумма");
    else
      gtk_entry_set_placeholder_text(GTK_ENTRY(calc->deposit.entry[8]),
                                     "Номер дня");

    gtk_widget_set_visible(calc->deposit.entry[8], 1);
    gtk_widget_set_visible(calc->deposit.add_rate, 1);
    gtk_widget_set_visible(calc->deposit.remove_rate, 1);
    gtk_widget_set_visible(calc->deposit.show_list_rate, 1);
  }
  init_matrix(10, 3, calc->deposit.mat_rate);
}

/*!
    @brief Отображение поля ввода процента при нажатии на кнопку налога
*/
void toggled_taxes_deposit(GtkWidget *check_button, calculator *calc) {
  int active = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button));
  if (!active) {
    gtk_widget_set_visible(calc->deposit.entry[9], 0);
  } else
    gtk_widget_set_visible(calc->deposit.entry[9], 1);
}

/*!
    @brief Добавления процентной ставки и условий ее активации
*/
void add_rate_button(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  char *entry3 =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[3]));
  char *entry8 =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[8]));

  if (validate_rate_deposit(entry3) && validate_rate_deposit(entry8)) {
    double amount = atof(entry8);
    double rate = atof(entry3);
    for (int i = 0, flag = 1; i < ROWS && flag; i++) {
      if (calc->deposit.mat_rate[i][0] == -1) {
        calc->deposit.mat_rate[i][0] = 1;
        calc->deposit.mat_rate[i][1] = amount;
        calc->deposit.mat_rate[i][2] = rate;
        flag = 0;
      }
    }
  }
}

/*!
    @brief Удаление последней добавленной процентной ставки
*/
void rem_rate_button(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  int stop = 0;
  for (int i = 9; i >= 0 && !stop; i--) {
    if (calc->deposit.mat_rate[i][0] == 1) {
      calc->deposit.mat_rate[i][0] = -1;
      calc->deposit.mat_rate[i][1] = 0;
      calc->deposit.mat_rate[i][2] = 0;
      stop = 1;
    }
  }
}

/*!
    @brief Разбиение даты на месяц, день и год
        @param src Строка с датой
        @param month Месяц
        @param day День
        @param year Год
*/
void load_date_from_char(char *src, int *month, int *day, int *year) {
  char copy_src[12] = {0};
  strcpy(copy_src, src);
  char *str = strtok(copy_src, "/");
  int num = atoi(str);
  *month = num;

  str = strtok(NULL, "/");
  num = atoi(str);
  *day = num;

  str = strtok(NULL, "/");
  num = atoi(str);
  *year = num;
}

/*!
    @brief Добавления пополнения
*/
void add_repl_button(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  int status =
      gtk_drop_down_get_selected(calc->deposit.drop_down_replenishment);
  char *entry4 =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[4]));
  char *entry5 =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[5]));

  if (validity_date(entry4) && validate_rate_deposit(entry5)) {
    int month, day, year;
    load_date_from_char(entry4, &month, &day, &year);
    double amount = atof(entry5);

    for (int i = 0, flag = 1; i < ROWS && flag; i++) {
      if (calc->deposit.mat_repl[i][0] == -1) {
        calc->deposit.mat_repl[i][0] = status;
        calc->deposit.mat_repl[i][1] = month;
        calc->deposit.mat_repl[i][2] = day;
        calc->deposit.mat_repl[i][3] = year;
        calc->deposit.mat_repl[i][4] = amount;
        calc->deposit.mat_repl[i][5] = -1;  // counter -1.0
        calc->deposit.mat_repl[i][6] = 0;   // increase point
        flag = 0;
      }
    }
  }
}

/*!
    @brief Удаление последнего добавленного пополнения
*/
void rem_repl_button(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  int stop = 0, i = 9;
  for (; i >= 0 && !stop; i--) {
    if (calc->deposit.mat_repl[i][0] >= 0) {
      calc->deposit.mat_repl[i][0] = -1;
      calc->deposit.mat_repl[i][1] = 0;
      calc->deposit.mat_repl[i][2] = 0;
      calc->deposit.mat_repl[i][3] = 0;
      calc->deposit.mat_repl[i][4] = 0;
      calc->deposit.mat_repl[i][5] = -1;
      calc->deposit.mat_repl[i][6] = 0;
      stop = 1;
    }
  }
}

/*!
    @brief Добавления снятий
*/
void add_cut_button(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  int status = gtk_drop_down_get_selected(calc->deposit.drop_down_cut);
  char *entry4 =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[6]));
  char *entry5 =
      (char *)gtk_editable_get_text(GTK_EDITABLE(calc->deposit.entry[7]));

  if (validity_date(entry4) && validate_rate_deposit(entry5)) {
    int month, day, year;
    load_date_from_char(entry4, &month, &day, &year);
    double amount = atof(entry5);

    for (int i = 0, flag = 1; i < ROWS && flag; i++) {
      if (calc->deposit.mat_cut[i][0] == -1) {
        calc->deposit.mat_cut[i][0] = status;
        calc->deposit.mat_cut[i][1] = month;
        calc->deposit.mat_cut[i][2] = day;
        calc->deposit.mat_cut[i][3] = year;
        calc->deposit.mat_cut[i][4] = amount;
        calc->deposit.mat_cut[i][5] = -1;  // counter -1.0
        calc->deposit.mat_cut[i][6] = 0;   // increase point
        flag = 0;
      }
    }
  }
}

/*!
    @brief Удаление последнего добавленного снятия
*/
void rem_cut_button(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  int stop = 0, i = 9;
  for (; i >= 0 && !stop; i--) {
    if (calc->deposit.mat_cut[i][0] >= 0) {
      calc->deposit.mat_cut[i][0] = -1;
      calc->deposit.mat_cut[i][1] = 0;
      calc->deposit.mat_cut[i][2] = 0;
      calc->deposit.mat_cut[i][3] = 0;
      calc->deposit.mat_cut[i][4] = 0;
      calc->deposit.mat_cut[i][5] = -1;
      calc->deposit.mat_cut[i][6] = 0;
      stop = 1;
    }
  }
}

void setup_cb(G_GNUC_UNUSED GtkSignalListItemFactory *self,
              GtkListItem *listitem, G_GNUC_UNUSED gpointer user_data) {
  GtkWidget *lb = gtk_label_new(NULL);
  gtk_list_item_set_child(listitem, lb);
  /* Because gtk_list_item_set_child sunk the floating reference of lb,
   * releasing (unref) isn't necessary for lb. */
}

void bind_cb(G_GNUC_UNUSED GtkSignalListItemFactory *self,
             GtkListItem *listitem, G_GNUC_UNUSED gpointer user_data) {
  GtkWidget *lb = gtk_list_item_get_child(listitem);
  /* Strobj is owned by the instance. Caller mustn't change or destroy it. */
  GtkStringObject *strobj = gtk_list_item_get_item(listitem);
  /* The string returned by gtk_string_object_get_string is owned by the
   * instance. */
  gtk_label_set_text(GTK_LABEL(lb), gtk_string_object_get_string(strobj));
}

void unbind_cb(G_GNUC_UNUSED GtkSignalListItemFactory *self,
               G_GNUC_UNUSED GtkListItem *listitem,
               G_GNUC_UNUSED gpointer user_data) {
  /* There's nothing to do here. */
}
void teardown_cb(G_GNUC_UNUSED GtkSignalListItemFactory *self,
                 G_GNUC_UNUSED GtkListItem *listitem,
                 G_GNUC_UNUSED gpointer user_data) {
  /* There's nothing to do here. */
  /* GtkListItem instance will be destroyed soon. You don't need to set the
   * child to NULL. */
}

/*!
    @brief Добавление строки в матрицу char
        @param array массив строк
        @param string строка, которую нужно добавить
*/
char **add_string(char **array, const char *string) {
  int i = 0;
  while (array[i] != NULL) {
    i++;
  }
  array = realloc(array, (i + 2) * sizeof(char *));
  array[i] = malloc((strlen(string) + 1));
  strcpy(array[i], string);
  array[i + 1] = NULL;
  return array;
}

/*!
    @brief Вывод списка ставок в отдельном окне
*/
void show_list_rate(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  GtkWidget *window_list = gtk_window_new();
  gtk_window_set_default_size(GTK_WINDOW(window_list), 400, 400);
  gtk_window_set_title(GTK_WINDOW(window_list), "List of rates");
  gtk_widget_add_css_class(GTK_WIDGET(window_list), "window_list");
  GtkWidget *scr = gtk_scrolled_window_new();
  gtk_window_set_child(GTK_WINDOW(window_list), scr);

  char **array2 = malloc(sizeof(char *));
  array2[0] = NULL;
  calc->deposit.rate_type =
      gtk_combo_box_get_active(GTK_COMBO_BOX(calc->deposit.drop_down_interest));

  if (calc->deposit.rate_type == от_суммы)
    array2 = add_string(array2, "Сумма | Ставка %");
  else if (calc->deposit.rate_type == от_срока)
    array2 = add_string(array2, "День | Ставка");

  int stop = 0, i = 0;

  for (; i < ROWS && !stop; i++) {
    if (calc->deposit.mat_rate[i][0] == 1.0) {
      char exp[30] = {0};
      sprintf(exp, "%.2lf | %.2lf", calc->deposit.mat_rate[i][1],
              calc->deposit.mat_rate[i][2]);
      array2 = add_string(array2, exp);
    } else
      stop = 1;
  }

  GtkStringList *sl2 = gtk_string_list_new((const char *const *)array2);

  for (int j = 0; j < i; j++) {
    free(array2[j]);
  }
  free(array2);

  GtkNoSelection *ns = gtk_no_selection_new(G_LIST_MODEL(sl2));
  GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
  g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
  g_signal_connect(factory, "bind", G_CALLBACK(bind_cb), NULL);
  /* The following two lines can be left out. The handlers do nothing. */
  g_signal_connect(factory, "unbind", G_CALLBACK(unbind_cb), NULL);
  g_signal_connect(factory, "teardown", G_CALLBACK(teardown_cb), NULL);
  GtkWidget *lv = gtk_list_view_new(GTK_SELECTION_MODEL(ns), factory);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), lv);
  gtk_window_present(GTK_WINDOW(window_list));
}

/*!
    @brief Вывод списка пополнений в отдельном окне
*/
void show_list_repl(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  GtkWidget *window_list = gtk_window_new();
  gtk_window_set_default_size(GTK_WINDOW(window_list), 600, 400);
  gtk_window_set_title(GTK_WINDOW(window_list), "List of replenishments");
  gtk_widget_add_css_class(GTK_WIDGET(window_list), "window_list");
  GtkWidget *scr = gtk_scrolled_window_new();
  gtk_window_set_child(GTK_WINDOW(window_list), scr);

  char **array2 = malloc(sizeof(char *)), type_name[25] = {0};
  array2[0] = NULL;

  array2 = add_string(array2, "Период |    Дата    | Сумма");

  int stop = 0, i = 0;

  char types[6][25] = {
      "Разовое",       "Раз в месяц",   "Раз в 2 месяца",
      "Раз в квартал", "Раз в полгода", "Раз в год",
  };

  for (; i < ROWS && !stop; i++) {
    if (calc->deposit.mat_repl[i][0] > -1) {
      strcpy(type_name, types[(int)calc->deposit.mat_repl[i][0]]);

      char exp[100] = {0};

      sprintf(exp, "  %s |   %.0lf.%.0lf.%.0lf   | %.2lf", type_name,
              calc->deposit.mat_repl[i][1], calc->deposit.mat_repl[i][2],
              calc->deposit.mat_repl[i][3], calc->deposit.mat_repl[i][4]);

      array2 = add_string(array2, exp);
      memset(type_name, 0, 25);
    } else
      stop = 1;
  }

  GtkStringList *sl2 = gtk_string_list_new((const char *const *)array2);

  for (int j = 0; j < i; j++) {
    free(array2[j]);
  }
  free(array2);

  GtkNoSelection *ns = gtk_no_selection_new(G_LIST_MODEL(sl2));
  GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
  g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
  g_signal_connect(factory, "bind", G_CALLBACK(bind_cb), NULL);
  /* The following two lines can be left out. The handlers do nothing. */
  g_signal_connect(factory, "unbind", G_CALLBACK(unbind_cb), NULL);
  g_signal_connect(factory, "teardown", G_CALLBACK(teardown_cb), NULL);
  GtkWidget *lv = gtk_list_view_new(GTK_SELECTION_MODEL(ns), factory);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), lv);
  gtk_window_present(GTK_WINDOW(window_list));
}

/*!
    @brief Вывод списка снятий в отдельном окне
*/
void show_list_cuts(GtkButton *button, calculator *calc) {
  gtk_widget_set_visible(GTK_WIDGET(button), 1);
  GtkWidget *window_list = gtk_window_new();
  gtk_window_set_default_size(GTK_WINDOW(window_list), 600, 400);
  gtk_window_set_title(GTK_WINDOW(window_list), "List of cuts");
  gtk_widget_add_css_class(GTK_WIDGET(window_list), "window_list");
  GtkWidget *scr = gtk_scrolled_window_new();
  gtk_window_set_child(GTK_WINDOW(window_list), scr);
  char **array2 = malloc(sizeof(char *)), type_name[25] = {0};
  array2[0] = NULL;

  array2 = add_string(array2, "Период |    Дата    | Сумма");

  int stop = 0, i = 0;

  char types[6][25] = {
      "Разовое",       "Раз в месяц",   "Раз в 2 месяца",
      "Раз в квартал", "Раз в полгода", "Раз в год",
  };

  for (; i < ROWS && !stop; i++) {
    if (calc->deposit.mat_cut[i][0] > -1) {
      strcpy(type_name, types[(int)calc->deposit.mat_cut[i][0]]);
      char exp[100] = {0};
      sprintf(exp, "  %s |   %.0lf.%.0lf.%.0lf   | %.2lf", type_name,
              calc->deposit.mat_cut[i][1], calc->deposit.mat_cut[i][2],
              calc->deposit.mat_cut[i][3], calc->deposit.mat_cut[i][4]);

      array2 = add_string(array2, exp);
      memset(type_name, 0, 25);
    } else
      stop = 1;
  }
  GtkStringList *sl2 = gtk_string_list_new((const char *const *)array2);

  for (int j = 0; j < i; j++) {
    free(array2[j]);
  }
  free(array2);

  GtkNoSelection *ns = gtk_no_selection_new(G_LIST_MODEL(sl2));
  GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
  g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
  g_signal_connect(factory, "bind", G_CALLBACK(bind_cb), NULL);
  /* The following two lines can be left out. The handlers do nothing. */
  g_signal_connect(factory, "unbind", G_CALLBACK(unbind_cb), NULL);
  g_signal_connect(factory, "teardown", G_CALLBACK(teardown_cb), NULL);
  GtkWidget *lv = gtk_list_view_new(GTK_SELECTION_MODEL(ns), factory);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), lv);
  gtk_window_present(GTK_WINDOW(window_list));
}