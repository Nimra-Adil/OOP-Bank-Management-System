#ifndef SAVINGS_H
#define SAVINGS_H

#include "Account.h"

class SavingsAccount : public Account {

    double interestRate;

public:

    SavingsAccount(int a, string n, double b, double r)
        : Account(a, n, b), interestRate(r) {}

    void deposit(double amount) override {

        Account::deposit(amount);

        cout << "\nDeposit successful in Savings Account.\n";
    }

    void withdraw(double amount) override {

        Account::withdraw(amount);

        cout << "\nWithdrawal successful from Savings Account.\n";
    }

    void calculateInterest() override {

        if(balance <= 0)
            throw runtime_error("No interest on zero/negative balance");

        double interest = balance * interestRate;
        balance += interest;

        history[totalTransactions++] =
            Transaction("Interest", interest);

        saveTransaction("Interest", interest);

        cout << "\nInterest applied: " << interest << endl;
    }

    void display() override {

        cout << "\n[SAVINGS ACCOUNT]\n";
        Account::display();
    }
};

#endif
