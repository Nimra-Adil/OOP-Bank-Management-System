#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include<stdexcept>
#include<fstream>
#include "Transaction.h"
using namespace std;

class Account {
protected:
    int accNo;
    string name;
    double balance;
    Transaction history[100];
    int totalTransactions = 0;

public:
    Account(int a, string n, double b) : accNo(a), name(n), balance(b) {}

   virtual void deposit(double amount) {

    if(amount <= 0)
        throw invalid_argument("Invalid deposit");

    balance += amount;

    history[totalTransactions] = Transaction("Deposit", amount);

    totalTransactions++;
    
    saveTransaction("Deposit", amount);
}

    virtual void withdraw(double amount) {
        if(amount > balance) 
		throw runtime_error("Insufficient balance");
		
        balance -= amount;
        history[totalTransactions] =
    Transaction("Withdraw", amount);

    totalTransactions++;
    saveTransaction("Withdraw", amount);
    }

    // operator overloading for transfer
    void operator>>(Account &to) {
        double amount;
        cout << "Enter amount to transfer: ";
        cin >> amount;

        if(amount > balance) 
		throw runtime_error("Transfer failed");

        this->balance -= amount;
        to.balance += amount;

        history[totalTransactions] =
        Transaction("Transfer Out", amount);

        totalTransactions++;
        to.history[to.totalTransactions] =
        Transaction("Transfer In", amount);

        to.totalTransactions++;

        saveTransaction("TransferOut", amount);

        to.saveTransaction("TransferIn", amount);
    }

    int getAccNo() const { 
	return accNo; 
	}
	
    double getBalance() const { 
	return balance; 
	}

    string getName() const {
	return name;
    }

    void saveTransaction(string type, double amount) {

    ofstream file("transactions.txt", ios::app);
    file << "---------------------------------\n";
    file << "Account Number : "<< accNo << endl;
    file << "Transaction    : "<< type << endl;
    file << "Amount         : "<< amount << endl;
    file << "-----------------------------------\n\n";

    file.close();
}

    void showHistory() {
    	int i;
        for(i = 0; i < totalTransactions; i++) {
        	
    history[i].show();
    }
	}

    virtual void calculateInterest() = 0; // pure virtual

    virtual void display() {
        cout << accNo << " | " << name << " | " << balance << endl;
    }

    friend void detectFraud(Account &acc);

    virtual ~Account() {}
};

#endif
