#include "mainwindow.h"

#include "ui_mainwindow.h"

bool sign = false;
int butt_end = END;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_sign()));

  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(function_trig()));

  graph_form = new graph();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_doubleSpinBox_SetX_valueChanged(double arg1) { arg = arg1; }

void MainWindow::on_pushButton_C_clicked() {
  Validate(END);
  ui->input_text->setPlainText("0");
}

void MainWindow::digits_numbers() {
  if (Validate(NUMBER)) {
    QPushButton *button = (QPushButton *)sender();
    ui->input_text->setPlainText(first_num(button->text()));
  }
}

void MainWindow::digits_sign() {
  if (Validate(SIGN)) {
    QPushButton *button = (QPushButton *)sender();
    if (ui->input_text->toPlainText() == "0" ||
        ui->input_text->toPlainText() == "(") {
      if (button->text() == "+" || button->text() == "-")
        ui->input_text->setPlainText(button->text());
    } else {
      ui->input_text->setPlainText(ui->input_text->toPlainText() +
          button->text());
    }
  }
}

void MainWindow::on_pushButton_degree_clicked() {
  if (Validate(SIGN))
    ui->input_text->setPlainText(ui->input_text->toPlainText() + "^");
}

void MainWindow::on_pushButton_mod_clicked() {
  if (Validate(SIGN))
    ui->input_text->setPlainText(ui->input_text->toPlainText() + "m");
}

void MainWindow::on_pushButton_dot_clicked() {
  if (Validate(DOT))
    ui->input_text->setPlainText(ui->input_text->toPlainText() + ".");
}

void MainWindow::on_pushButton_open_bracket_clicked() {
  if (Validate(BOP)) ui->input_text->setPlainText(first_num("("));
}

void MainWindow::on_pushButton_closed_bracket_clicked() {
  if (Validate(BCL)) ui->input_text->setPlainText(first_num(")"));
}

void MainWindow::on_pushButton_x_clicked() {
  if (Validate(BTX)) ui->input_text->setPlainText(first_num("x"));
}

void MainWindow::function_trig() {
  if (Validate(OPR)) {
    QString new_label;
    QPushButton *button = (QPushButton *)sender();
    if (button->text() == "cos")
      new_label = "cos(";
    else if (button->text() == "sin")
      new_label = "sin(";
    else if (button->text() == "sin")
      new_label = "sin(";
    else if (button->text() == "tan")
      new_label = "tan(";
    else if (button->text() == "acos")
      new_label = "acos(";
    else if (button->text() == "asin")
      new_label = "asin(";
    else if (button->text() == "atan")
      new_label = "atan(";
    else if (button->text() == "log")
      new_label = "log(";
    else if (button->text() == "ln")
      new_label = "ln(";
    else if (button->text() == "sqrt")
      new_label = "sqrt(";

    ui->input_text->setPlainText(first_num(new_label));
  }
}

void MainWindow::on_pushButton_equil_clicked() {
  char str_normal[STACK_MAX_SIZE];
  char str_polish[STACK_MAX_SIZE];
  int is_error = 0;
  strcpy(str_normal, ui->input_text->toPlainText().toLocal8Bit().data());
  if (sign)
    on_pushButton_C_clicked(),
        strcpy(str_normal, ui->input_text->toPlainText().toLocal8Bit().data());
  convert_to_polish_record(str_normal, str_polish);
  QString history = ui->input_text->toPlainText();
  bool checkBox_graf = ui->checkBox_graf->isChecked();
  QString str_out = "0";
  if (checkBox_graf) {
    calculate_value(str_polish, 1, &is_error);
    if (!is_error) {
      Window_Pos();
      double ranges[4] = {
          ui->doubleSpinBox_domain_min->value(), ui->doubleSpinBox_domain_max->value(),
          ui->doubleSpinBox_range_min->value(), ui->doubleSpinBox_range_max->value()};
      connect(this, SIGNAL(sendPrint(const char*,double*)), graph_form,
          SLOT(Print(const char*,double*)), Qt::DirectConnection);
      graph_form->show();
      emit sendPrint(str_polish, ranges);
    }
    butt_end = END;
  } else {
      double rez = calculate_value(str_polish, arg, &is_error);
      str_out = QString::number(rez, 'g', 15);
      rez = QVariant{str_out}.toDouble();
      str_out = QVariant{rez}.toString();
      butt_end = EQL;
      sign = false;
  }
  switch (is_error) {
    case -1:
      str_out = "стек переполнен";
      break;
    case -2:
      str_out = "недостаточно операндов в стеке";
      break;
    case -3:
      str_out = "неверное значение";
      break;
    case -4:
      str_out = "нет закрывающей скобки";
      break;
    case -5:
      str_out = "бесконечность";
      break;
  }
  ui->input_text->setPlainText(str_out);
  if (!checkBox_graf) history += " = " + str_out;
  ui->history_text->appendPlainText(history);
}

void MainWindow::on_input_text_textChanged() {
  if (ui->input_text->toPlainText().length() > 255) on_pushButton_C_clicked();
  if (!ui->input_text->toPlainText().contains('x')) {
    arg = 1.0;
    ui->label_SetX->setEnabled(false);
    ui->doubleSpinBox_SetX->setEnabled(false);
    if (ui->checkBox_graf->isChecked()) {
      on_checkBox_graf_clicked(0);
      ui->checkBox_graf->setChecked(0);
    }
  } else {
    if (!ui->checkBox_graf->isChecked()) {
      arg = ui->doubleSpinBox_SetX->value();
      ui->label_SetX->setEnabled(true);
      ui->doubleSpinBox_SetX->setEnabled(true);
    }
  }
}

