#ifndef BANK_H
#define BANK_H


#include "SavingsAccount.h"
#include "CurrentAccount.h"

class Bank {
    Account* accounts[100];
    int totalAccounts;

public:

    Bank() {
        totalAccounts = 0;
    }

    ~Bank() {
    	int i;
        for(i = 0; i < totalAccounts; i++) {
            delete accounts[i];
        }
    }

    void add(Account* acc) {
        if(totalAccounts >= 100)
            throw runtime_error("Bank capacity full");

        accounts[totalAccounts++] = acc;
    }

    Account* find(int id) {
    	int i;
        for(i = 0; i < totalAccounts; i++) {
            if(accounts[i]->getAccNo() == id)
                return accounts[i];
        }
        return nullptr;
    }

    void searchAccount(int id) {
        Account* acc = find(id);

        if(acc == nullptr) {
            cout << "Account not found\n";
            return;
        }

        acc->display();
    }

    void showAll() {

    if(totalAccounts == 0) {

        cout << "\nNo accounts available.\n";
        return;
    }

    for(int i = 0; i < totalAccounts; i++) {

        accounts[i]->display();
    }
}
};

#endif
