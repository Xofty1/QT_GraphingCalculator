#ifndef DEPOSIT_H
#define DEPOSIT_H
void calculateDeposit(double initialDeposit, int depositTerm,
                      double interestRate, double taxRate, int paymentFrequency,
                      int term_r, int term_w, int capitalization,
                      double *earnedInterest, double *taxAmount,
                      double *finalAmount, double deposits, double withdrawals);
#endif  // DEPOSIT_H