void MainWindow::on_checkBox_graf_clicked(bool checked) {
  if (checked) {
    ui->label_SetX->setEnabled(false);
    ui->doubleSpinBox_SetX->setEnabled(false);
    ui->label_domain->setEnabled(true);
    ui->doubleSpinBox_domain_min->setEnabled(true);
    ui->doubleSpinBox_domain_max->setEnabled(true);
    ui->label_range->setEnabled(true);
    ui->doubleSpinBox_range_min->setEnabled(true);
    ui->doubleSpinBox_range_max->setEnabled(true);
  } else {
    if (!ui->input_text->toPlainText().contains('x')) {
      ui->label_SetX->setEnabled(false);
      ui->doubleSpinBox_SetX->setEnabled(false);
    } else {
      ui->label_SetX->setEnabled(true);
      ui->doubleSpinBox_SetX->setEnabled(true);
    }
    ui->label_domain->setEnabled(false);
    ui->doubleSpinBox_domain_min->setEnabled(false);
    ui->doubleSpinBox_domain_max->setEnabled(false);
    ui->label_range->setEnabled(false);
    ui->doubleSpinBox_range_min->setEnabled(false);
    ui->doubleSpinBox_range_max->setEnabled(false);
  }
}

void MainWindow::Window_Pos() {
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rect = screen->availableGeometry();
  QPoint center = rect.center();
  center.setX(center.x() - (this->width() + 5));
  center.setY(center.y() - (this->height() / 2));
  move(center);
}

QString MainWindow::first_num(QString butt) {
  return (ui->input_text->toPlainText() == "0")
         ? butt
         : ui->input_text->toPlainText() + butt;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  QString str = event->text();
  if (key >= Qt::Key_0 && key <= Qt::Key_9) {
    this->findChild<QPushButton *>("Button_" + str)->click();
  } else if (key == Qt::Key_Delete) {
    ui->pushButton_C->click();
  } else if (key == Qt::Key_Plus) {
    ui->pushButton_plus->click();
  } else if (key == Qt::Key_Minus) {
    ui->pushButton_minus->click();
  } else if (key == Qt::Key_Asterisk) {
    ui->pushButton_mul->click();
  } else if (key == Qt::Key_ParenLeft) {
    ui->pushButton_open_bracket->click();
  } else if (key == Qt::Key_ParenRight) {
    ui->pushButton_closed_bracket->click();
  } else if (key == Qt::Key_Slash) {
    ui->pushButton_del->click();
  } else if (key == Qt::Key_Period || key == Qt::Key_Comma) {
    ui->pushButton_dot->click();
  } else if (key == Qt::Key_V && event->modifiers() & Qt::ControlModifier) {
    ui->input_text->setPlainText(QGuiApplication::clipboard()->text());
    ui->pushButton_equil->click();
  } else if (key == Qt::Key_Enter || key == Qt::Key_Return) {
    ui->pushButton_equil->click();
  } else if (key == Qt::Key_Escape) {
  }
}

bool MainWindow::Validate(int clicked_button) {
  bool rez = false;
  if (butt_end == END) ui->input_text->setPlainText("0");
  switch (clicked_button) {
    case END:
      rez = true;
      sign = false;
      break;
    case NUMBER:
      if (butt_end != BTX && butt_end != BCL && butt_end != EQL) {
        rez = true;
        sign = false;
      }
      break;
    case SIGN:
      if (butt_end != DOT) {
        rez = true;
        sign = true;
      }
      break;
    case DOT:
      if (butt_end == END || butt_end == NUMBER) rez = true;
      break;
    case BOP:
      if (butt_end == END || butt_end == SIGN || butt_end == BOP) {
        rez = true;
        sign = false;
      }
      break;
    case BCL:
      if (butt_end == NUMBER || butt_end == BTX || butt_end == BCL) rez = true;
      break;
    case BTX:
      if (butt_end == END || butt_end == SIGN || butt_end == BOP ||
          butt_end == OPR) {
        rez = true;
        sign = false;
      }
      break;
    case OPR:
      if (butt_end == END || butt_end == SIGN || butt_end == BOP ||
          butt_end == OPR) {
        rez = true;
        sign = false;
      }
      break;
  }

  if (rez) butt_end = clicked_button;
  return rez;
}

void MainWindow::on_doubleSpinBox_domain_min_valueChanged(double arg1) {
  if (arg1 >= ui->doubleSpinBox_domain_max->value())
    ui->doubleSpinBox_domain_min->setValue(ui->doubleSpinBox_domain_max->value() - 1);
}

void MainWindow::on_doubleSpinBox_domain_max_valueChanged(double arg1) {
  if (arg1 <= ui->doubleSpinBox_domain_min->value())
    ui->doubleSpinBox_domain_max->setValue(ui->doubleSpinBox_domain_min->value() + 1);
}

void MainWindow::on_doubleSpinBox_range_min_valueChanged(double arg1) {
  if (arg1 >= ui->doubleSpinBox_range_max->value())
    ui->doubleSpinBox_range_min->setValue(ui->doubleSpinBox_range_max->value() - 1);
}

void MainWindow::on_doubleSpinBox_range_max_valueChanged(double arg1) {
  if (arg1 <= ui->doubleSpinBox_range_min->value())
    ui->doubleSpinBox_range_max->setValue(ui->doubleSpinBox_range_min->value() + 1);
}
