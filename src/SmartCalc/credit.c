#include <math.h>
#include <stdio.h>

// Функция для расчета аннуитетного кредита
int calculateAnnuity(double loanAmount, int loanTermMonths, double interestRate,
                     double *monthlyPayment, double *totalInterest,
                     double *totalPayment) {
  // Проверка входных параметров
  if (loanAmount <= 0 || loanTermMonths <= 0 || interestRate <= 0 ||
      monthlyPayment == NULL || totalInterest == NULL || totalPayment == NULL) {
    return 1;  // Ошибка входных данных
  }

  // Расчет месячной процентной ставки
  double monthlyInterestRate = interestRate / 1200.0;
  // Расчет ежемесячного платежа по формуле аннуитета
  *monthlyPayment =
      loanAmount *
      (monthlyInterestRate * pow(1 + monthlyInterestRate, loanTermMonths)) /
      (pow(1 + monthlyInterestRate, loanTermMonths) - 1);

  // Расчет общей выплаты и переплаты
  *totalPayment = *monthlyPayment * loanTermMonths;
  *totalInterest = *totalPayment - loanAmount;

  return 0;  // Успешное выполнение
}

// Функция для расчета дифференцированного кредита
int calculateDifferentiated(double loanAmount, int loanTermMonths,
                            double interestRate, double *monthlyPayments,
                            double *totalInterest, double *totalPayment) {
  // Проверка входных параметров
  if (loanAmount <= 0 || loanTermMonths <= 0 || interestRate <= 0 ||
      monthlyPayments == NULL || totalInterest == NULL ||
      totalPayment == NULL) {
    return 1;  // Ошибка входных данных
  }

  // Расчет месячной процентной ставки
  double monthlyInterestRate = interestRate / 1200.0;

  // Расчет ежемесячных платежей
  for (int month = 1; month <= loanTermMonths; ++month) {
    double monthlyPayment =
        (loanAmount / loanTermMonths) +
        (loanAmount - (month - 1) * (loanAmount / loanTermMonths)) *
            monthlyInterestRate;
    monthlyPayments[month - 1] = monthlyPayment;
  }

  // Расчет общей выплаты и переплаты
  *totalPayment = 0;
  for (int month = 0; month < loanTermMonths; ++month) {
    *totalPayment += monthlyPayments[month];
  }

  *totalInterest = *totalPayment - loanAmount;

  return 0;  // Успешное выполнение
}
