#include <iostream>
using namespace std;

class Booking;

class TicketPrinter {
public:
    void printTicket(const Booking& booking) const;
};
