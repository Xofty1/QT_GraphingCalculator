#ifndef CREDIT_H
#define CREDIT_H
int calculateAnnuity(double loanAmount, int loanTermMonths, double interestRate,
                     double *monthlyPayment, double *totalInterest,
                     double *totalPayment);
int calculateDifferentiated(double loanAmount, int loanTermMonths,
                            double interestRate, double *monthlyPayments,
                            double *totalInterest, double *totalPayment);
#endif  // CREDIT_H
