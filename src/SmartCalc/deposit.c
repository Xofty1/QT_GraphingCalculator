#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <wchar.h>
// Функция для расчета суммы на вкладе к концу срока
void calculateDeposit(double initialDeposit, int depositTerm,
                      double interestRate, double taxRate, int paymentFrequency,
                      int term_r, int term_w, int capitalization,
                      double *earnedInterest, double *taxAmount,
                      double *finalAmount, double deposits,
                      double withdrawals) {
  // Инициализация переменных
  double balance = initialDeposit;  // Текущий баланс
  double totalInterest = 0.0;       // Начисленные проценты
  double totalTax = 0.0;            // Сумма налога
  double k = 12.0 / paymentFrequency;

  // Расчет процентов и налога для каждого периода
  for (int i = 0; i < depositTerm; ++i) {
    // Добавление пополнения, если оно есть

    if (term_r != 0 && (i + 1) % term_r == 0) {
      balance += deposits;
    }
    // Расчет процентов с учетом капитализации
    if (capitalization) {
      if (i % paymentFrequency == 0)
        balance += (balance * interestRate / (100.0 * k));
    } else {
      if (i % paymentFrequency == 0) {
        balance += (balance * interestRate / 100.0);
      }
    }

    // Вычет налога
    double taxableInterest = balance - initialDeposit;
    double currentTax = taxableInterest * taxRate / 100.0;
    totalTax += currentTax;

    // Обновление баланса
    balance -= currentTax;

    // Добавление частичного снятия, если оно есть
    if (term_w != 0 && (i + 1) % term_w == 0) {
      balance -= withdrawals;
    }

    // Обновление начисленных процентов
    totalInterest += (balance - initialDeposit - totalInterest - totalTax);
  }

  // Вывод результатов
  *earnedInterest = totalInterest;
  *taxAmount = totalTax;
  *finalAmount = balance;
}
