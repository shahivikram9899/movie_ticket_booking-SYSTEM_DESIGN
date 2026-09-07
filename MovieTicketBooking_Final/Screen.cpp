#include <iostream>
#include <vector>
using namespace std;

class Seat;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats; // Composition: Screen owns its seats.

public:
    Screen(int screenNumber) {
        this->screenNumber = screenNumber;
    }

    void addSeat(const Seat& seat) {
        seats.push_back(seat);
    }

    int getScreenNumber() const {
        return screenNumber;
    }

    const vector<Seat>& getSeats() const {
        return seats;
    }
};
