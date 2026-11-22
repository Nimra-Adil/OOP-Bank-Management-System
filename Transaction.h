#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <ctime>

using namespace std;

class Transaction {

    string type;
    double amount;
    string timestamp;

public:

    // DEFAULT CONSTRUCTOR
    Transaction() {
        type = "";
        amount = 0;
        timestamp = "";
    }

    // PARAMETERIZED CONSTRUCTOR
    Transaction(string t, double a) {
	type = t;
    amount = a;

    time_t now = time(0);
    string raw = ctime(&now);
    raw.pop_back(); // removes newline

    timestamp = "[" + raw + "]";
}

    void show() const {

        cout << type
             << " | "
             << amount
             << " | "
             << timestamp;
    }
};

#endif
