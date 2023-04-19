#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Mainwindow;
}
QT_END_NAMESPACE

namespace s21 {
/**
 * @brief View для приложения калькулятора
 */
class Mainwindow : public QMainWindow {
  Q_OBJECT

 public:
  Mainwindow(
      QWidget *parent = nullptr);  ///< Дефолтный конструктор с вариационным
                                   ///< указателем на родителя
  ~Mainwindow();  ///< Дефолтный деструктор

 private slots:
  void on_pushButton_graph_clicked();  ///< Слот вызывает создание графика
  void on_pushButton_C_clicked();  ///< Слот вызывает очистку всего уравнения
  void
  on_pushButton_equil_clicked();  ///< Слот вызывает вызов решения уравнения

  void
  AnyButtonClick();  ///< Слот добавляет символ кнопки которая вызвала этот слот

 private:
  Ui::Mainwindow *ui;     ///< Указатель на View
  Controller controller;  ///< Объект класса Controller
};

}  // namespace s21

#endif  // MAINWINDOW_H_
