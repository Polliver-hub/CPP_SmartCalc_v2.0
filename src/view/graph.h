#ifndef GRAPH_H
#define GRAPH_H

#include <QChart>
#include <QChartView>
#include <QDialog>
#include <QLogValueAxis>
#include <QScreen>
#include <QSplineSeries>
#include <QValueAxis>
#include <cmath>

namespace Ui {
class graph;
}

class graph : public QDialog {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();

 private:
  Ui::graph *ui;
  QLineSeries *series1;
  QChart *chart;
  QChartView *chartView;
  QValueAxis *axisX;
  QValueAxis *axisY;

 public slots:
  void Print(const char *str_in1, double *ranges);
};

#endif  // GRAPH_H
