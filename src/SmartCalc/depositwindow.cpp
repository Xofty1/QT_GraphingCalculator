#include "depositwindow.h"

#include "ui_depositwindow.h"

DepositWindow::DepositWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositWindow) {
  ui->setupUi(this);
  setWindowTitle("Депозитный калькулятор");
  ui->comboBox_periodicity_rep->activated(0);
  ui->comboBox_periodicity_wit->activated(0);
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::on_pushButton_toMain_clicked() {
  this->close();
  emit mainWindow();
}

void DepositWindow::on_pushButton_calculate_clicked() {
  bool ok = true;
  bool conversionError = false;
  if (ui->lineEdit_totalS->text() == "") ui->lineEdit_totalS->setText("0");
  double initialDeposit = ui->lineEdit_totalS->text().toDouble(&ok);
  conversionError |= !ok;
  if (ui->lineEdit_percent->text() == "") ui->lineEdit_percent->setText("0");
  double interestRate = ui->lineEdit_percent->text().toDouble(&ok);
  conversionError |= !ok;
  int depositTerm = ui->spinBox_term->text().toInt(&ok);
  conversionError |= !ok;
  if (ui->lineEdit_percent_tax->text() == "")
    ui->lineEdit_percent_tax->setText("0");
  int taxRate = ui->lineEdit_percent_tax->text().toInt(&ok);
  conversionError |= !ok;
  double deposits = ui->lineEdit_replenishment->text().toDouble(&ok);
  conversionError |= !ok;
  double withdrawals = ui->lineEdit_withdrawal->text().toDouble(&ok);
  conversionError |= !ok;
  int capitalization = ui->checkBox_capitalization->isChecked();
  if (conversionError) {
    QMessageBox::information(nullptr, "Ошибка",
                             "Введены некорректные значения");
  } else {
    if (ui->comboBox_term->currentIndex() == 1) {
      depositTerm *= 12;
    }
    double earnedInterest, taxAmount, finalAmount;
    calculateDeposit(initialDeposit, depositTerm, interestRate, taxRate,
                     paymentFrequency, term_r, term_w, capitalization,
                     &earnedInterest, &taxAmount, &finalAmount, deposits,
                     withdrawals);
    ui->label_total_percent_res->setText(
        QString::number(earnedInterest, 'f', 3) + "₽");
    ui->label_total_tax_res->setText(QString::number(taxAmount, 'f', 3) +
                                     "₽");
    ui->label_total_res->setText(QString::number(finalAmount, 'f', 3) + "₽");
  }
}

void DepositWindow::on_comboBox_cap_activated(int index) {
  switch (index) {
    case 0:
      paymentFrequency = 1;
      break;
    case 1:
      paymentFrequency = 2;
      break;
    case 2:
      paymentFrequency = 3;
      break;
    case 3:
      paymentFrequency = 4;
      break;
    case 4:
      paymentFrequency = 5;
      break;
    case 5:
      paymentFrequency = 12;
      break;
  }
}
void DepositWindow::on_comboBox_periodicity_rep_activated(int index) {
  switch (index) {
    case 0:
      ui->label_replenishment->setVisible(false);
      ui->lineEdit_replenishment->setVisible(false);
      ui->lineEdit_replenishment->setText("0");
      term_r = 0;
      break;
    case 1:
      term_r = 1;
      ui->label_replenishment->setVisible(true);
      ui->lineEdit_replenishment->setVisible(true);
      break;
    case 2:
      term_r = 2;
      ui->label_replenishment->setVisible(true);
      ui->lineEdit_replenishment->setVisible(true);
      break;
    case 3:
      ui->label_replenishment->setVisible(true);
      ui->lineEdit_replenishment->setVisible(true);
      term_r = 3;
      break;
    case 4:
      ui->label_replenishment->setVisible(true);
      ui->lineEdit_replenishment->setVisible(true);
      term_r = 4;
      break;
    case 5:
      ui->label_replenishment->setVisible(true);
      ui->lineEdit_replenishment->setVisible(true);
      term_r = 6;
      break;
    case 6:
      ui->label_replenishment->setVisible(true);
      ui->lineEdit_replenishment->setVisible(true);
      term_r = 12;
      break;
  }
}

void DepositWindow::on_comboBox_periodicity_wit_activated(int index) {
  switch (index) {
    case 0:
      ui->label_withdrawal->setVisible(false);
      ui->lineEdit_withdrawal->setVisible(false);
      ui->lineEdit_withdrawal->setText("0");
      term_w = 0;
      break;
    case 1:
      term_w = 1;
      ui->label_withdrawal->setVisible(true);
      ui->lineEdit_withdrawal->setVisible(true);
      break;
    case 2:
      term_w = 2;
      ui->label_withdrawal->setVisible(true);
      ui->lineEdit_withdrawal->setVisible(true);
      break;
    case 3:
      ui->label_withdrawal->setVisible(true);
      ui->lineEdit_withdrawal->setVisible(true);
      term_w = 3;
      break;
    case 4:
      ui->label_withdrawal->setVisible(true);
      ui->lineEdit_withdrawal->setVisible(true);
      term_w = 4;
      break;
    case 5:
      ui->label_withdrawal->setVisible(true);
      ui->lineEdit_withdrawal->setVisible(true);
      term_w = 6;
      break;
    case 6:
      ui->label_withdrawal->setVisible(true);
      ui->lineEdit_withdrawal->setVisible(true);
      term_w = 12;
      break;
  }
}

void DepositWindow::on_checkBox_capitalization_stateChanged(int arg1) {
  if (arg1 == 0)
    ui->label_periodicity_cap->setText("Переодичность выплат");

  else
    ui->label_periodicity_cap->setText("Переодичность капитализации");
}
