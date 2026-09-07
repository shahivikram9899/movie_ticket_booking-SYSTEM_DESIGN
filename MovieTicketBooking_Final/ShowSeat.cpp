#include <iostream>
using namespace std;

class Seat;

class ShowSeat {
private:
    Seat* seat;
    bool booked;

public:
    ShowSeat(Seat* seat) {
        this->seat = seat;
        this->booked = false;
    }

    Seat* getSeat() const { return seat; }

    bool isAvailable() const {
        return !booked;
    }

    bool bookSeat() {
        if (booked) return false;
        booked = true;
        return true;
    }

    void cancelSeat() {
        booked = false;
    }

    void displayStatus() const;
};
