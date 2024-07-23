/*!
        @file
        @brief Заголовочный файл с описанием структур, перечислений и
   прототопипов.

        Данный файл содержит в себе прототипы функций, определения структур
   обычного калькулятороа, кредитного и депозитного. А также перечислений для
   депозитного калькулятора.
*/
#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

#define _GNU_SOURCE

#define ROWS 10
#define COLUMNS 3

#define COLUMNS7 7

#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_INFINITY (1.0f / 0.0f)
#define S21_NEGATIVE_INFINITY (-1.0f / 0.0f)

#define s21_is_nan(x) (x != x)
#define s21_is_inf(x) (x == S21_INFINITY || x == S21_NEGATIVE_INFINITY)

/// Перечисление типов срока размещения депозита
enum start_date { дней, месяцев, лет };

/// Перечисление типов процентной ставки депозита
enum interest_rate { фиксированная, от_суммы, от_срока };

/// Перечисление типов периодичности выплат/капитализации
enum frequency_of_paymnets {
  каждый_день,
  каждую_неделю,
  раз_в_месяц,
  раз_в_квартал,
  раз_в_полгода,
  раз_в_год,
  в_конце_срока
};

/// Перечисление типов периодичности пополнений/снятий
enum replenishment_and_cut {
  _разовое,
  _раз_в_месяц,
  _раз_в_2_месяца,
  _раз_в_квартал,
  _раз_в_полгода,
  _раз_в_год,
};

/// Структура, описывающая депозитный калькулятор
typedef struct {
  double amount;            ///< Начальная сумма депозита
  double term;              ///< Срок депозита
  char start_date[25];      ///< Дата начала срока
  double rate;              ///< Начальная процентная ставка
  double taxe;              ///< Налог
  double taxe_free_amount;  ///< Сумма свободная от налога

  int all_term_type;        ///< Тип срока размещения
  int rate_type;            ///< Тип процентной ставки
  int periodicity_type;     ///< Тип периодичности выплат/капитализации
  int capytalization_type;  ///< Тип капитализации
  int taxes_type;           ///< Тип налога

  double temp_inte_charges;  ///< Буфер для начисленных процентов

  double res_inte_charges;  ///< Итоговые начисленные проценты
  double res_amount;       ///< Итоговая сумма
  double res_taxes;       ///< Итоговая сумма налога

  int current_month;  ///< Текущий месяц
  int current_day;    ///< Текущий день
  int current_year;   ///< Текущий год

  double mat_rate[ROWS][COLUMNS];  ///< Матрица с процентными ставками
  double mat_repl[ROWS][COLUMNS7];  ///< Матрица с пополнениями
  double mat_cut[ROWS][COLUMNS7];  ///< Матрица со снятиями

  double *lost_additions;  ///< Матрица с потерянными пополнениями/снятиями
  int count_l_a;  ///< Количество потерянных пополнений/снятий

  GtkWidget *grid;       ///< Сетка размещения элементов
  GtkWidget *entry[10];  ///< Поля ввода

  GtkDropDown *drop_down_term;  ///< Список сроков размещения
  GtkDropDown *drop_down_replenishment;  ///< Список периодичности пополнений
  GtkDropDown *drop_down_cut;  ///< Список периодичности снятий

  GtkWidget *drop_down_interest;  ///< Список типов процентной ставки
  GtkWidget *
      drop_down_periodity;  ///< Список типов периодичности выплат/капитализации

  GtkWidget *periodicity_label;  ///< Надпись периодичности выплат/капитализации
  GtkWidget *error_widget;       ///< Виджет ошибки

  GtkWidget *check_button_cap;  ///< Кнопка переключатель капитализации
  GtkWidget *check_button_taxes;  ///< Кнопка переключатель налога

  GtkWidget *add_rate;  ///< Кнопка добавления процентной ставки
  GtkWidget *remove_rate;  ///< Кнопка удаления процентной ставки

  GtkWidget *show_list_rate;  ///< Кнопка выводящая список процентных ставок

} DepositCalc;

