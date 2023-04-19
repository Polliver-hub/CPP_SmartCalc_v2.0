#include "mainwindow.h"

#include "graphplot.h"
#include "ui_mainwindow.h"

using namespace s21;

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Mainwindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(AnyButtonClick()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));

  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(AnyButtonClick()));
  connect(ui->pushButton_closed_bracket, SIGNAL(clicked()), this,
          SLOT(AnyButtonClick()));

  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));

  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
}

void Mainwindow::AnyButtonClick() {
  switch (controller.pushBack(
      ((QPushButton *)sender())->text().toStdString().back())) {
    case Model::DOT_FOR_CONST:
      QMessageBox::warning(this, "Ошибка",
                           "Невозможно установить точность к константе");
      break;
    case Model::DOUBLE_DOT:
      QMessageBox::warning(this, "Ошибка", "В этом числе уже есть точка");
      break;
    case Model::DOUBLE_OPER:
      QMessageBox::warning(
          this, "Ошибка",
          "Нельзя применить бинарный оператор к бинарному оператору");
      break;
    case Model::OPER_FOR_NEW_EXP:
      QMessageBox::warning(this, "Ошибка",
                           "Нет первого аргумента для бинарного оператора");
      break;
    case Model::BRACKET_MINUS:
      QMessageBox::warning(this, "Ошибка",
                           "Невозможные скобочные представления");
      break;
    case Model::OVER_FLOW_EXP:
      QMessageBox::warning(
          this, "Ошибка",
          "Размер строки переполнен, максимальное значение 255 символов");
      break;
    case Model::INCOMPLETE_EXP:
      QMessageBox::warning(this, "Ошибка",
                           "Невозможно закончить скобочное уравнение, "
                           "требуется поставить значение");
      break;
    default:
      ui->input_text->setText(QString::fromStdString(controller.ToString()));
  };
}

Mainwindow::~Mainwindow() { delete ui; }

void Mainwindow::on_pushButton_graph_clicked() {
  if (controller.IsValid()) {
    QLineSeries *series = new QLineSeries();
    int xAxisSize = ui->doubleSpinBox_domain_max->value(),
        yAxisSize = ui->doubleSpinBox_range_max->value();
    double increment = xAxisSize / 10000.;
    double result;
    for (double i = -xAxisSize; i < xAxisSize; i += increment) {
      if (!controller.SolveEquation(&result, i)) {
        *series << QPointF(i, result);
      }
    }
    GraphPlot graph(series, yAxisSize, xAxisSize);
    graph.exec();
    on_pushButton_C_clicked();
  } else {
    controller.Clear();
    QMessageBox::warning(this, "Ошибка", "Не правильное уравнение");
  }
}

void Mainwindow::on_pushButton_C_clicked() {
  controller.Clear();
  ui->input_text->setText(QString::fromStdString(controller.ToString()));
}

void Mainwindow::on_pushButton_equil_clicked() {
  double result = 0;
  QString history = ui->input_text->text();
  Model::CalculationError error =
      controller.SolveEquation(&result, ui->doubleSpinBox_SetX->value());
  if (!error) {
    controller.AddNewExp(QString::number(result).toStdString());
    ui->input_text->setText(QString::fromStdString(controller.ToString()));
    history += " = " + ui->input_text->text();
    ui->history_text->appendPlainText(history);
  } else {
    QString error_text;
    switch (error) {
      case Model::WRONG_EXP:
        error_text = "Не правильное уравнение";
        break;
      case Model::LOG_MINUS:
      case Model::LN_MINUS:
        error_text = "Нет логарифма от отрицательного числа";
        break;
      case Model::SQRT_MINUS:
        error_text = "Нет корня от отрицательного числа";
        break;
      case Model::ASIN_RANGE:
        error_text = "Арксинус ограничен от -1 до 1";
        break;
      case Model::ACOS_RANGE:
        error_text = "Арккосинус ограничен от -1 до 1";
        break;
      case Model::DIV_ZERO:
        error_text = "Деление на ноль - невозможно";
        break;
      case Model::SUCCESS:
        break;
    }
    QMessageBox::warning(this, "Ошибка", error_text);
  }
}
