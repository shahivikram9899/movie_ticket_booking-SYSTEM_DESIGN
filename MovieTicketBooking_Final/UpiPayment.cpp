#include <iostream>
#include <string>
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(string upiId) {
        this->upiId = upiId;
    }

    bool pay(double amount) override {
        cout << "\nUPI Payment\n";
        cout << "UPI ID: " << upiId << endl;
        cout << "Amount: Rs." << amount << endl;

        char choice;
        cout << "Payment successful? (y/n): ";
        cin >> choice;

        return choice == 'y' || choice == 'Y';
    }
};