/// Структура, описывающая кредитный калькулятор
typedef struct {
  double amount;  ///< Начальная сумма кредита
  double rate;    ///< Процентная ставка
  double term;    ///< Срок кредита

  double res_mon_pay;    ///< Сумма ежемесячной выплаты
  double res_inte_rest;  ///< Начисленные проценты
  double res_debt_interest;  ///< Долг + проценты

  GtkWidget *grid;      ///< Сетка размещения элементов
  GtkWidget *entry[3];  ///< Поля ввода
  GtkWidget *check_button[4];  ///< Кнопки переключатели

} CreditCalc;

/// Структура, описывающая график функции
typedef struct {
  double x_min;  ///< Минимальное значение Х
  double x_max;  ///< Максимальное значение Х
  double y_min;  ///< Минимальное значение Y
  double y_max;  ///< Максимальное значение Y

  GtkWidget *area;            ///< Поле отрисовки графика
  GtkWidget *entry_graph[4];  ///< Поля ввода областей определения и значени
  GtkWidget *error_widget;    ///< Виджет ошибки
  int status;                 ///< Статус графика

} Graph_of_func;

/// Структура, описывающая умный калькулятор
typedef struct {
  GtkWidget *window;  ///< Виджет окна приложения
  GtkWidget *grid;    ///< Сетка размещения элементов
  GtkWidget *button[40];  ///< Кнопки калькулятора

  char input_buffer[300];  ///< Буфер ввода выражения

  char X_value[30];  ///< Буфер ввода Х
  char last_x;       ///< Последний символ Х

  int f_input_x;      ///< Флаг ввода Х
  int is_arithmetic;  ///< Флаг арифметической функции

  Graph_of_func graph;  ///< График функции
  DepositCalc deposit;  ///< Депозитный калькулятор
  CreditCalc credit;    ///< Кредитный калькулятор

} calculator;

typedef struct Node Node;

/// Структура, описывающая узел стека и очереди
struct Node {
  char data[40];  ///< Данные
  Node *next;     ///< Указатель на следующий узел
};

/// Структура, описывающая очередь
typedef struct {
  Node *head;  ///< Указатель на первый узел
  Node *tail;  ///< Указатель на последний узел
} Queue;

//////////// POLISH NOTATION ////////////

int from_infix_to_postfix(char *str, char *x, Queue *queue);

int from_postfix_to_double(Queue *queue, char *x, double *result);

int get_instruction(char *last, char *current);

int get_index(char *operation);

double calc_two_double(double *arr, char *operation);

double calc_func_double(double *arr, char *operation);

int is_arithmetic(char sym);

int validity_check_x(char *str);

int validity_check(char *str, int *have_x);

///////////// Stack /////////////

Node *list_create();

// void print_stack(Node * list);

int is_empty_stack(Node *list);

char *peek_stack(struct Node *list);

// int  stack_size(struct Node * list);

void clear_stack(struct Node **plist);

void push(Node **list, char *x);

char *pop(Node **list);

///////////// Queue /////////////

struct Node *newNode(char *item);

int is_empty_queue(Queue *q);

char *peek_queue(Queue *q);

void enqueue(Queue *q, char *item);

char *dequeue(Queue *q);

void print_queue(Queue *lst);

void clear_queue(Queue *lst);

///////////// GUI ///////////////

void activate(GtkApplication *appl, calculator *widget);

void include_css();

void create_structure_app(calculator *widget);

void main_calc(calculator *widget);

void main_calc_create(GtkButton *button, calculator *widget);

void add_menu(calculator *widget);

//////////////// VALIDATORS ////////////////////

int validate_credit(char *str);

int validity_check_dot(char *str);

int validate_credit(char *str);

int validate_rate_deposit(char *str);

////////////// INIT FUNCTIONS //////////////////

void init_matrix(int rows, int columns, double array[rows][columns]);

void calculator_init(calculator *calc);

///////////// SMARTCALC FUNCTIONS ////////////////

void create_buttons(calculator *widget);

void attach_butons_to_grid(calculator *widget);

void connect_buttons(calculator *widget);

void calculate(GtkButton *button, calculator *calc);

void add_to_buffer(calculator *calc, char *text, int *dont_check);

void entering_numbers_and_operations(calculator *calc, char *text,
                                     int *dont_check, char last_char_input);

