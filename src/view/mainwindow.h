#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QClipboard>
#include <QKeyEvent>
#include <QMainWindow>
#include <QScreen>

#include "graph.h"
#include "polish.h"

#define END 0
#define NUMBER 1  //цифры
#define SIGN 2    //знаки
#define DOT 3     //точка
#define BOP 4     //(
#define BCL 5     //)
#define BTX 6     //х
#define OPR 7     // sin
#define EQL 8

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  graph *graph_form;
  double arg;

 private slots:
  void digits_numbers();
  void digits_sign();
  void on_pushButton_C_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_open_bracket_clicked();
  void on_pushButton_closed_bracket_clicked();

  void on_doubleSpinBox_SetX_valueChanged(double arg1);
  void on_input_text_textChanged();
  void on_checkBox_graf_clicked(bool checked);
  void Window_Pos();

  QString first_num(QString butt);
  bool Validate(int clicked_button);
  void on_pushButton_degree_clicked();
  void on_pushButton_mod_clicked();
  void function_trig();
  void on_pushButton_equil_clicked();
  void on_doubleSpinBox_domain_min_valueChanged(double arg1);
  void on_doubleSpinBox_domain_max_valueChanged(double arg1);
  void on_doubleSpinBox_range_min_valueChanged(double arg1);
  void on_doubleSpinBox_range_max_valueChanged(double arg1);

 protected:
  virtual void keyPressEvent(QKeyEvent *event);

 signals:
  void sendPrint(const char *str_in1, double *ranges);
};
#endif  // MAINWINDOW_H
