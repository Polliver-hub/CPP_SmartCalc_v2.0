#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::Mainwindow window;
  window.show();
  return app.exec();
}
