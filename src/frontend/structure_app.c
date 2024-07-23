/*!
        @file
        @brief Структура приложения и начального окна
*/
#include "../s21_smart_calc.h"  // gcc -o a draw.c $(pkg-config --cflags --libs gtk4)

/*!
    @brief Подключение CSS стилей
*/
void include_css() {
  const char cssPath[15] = "frontend/a.css";
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, cssPath);
  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(cssProvider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);
}

/*!
    @brief Создание структуры приложения
*/
void create_structure_app(calculator *widget) {
  gtk_window_set_title(GTK_WINDOW(widget->window), "Smart calculator");
  gtk_widget_add_css_class(widget->window, "window");
  gtk_window_set_default_size(GTK_WINDOW(widget->window), 100, 100);

  widget->grid = gtk_grid_new();
  gtk_widget_add_css_class(widget->grid, "grid_regular_calc");

  widget->graph.area = gtk_drawing_area_new();
  gtk_widget_set_size_request(widget->graph.area, 500, 100);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_add_css_class(left_box, "left_box");
  ///////////////////////////////////////////////////////////////////////////////////////////
  GtkWidget *domain = gtk_label_new("Область определения X");
  gtk_widget_add_css_class(domain, "domain");
  gtk_box_append(GTK_BOX(left_box), domain);

  GtkWidget *codomain = gtk_label_new("Область значения Y");
  gtk_widget_add_css_class(codomain, "domain");

  for (int i = 0; i < 4; i++) {
    widget->graph.entry_graph[i] = gtk_entry_new();
    gtk_widget_add_css_class(widget->graph.entry_graph[i], "entry_graph");
    if (i == 2) gtk_box_append(GTK_BOX(left_box), codomain);

    gtk_box_append(GTK_BOX(left_box), widget->graph.entry_graph[i]);
  }
  widget->graph.error_widget = gtk_label_new("ERROR");
  gtk_widget_add_css_class(widget->graph.error_widget, "error_graph");
  gtk_box_append(GTK_BOX(left_box), widget->graph.error_widget);

  gtk_entry_set_placeholder_text(GTK_ENTRY(widget->graph.entry_graph[0]),
                                 "MIN -10");
  gtk_entry_set_placeholder_text(GTK_ENTRY(widget->graph.entry_graph[1]),
                                 "MAX 10");
  gtk_entry_set_placeholder_text(GTK_ENTRY(widget->graph.entry_graph[2]),
                                 "MIN -10");
  gtk_entry_set_placeholder_text(GTK_ENTRY(widget->graph.entry_graph[3]),
                                 "MAX 10");
  ///////////////////////////////////////////////////////////////////////////////////////////
  gtk_window_set_child(GTK_WINDOW(widget->window), box);

  gtk_box_append(GTK_BOX(box), left_box);

  gtk_box_append(GTK_BOX(box), widget->graph.area);

  gtk_box_append(GTK_BOX(box), widget->grid);

  gtk_widget_set_visible(widget->graph.error_widget, 0);
}

/*!
    @brief Создание главного калькулятора
*/
void main_calc(calculator *widget) {
  widget->graph.status = 0;
  create_structure_app(widget);
  create_buttons(widget);
  attach_butons_to_grid(widget);
  connect_buttons(widget);
}

/*!
    @brief Функция обертка создания главного калькулятора
*/
void main_calc_create(G_GNUC_UNUSED GtkButton *button, calculator *widget) {
  main_calc(widget);
}

/*!
    @brief Создание меню окна приложения
*/
void add_menu(calculator *widget) {
  GtkWidget *menubar = gtk_header_bar_new();
  gtk_window_set_titlebar(GTK_WINDOW(widget->window), menubar);

  GtkWidget *menu_button_main = gtk_button_new_with_label("Calc");
  gtk_widget_add_css_class(menu_button_main, "menu_bar");
  GtkWidget *menu_button_credit = gtk_button_new_with_label("Credit");
  gtk_widget_add_css_class(menu_button_credit, "menu_bar");
  GtkWidget *menu_button_deposit = gtk_button_new_with_label("Deposit");
  gtk_widget_add_css_class(menu_button_deposit, "menu_bar");

  gtk_header_bar_pack_start(GTK_HEADER_BAR(menubar), menu_button_main);
  gtk_header_bar_pack_start(GTK_HEADER_BAR(menubar), menu_button_credit);
  gtk_header_bar_pack_start(GTK_HEADER_BAR(menubar), menu_button_deposit);
  gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(menubar), 1);

  g_signal_connect(menu_button_main, "clicked", G_CALLBACK(main_calc_create),
                   widget);
  g_signal_connect(menu_button_credit, "clicked",
                   G_CALLBACK(create_credit_calc), widget);
  g_signal_connect(menu_button_deposit, "clicked",
                   G_CALLBACK(create_deposit_calc), widget);
}

/*!
    @brief Запуск приложения и создание окна
*/
void activate(GtkApplication *appl, calculator *widget) {
  widget->window = gtk_application_window_new(appl);
  include_css();
  add_menu(widget);
  main_calc(widget);
  gtk_window_present(GTK_WINDOW(widget->window));
}