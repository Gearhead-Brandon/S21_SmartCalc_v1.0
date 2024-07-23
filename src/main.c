#include "s21_smart_calc.h"

int main(int argc, char **argv) {
  GtkApplication *app;
  gtk_init();

  calculator calc;
  calculator_init(&calc);

  int status;

  app = gtk_application_new("org.gtk.calculator", G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(activate), &calc);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}