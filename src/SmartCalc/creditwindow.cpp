#include "creditwindow.h"

#include "ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
  setWindowTitle("Кредитный калькулятор");
  ui->comboBox_credittype->activated(0);
  ui->comboBox_temp->activated(0);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_pushButton_toMain_clicked() {
  this->close();  // Закрываем окно
  emit mainWindow();
}

void CreditWindow::on_pushButton_calculate_clicked() {
  bool ok = true;
  bool conversionError = false;
  if (ui->lineEdit_totalS->text() == "") ui->lineEdit_totalS->setText("0");
  double total = ui->lineEdit_totalS->text().toDouble(&ok);
  conversionError |= !ok;
  if (ui->lineEdit_percent->text() == "") ui->lineEdit_percent->setText("0");
  double percent = ui->lineEdit_percent->text().toDouble(&ok);
  conversionError |= !ok;
  int term = ui->spinBox_term->text().toInt(&ok);
  conversionError |= !ok;

  double payment, overpayment, totalP;
  if (conversionError) {
    QMessageBox::information(nullptr, "Ошибка",
                             "Введены некорректные значения");
  } else {
    if (ui->comboBox_temp->currentIndex() == 1) {
      term *= 12;
    }
    if (ui->comboBox_credittype->currentIndex() == 0) {
      ui->listWidget_diff_payout->setVisible(false);
      ui->listWidget_diff_payout->clear();
      if (calculateAnnuity(total, term, percent, &payment, &overpayment,
                           &totalP) == 0) {
        ui->label_payment_res->setText(QString::number(payment, 'f', 2) +
                                       "₽");
        ui->label_overpayment_res->setText(
            QString::number(overpayment, 'f', 2) + "₽");
        ui->label_total_payout_res->setText(QString::number(totalP, 'f', 2) +
                                            "₽");
      } else {
        QMessageBox::information(nullptr, "Ошибка",
                                 "Введены некорректные значения");
      }
    } else {
      double *payment_arr = new double[term];
      if (calculateDifferentiated(total, term, percent, payment_arr,
                                  &overpayment, &totalP) == 0) {
        ui->listWidget_diff_payout->clear();
        ui->listWidget_diff_payout->setVisible(true);

        for (int i = 0; i < term; ++i) {
          ui->listWidget_diff_payout->addItem(
              QString::number(i + 1) + " выплата - " +
              QString::number(payment_arr[i]) + "₽");
        }
        ui->label_payment_res->setText(
            QString::number(payment_arr[0], 'f', 3) + "₽  ..  " +
            QString::number(payment_arr[term - 1], 'f', 2) + "₽");
        ui->label_overpayment_res->setText(
            QString::number(overpayment, 'f', 3) + "₽");
        ui->label_total_payout_res->setText(QString::number(totalP, 'f', 3) +
                                            "₽");
      } else {
        QMessageBox::information(nullptr, "Ошибка",
                                 "Введены некорректные значения");
      }
      delete[] payment_arr;
    }
  }
}

void CreditWindow::on_comboBox_credittype_activated(int index) {
  if (index == 0) {
    ui->listWidget_diff_payout->setVisible(false);
    ui->listWidget_diff_payout->clear();
  }
}