void function_input(calculator *calc, char *text, char last_char_input);

void input_X(calculator *calc, char *text);

void input_X(calculator *calc, char *text);

void solve_expression(calculator *calc, int *error);

void erase_expression(calculator *calc, int *write);

void error_output(calculator *calc);

void from_comma_to_dot(char *str);

int symbol_not_arithmetic(char str);

int symbol_arithmetic(char str);

/////////////////// GRAPH ///////////////////////

void draw_grid_axes(cairo_t *cr, int width, int height, calculator *calc);

void plot(GtkDrawingArea *area, cairo_t *cr, int width, int height,
          calculator *calc);

void plot_button(GtkButton *button, GtkDrawingArea *area, gpointer data);

void draw_cb(GtkDrawingArea *area, cairo_t *cr, int width, int height,
             gpointer data);

double new_x(double x, double range, double sum, double width);

double new_y(double y, double range, double sum, double height);

int from_postfix_to_result(Queue *queue, double x, double *result);

///////////// CREDIT FUNCTIONS //////////////////

void create_credit_calc(GtkButton *button, calculator *calc);

void calculus_credit_payments(GtkButton *button, calculator *calc);

void calculate_annuity(calculator *calc);

void calculate_differentiated(calculator *calc, char **out_pay);

///////////// DEPOSIT FUNCTIONS ///////////////]

void create_deposit_calc(GtkButton *button, calculator *calc);

void show_list_repl(GtkButton *button, calculator *calc);

void show_list_rate(GtkButton *button, calculator *calc);

void teardown_cb(GtkSignalListItemFactory *self, GtkListItem *listitem,
                 gpointer user_data);

void unbind_cb(GtkSignalListItemFactory *self, GtkListItem *listitem,
               gpointer user_data);

void bind_cb(GtkSignalListItemFactory *self, GtkListItem *listitem,
             gpointer user_data);

void setup_cb(GtkSignalListItemFactory *self, GtkListItem *listitem,
              gpointer user_data);

void toggled_periodicity_deposit(GtkWidget *check_button, calculator *calc);

void toggled_interest_deposit(GtkWidget *check_button, calculator *calc);

void toggled_taxes_deposit(GtkWidget *check_button, calculator *calc);

void add_rate_button(GtkButton *button, calculator *calc);

void rem_rate_button(GtkButton *button, calculator *calc);

void add_repl_button(GtkButton *button, calculator *calc);

void rem_repl_button(GtkButton *button, calculator *calc);

char **add_string(char **array, const char *string);

void calculus_deposit_payments(GtkButton *button, calculator *calc);

void calculate_deposit(calculator *calc);

int is_leap_year(int year);

void split_date(calculator *calc, int *day, int *month, int *year);

int get_total_days(calculator *calc);

int validity_date(char *str);

void calc_periodity_types(calculator *calc, int *point, double num,
                          int *date_point);

int array_rate_is_empty(calculator *calc);

int change_rate_on_amount(calculator *calc);

int change_rate_on_term(calculator *calc, int point);

int validate_rate_deposit(char *str);

int days_in_month(int month, int year);

void load_date_from_char(char *str, int *month, int *day, int *year);

void flow_of_time(int *month, int *day, int *year);

void increase_in_months(int *month, int *year);

int count_days(int month1, int day1, int year1, int month2, int day2,
               int year2);

int correctness_of_the_second_date(calculator *calc, int month2, int day2,
                                   int year2);

void processing_incorrect_replenishments(calculator *calc, double src[10][7],
                                         double **arr, int *n, int flag);

void replenishments_and_cuts(calculator *calc, double arr[10][7], int flag);

void collect_lost_additions(calculator *calc, double amount);

void calc_replenishments(calculator *calc, double arr[10][7], int i, int flag);

void push_repl_to_arr(double src[10][7], double **arr, int *n, int i, int flag);

void reduction_initial_state(calculator *calc);

void show_list_cuts(GtkButton *button, calculator *calc);

int determine_refill_point(int month, int year, int type);

void rem_cut_button(GtkButton *button, calculator *calc);

void add_cut_button(GtkButton *button, calculator *calc);

int determine_refill_date(int month, int year, int type);

#endif