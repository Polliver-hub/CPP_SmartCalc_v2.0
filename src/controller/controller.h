#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <QMainWindow>

#include "../model/model.h"
#include "graphplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Controller;
}
QT_END_NAMESPACE

namespace s21 {
/**
 * @brief Контроллер для приложения калькулятора
 */
class Controller : public QMainWindow {
  Q_OBJECT

 public:
  Controller(
      QWidget *parent = nullptr);  ///< Дефолтный конструктор с вариационным
                                   ///< указателем на родителя
  ~Controller();  ///< Дефолтный деструктор

 private slots:
  void on_pushButton_graph_clicked();  ///< Слот вызывает создание графика
  void on_pushButton_C_clicked();  ///< Слот вызывает очистку всего уравнения
  void
  on_pushButton_equil_clicked();  ///< Слот вызывает вызов решения уравнения

  void
  AnyButtonClick();  ///< Слот добавляет символ кнопки которая вызвала этот слот

 private:
  Ui::Controller *ui;  ///< Указатель на View
  Model data;          ///< Объект класса Model
};

}  // namespace s21

#endif  // CONTROLLER_H_
