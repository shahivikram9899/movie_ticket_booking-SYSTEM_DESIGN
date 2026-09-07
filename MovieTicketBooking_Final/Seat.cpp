#include <iostream>
#include <string>
using namespace std;

// Encapsulation: seat data is private.
class Seat {
private:
    int number;
    string type;

public:
    static const int SILVER_PRICE = 150;
    static const int GOLD_PRICE = 250;
    static const int PLATINUM_PRICE = 400;

    Seat(int number, string type) {
        this->number = number;
        this->type = type;
    }

    int getNumber() const { return number; }
    string getType() const { return type; }

    int getPrice() const {
        if (type == "SILVER") return SILVER_PRICE;
        if (type == "GOLD") return GOLD_PRICE;
        return PLATINUM_PRICE;
    }
};
