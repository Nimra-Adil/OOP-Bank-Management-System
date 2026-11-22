#ifndef CURRENT_H
#define CURRENT_H

#include "Account.h"

class CurrentAccount : public Account {

private:
    double overdraftLimit;
    double overdraftUsed;
    double fee;

public:

    CurrentAccount(int a, string n, double b, double limit = 5000, double f = 50) : Account(a, n, b), overdraftLimit(limit), overdraftUsed(0), fee(f) {}

    void withdraw(double amount) override {

        if(amount <= 0)
            throw runtime_error("Invalid amount");

        double total = amount + fee;
        double available = balance + (overdraftLimit - overdraftUsed);

        if(total > available)
            throw runtime_error("Overdraft limit exceeded");

        double remaining = total;

        if(balance >= remaining) {
            balance -= remaining;
        }
        else {
            remaining -= balance;
            balance = 0;
            overdraftUsed += remaining;
        }

        history[totalTransactions++] =
            Transaction("Withdraw + Fee", total);

        saveTransaction("Withdraw+Fee", total);

        cout << "\nWithdrawal successful.\n";
    }

    void deposit(double amount) override {

        if(amount <= 0)
            throw runtime_error("Invalid deposit");

        double original = amount;

        if(overdraftUsed > 0) {

            if(amount >= overdraftUsed) {
                amount -= overdraftUsed;
                overdraftUsed = 0;
            }
            else {
                overdraftUsed -= amount;
                amount = 0;
            }
        }

        balance += amount;

        history[totalTransactions++] =
            Transaction("Deposit", original);

        saveTransaction("Deposit", original);

        cout << "\nDeposit successful.\n";
    }

    void calculateInterest() override {
        //no interest for current account
    }

    void display() override {

        cout << "\n[CURRENT ACCOUNT]\n";
        Account::display();

        cout << "Overdraft Limit : " << overdraftLimit << endl;
        cout << "Overdraft Used  : " << overdraftUsed << endl;
        cout << "Available Credit: "
             << (overdraftLimit - overdraftUsed) << endl;
    }
};

#endif
