#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QMessageBox>
#include <QWidget>
extern "C" {
#include "credit.h"
}

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QWidget {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();
 signals:
  void mainWindow();
 private slots:
  void on_pushButton_toMain_clicked();

  void on_pushButton_calculate_clicked();

  void on_comboBox_credittype_activated(int index);

 private:
  Ui::CreditWindow *ui;
};

#endif  // CREDITWINDOW_H
