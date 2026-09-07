#include <vector>
using namespace std;

class ShowSeat;

class PriceCalculator {
public:
    double calculateTotal(const vector<ShowSeat*>& seats);

    // Compile-time polymorphism: overloaded method.
    double calculateTotal(double amount) {
        return amount;
    }
};
