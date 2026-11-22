#include "Bank.h"
#include "FileManager.h"
#include "Login.h"

void detectFraud(Account &acc) {

    if(acc.getBalance() > 1000000) {
        cout << "\nFRAUD ALERT!\n";
        cout << "Account: " << acc.getAccNo() << endl;
        cout << "Balance: " << acc.getBalance() << endl;
    }
    else {
        cout << "\nNo fraud detected.\n";
    }
}

Account* safeFind(Bank &bank, int id) {

    Account* acc = bank.find(id);

    if(!acc)
        throw runtime_error("Account not found");

    return acc;
}

int main() {
    if(!Login::authenticate()) {
    return 0;
	}
    
    Bank bank;
    FileManager::load(bank);

    int choice;

    do {

        cout << "\n----- BANK SYSTEM -----\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Show Accounts\n";
        cout << "6. Fraud Check\n";
        cout << "7. Search\n";
        cout << "8. Interest\n";
        cout << "9. View Transaction History\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        try {

            switch(choice) {

            case 1: {
                int id, type;
                string name;
                double bal;

                cout << "1. Savings\n2. Current\n";
                cin >> type;

                cout << "ID: "; cin >> id;
                cout << "Name: "; cin >> name;
                cout << "Balance: "; cin >> bal;

                Account* acc = nullptr;

                if(type == 1)
                    acc = new SavingsAccount(id, name, bal, 0.05);
                else if(type == 2)
                    acc = new CurrentAccount(id, name, bal);
                else
                    throw runtime_error("Invalid type");

                bank.add(acc);

                cout << "Account created.\n";
                break;
            }

            case 2: {
			int id;
			double amt;
			 cout << "Enter Account ID: ";
            cin >> id;

            cout << "Enter Deposit Amount: ";
            cin >> amt;

            Account* acc = safeFind(bank, id);

            acc->deposit(amt);
			cout << "Deposit done.\n";
			break;
			}

            case 3: {
                int id; double amt;
                cin >> id >> amt;

                Account* acc = safeFind(bank, id);
                acc->withdraw(amt);

                cout << "Withdraw done.\n";
                break;
            }

            case 4: {
                int a,b;
                cin >> a >> b;

                Account* from = safeFind(bank, a);
                Account* to = safeFind(bank, b);

                *from >> *to;

                cout << "Transfer done.\n";
                break;
            }

            case 5:
                bank.showAll();
                break;

            case 6: {
                int id; cin >> id;
                detectFraud(*safeFind(bank, id));
                break;
            }

            case 7: {
                int id; 
				cin >> id;
                bank.searchAccount(id);
                break;
            }

            case 8: {
                int id; cin >> id;
                Account* acc = safeFind(bank, id);
                acc->calculateInterest();
                cout << "Interest applied.\n";
                break;
            }
            
            case 9: {
			int id;
			cout << "Enter Account ID: ";
			cin >> id;
			Account* acc = bank.find(id);
			if(acc == nullptr)
			throw runtime_error("Account not found");
			cout << "\n----- TRANSACTION HISTORY -----\n";
			acc->showHistory();
			break;
			}
			
            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
            }

        } catch(exception &e) {
            cout << "Error: " << e.what() << endl;
        }

    } while(choice != 0);

    return 0;
}
