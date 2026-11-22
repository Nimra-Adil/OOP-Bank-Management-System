#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include "Bank.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

class FileManager {

public:

    // save
    static void save(Account* acc, string type) {

        ofstream file("accounts.txt", ios::app);
        file << "Account Number: "<< acc->getAccNo() << endl;
        file << "Name: "<< acc->getName() << endl;
        file << "Balance: "<< acc->getBalance() << endl;
        file << "Type: "<< type << endl;
        file << "-------------------" << endl;

        file.close();
    }

    // load
    static void load(Bank &bank) {

    ifstream file("accounts.txt");

    int id;
    string name, label, type;
    double balance;

    while(file >> label >> label >> id >> label >> name>> label >> balance >> label >> type) {

        if(type == "Savings") {

            bank.add(new SavingsAccount(id, name, balance, 0.05));
        }
        else if(type == "Current") {

            bank.add(new CurrentAccount(id, name, balance));
        }
    }

    file.close();
}
};

#endif
