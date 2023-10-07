#include <QApplication>

#include "controller/calculator_controller.h"
#include "view/calculator_view.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::Models my_model;
  s21::CalculatorController processing(my_model);
  s21::CalculatorView window(processing);
  window.show();
  return app.exec();
}
