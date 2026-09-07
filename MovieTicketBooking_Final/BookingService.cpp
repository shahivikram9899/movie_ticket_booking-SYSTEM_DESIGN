#include <iostream>
#include <vector>
using namespace std;

class Customer;
class Show;
class ShowSeat;
class Booking;
class Payment;
class PriceCalculator;
class TicketPrinter;

class BookingService {
private:
    PriceCalculator& priceCalculator;
    TicketPrinter& ticketPrinter;
    vector<Booking*> bookings;

public:
    // Dependency Injection: BookingService receives its dependencies.
    BookingService(PriceCalculator& priceCalculator,
                   TicketPrinter& ticketPrinter)
        : priceCalculator(priceCalculator),
          ticketPrinter(ticketPrinter) {}

    ~BookingService();

    Booking* book(Customer& customer, Show& show,
                  const vector<int>& seatNumbers);

    bool makePayment(Booking& booking, Payment& payment);

    bool cancelBooking(int bookingId);

    Booking* findBooking(int bookingId) const;

    void printTicket(int bookingId) const;
};
