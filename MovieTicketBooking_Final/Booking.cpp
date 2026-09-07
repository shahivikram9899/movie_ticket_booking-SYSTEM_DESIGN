#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Customer;
class Show;
class ShowSeat;

class Booking {
private:
    static int nextBookingId;
    int bookingId;
    Customer* customer;          // Association
    Show* show;                  // Association
    vector<ShowSeat*> seats;     // Aggregation/reference to ShowSeat
    double totalAmount;
    string status;

public:
    Booking(Customer* customer, Show* show) {
        this->bookingId = nextBookingId++;
        this->customer = customer;
        this->show = show;
        this->totalAmount = 0;
        this->status = "PENDING";
    }

    int getBookingId() const { return bookingId; }
    Customer* getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    vector<ShowSeat*>& getSeats() { return seats; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    double getTotalAmount() const { return totalAmount; }
    string getStatus() const { return status; }

    void addSeat(ShowSeat* seat) {
        seats.push_back(seat);
    }

    void setTotalAmount(double amount) {
        totalAmount = amount;
    }

    void confirm() {
        status = "CONFIRMED";
    }

    void cancel() {
        status = "CANCELLED";
    }
};

// Static member: unique booking IDs.
int Booking::nextBookingId = 1001;
