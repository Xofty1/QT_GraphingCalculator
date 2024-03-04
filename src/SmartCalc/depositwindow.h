#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QMessageBox>
#include <QWidget>
#include <iostream>
extern "C" {
#include "deposit.h"
}

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QWidget {
  Q_OBJECT

 public:
  int paymentFrequency = 1, term_r = 0, term_w = 0;
  explicit DepositWindow(QWidget *parent = nullptr);
  ~DepositWindow();
 signals:
  void mainWindow();
 private slots:
  void on_pushButton_toMain_clicked();

  void on_pushButton_calculate_clicked();

  void on_comboBox_cap_activated(int index);

  void on_comboBox_periodicity_rep_activated(int index);

  void on_comboBox_periodicity_wit_activated(int index);

  void on_checkBox_capitalization_stateChanged(int arg1);

 private:
  Ui::DepositWindow *ui;
};

#endif  // DEPOSITWINDOW_H
