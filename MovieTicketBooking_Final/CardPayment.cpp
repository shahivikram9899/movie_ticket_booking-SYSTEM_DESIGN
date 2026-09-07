#include <iostream>
#include <string>
using namespace std;

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(string cardNumber) {
        this->cardNumber = cardNumber;
    }

    bool pay(double amount) override {
        cout << "\nCard Payment\n";
        cout << "Amount: Rs." << amount << endl;

        if (cardNumber.length() < 4) {
            cout << "Invalid card number.\n";
            return false;
        }

        cout << "Card: ****"
             << cardNumber.substr(cardNumber.length() - 4)
             << endl;

        char choice;
        cout << "Payment successful? (y/n): ";
        cin >> choice;

        return choice == 'y' || choice == 'Y';
    }
};
