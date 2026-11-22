#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
using namespace std;

class Login {

public:

    static bool authenticate() {

        string username;
        string password;

        cout << "------ LOGIN -----\n";

        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        if(username == "admin" && password == "1234") {

            cout << "\nLogin Successful!\n";
            return true;
        }

        cout << "\nInvalid Credentials!\n";
        return false;
    }
};

#endif
