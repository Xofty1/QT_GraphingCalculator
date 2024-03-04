#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPixmap>
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>
#include <iostream>
extern "C" {
#include "parse.h"
#include "pol.h"
#include "validator.h"
}
#include <creditwindow.h>
#include <depositwindow.h>

#include <QPointF>
#include <cmath>  // Для использования std::isnan

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  QString expression = "";
  int cursorPos, cursorPosConst;
  void updateExpressions(const QString &symbol);
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_0_clicked();

  void on_pushButton_1_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_backSpace_clicked();

  void on_pushButton_clear_clicked();

  void on_pushButton_div_clicked();

  void on_pushButton_mult_clicked();

  void on_pushButton_minus_clicked();

  void on_pushButton_plus_clicked();

  void on_pushButton_res_clicked();

  void on_pushButton_bracketLeft_clicked();

  void on_pushButton_bracketRight_clicked();

  void on_pushButton_mod_clicked();

  void on_pushButton_sin_clicked();

  void on_pushButton_cos_clicked();

  void on_pushButton_tan_clicked();

  void on_pushButton_log_clicked();

  void on_pushButton_sqrt_clicked();

  void on_pushButton_asin_clicked();

  void on_pushButton_acos_clicked();

  void on_pushButton_atan_clicked();

  void on_pushButton_ln_clicked();

  void on_lineEdit_expression_textChanged();

  void on_pushButton_point_clicked();

  void on_lineEdit_expression_editingFinished();

  void on_radioButton_radian_clicked();

  void on_radioButton_degree_clicked();

  void on_pushButton_degree_clicked();

  void on_pushButton_plot_clicked();

  void on_pushButton_toCredit_clicked();

  void on_pushButton_toDeposit_clicked();

  void on_pushButton_x_clicked();

  void on_pushButton_whoami_clicked();

 private:
  Ui::MainWindow *ui;
  CreditWindow *creditWindow;
  DepositWindow *depositWindow;
};

#endif  // MAINWINDOW_H
