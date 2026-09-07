#include <iostream>
using namespace std;

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "\nCash Payment\n";
        cout << "Amount: Rs." << amount << endl;

        char choice;
        cout << "Cash received? (y/n): ";
        cin >> choice;

        return choice == 'y' || choice == 'Y';
    }
};
