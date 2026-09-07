#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// One class per file; no header files as required by the assignment.
#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"
#include "Cinema.cpp"

// ----- ShowSeat implementation -----

void ShowSeat::displayStatus() const {
    cout << "Seat " << seat->getNumber()
         << " [" << seat->getType() << "] - "
         << (booked ? "BOOKED" : "AVAILABLE") << endl;
}

// ----- Show implementation -----

void Show::createShowSeats() {
    for (const Seat& seat : screen->getSeats()) {
        showSeats.push_back(ShowSeat(
            const_cast<Seat*>(&seat)
        ));
    }
}

void Show::displaySeats() const {
    cout << "\n----------- SEAT LAYOUT -----------\n";
    for (const ShowSeat& showSeat : showSeats) {
        showSeat.displayStatus();
    }
}

// ----- PriceCalculator implementation -----

double PriceCalculator::calculateTotal(
    const vector<ShowSeat*>& seats) {

    double total = 0;

    for (ShowSeat* showSeat : seats) {
        total += showSeat->getSeat()->getPrice();
    }

    return total;
}

// ----- TicketPrinter implementation -----

void TicketPrinter::printTicket(
    const Booking& booking) const {

    cout << "\n========================================\n";
    cout << "                TICKET\n";
    cout << "========================================\n";

    cout << "Booking ID : "
         << booking.getBookingId() << endl;

    cout << "Movie      : "
         << booking.getShow()->getMovie()->getTitle()
         << endl;

    cout << "Screen     : "
         << booking.getShow()->getScreen()->getScreenNumber()
         << endl;

    cout << "Time       : "
         << booking.getShow()->getStartTime()
         << endl;

    cout << "Seats      : ";

    for (size_t i = 0;
         i < booking.getSeats().size(); i++) {

        cout << booking.getSeats()[i]
                    ->getSeat()->getNumber();

        if (i + 1 < booking.getSeats().size())
            cout << ", ";
    }

    cout << endl;

    cout << "Total      : Rs."
         << booking.getTotalAmount() << endl;

    cout << "Status     : "
         << booking.getStatus() << endl;

    cout << "========================================\n";
}

// ----- BookingService implementation -----

BookingService::~BookingService() {
    for (Booking* booking : bookings) {
        delete booking;
    }
}

Booking* BookingService::findBooking(
    int bookingId) const {

    for (Booking* booking : bookings) {
        if (booking->getBookingId() == bookingId)
            return booking;
    }

    return nullptr;
}

Booking* BookingService::book(
    Customer& customer,
    Show& show,
    const vector<int>& seatNumbers) {

    if (seatNumbers.empty()) {
        cout << "No seat selected.\n";
        return nullptr;
    }

    vector<ShowSeat*> selectedSeats;

    // Validate all requested seats first.
    for (int seatNumber : seatNumbers) {

        ShowSeat* selected = nullptr;

        for (ShowSeat& showSeat : show.getShowSeats()) {

            if (showSeat.getSeat()->getNumber()
                == seatNumber) {

                selected = &showSeat;
                break;
            }
        }

        if (selected == nullptr) {
            cout << "Invalid seat number: "
                 << seatNumber << endl;
            return nullptr;
        }

        if (!selected->isAvailable()) {
            cout << "Seat " << seatNumber
                 << " is already BOOKED.\n";
            return nullptr;
        }

        selectedSeats.push_back(selected);
    }

    // Reject duplicate seat numbers.
    for (size_t i = 0; i < selectedSeats.size(); i++) {
        for (size_t j = i + 1;
             j < selectedSeats.size(); j++) {

            if (selectedSeats[i]->getSeat()->getNumber()
                == selectedSeats[j]->getSeat()->getNumber()) {

                cout << "Duplicate seat selected: "
                     << selectedSeats[i]->getSeat()->getNumber()
                     << endl;
                return nullptr;
            }
        }
    }

    // Reserve seats only after complete validation.
    for (ShowSeat* seat : selectedSeats) {
        seat->bookSeat();
    }

    Booking* booking = new Booking(&customer, &show);

    for (ShowSeat* seat : selectedSeats) {
        booking->addSeat(seat);
    }

    double total =
        priceCalculator.calculateTotal(selectedSeats);

    booking->setTotalAmount(total);

    bookings.push_back(booking);

    cout << "\nSeats selected successfully.\n";
    cout << "Total Amount: Rs." << total << endl;

    return booking;
}

bool BookingService::makePayment(
    Booking& booking,
    Payment& payment) {

    if (booking.getStatus() != "PENDING") {
        cout << "Payment cannot be made for this booking.\n";
        return false;
    }

    bool paid = payment.pay(
        booking.getTotalAmount()
    );

    if (paid) {
        booking.confirm();
        cout << "\nPayment successful.\n";
        cout << "Booking confirmed.\n";
        return true;
    }

    // Failed payment -> release all seats.
    for (ShowSeat* seat : booking.getSeats()) {
        seat->cancelSeat();
    }

    booking.cancel();

    cout << "\nPayment failed.\n";
    cout << "Booking NOT confirmed.\n";
    cout << "Seats released.\n";

    return false;
}

bool BookingService::cancelBooking(
    int bookingId) {

    Booking* booking = findBooking(bookingId);

    if (booking == nullptr) {
        cout << "Booking ID not found.\n";
        return false;
    }

    if (booking->getStatus() != "CONFIRMED") {
        cout << "Only a confirmed booking can be cancelled.\n";
        return false;
    }

    for (ShowSeat* seat : booking->getSeats()) {
        seat->cancelSeat();
    }

    booking->cancel();

    cout << "Booking " << bookingId
         << " cancelled successfully.\n";

    cout << "Seats are AVAILABLE again.\n";

    return true;
}

void BookingService::printTicket(
    int bookingId) const {

    Booking* booking = findBooking(bookingId);

    if (booking == nullptr) {
        cout << "Booking ID not found.\n";
        return;
    }

    ticketPrinter.printTicket(*booking);
}

// ----- Menu helpers -----

Show* findShow(Cinema& cinema, int showId) {
    for (Show& show : cinema.getShows()) {
        if (show.getShowId() == showId)
            return &show;
    }

    return nullptr;
}

void listMovies(Cinema& cinema) {
    cout << "\n----------- MOVIES -----------\n";

    int number = 1;

    for (Movie& movie : cinema.getMovies()) {
        cout << number++ << ". ";
        movie.display();
    }
}

void listShows(Cinema& cinema) {
    cout << "\n----------- SHOWS -----------\n";

    for (Show& show : cinema.getShows()) {

        cout << "Show ID: " << show.getShowId()
             << " | Movie: "
             << show.getMovie()->getTitle()
             << " | Screen: "
             << show.getScreen()->getScreenNumber()
             << " | Start Time: "
             << show.getStartTime()
             << endl;
    }
}

void showSeats(Cinema& cinema) {
    int showId;

    cout << "Enter Show ID: ";
    cin >> showId;

    Show* show = findShow(cinema, showId);

    if (show == nullptr) {
        cout << "Invalid Show ID.\n";
        return;
    }

    cout << "\nMovie: "
         << show->getMovie()->getTitle() << endl;

    cout << "Screen: "
         << show->getScreen()->getScreenNumber() << endl;

    cout << "Start Time: "
         << show->getStartTime() << endl;

    show->displaySeats();
}

void bookTicket(
    Cinema& cinema,
    BookingService& bookingService) {

    string name;
    string phone;
    int showId;
    int seatCount;

    cout << "\nCustomer Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Phone: ";
    getline(cin, phone);

    Customer customer(name, phone);

    cout << "Enter Show ID: ";
    cin >> showId;

    Show* show = findShow(cinema, showId);

    if (show == nullptr) {
        cout << "Invalid Show ID.\n";
        return;
    }

    cout << "How many seats do you want to book? ";
    cin >> seatCount;

    if (seatCount <= 0) {
        cout << "Invalid number of seats.\n";
        return;
    }

    vector<int> seatNumbers;

    for (int i = 0; i < seatCount; i++) {
        int seatNumber;

        cout << "Enter seat number "
             << i + 1 << ": ";
        cin >> seatNumber;

        seatNumbers.push_back(seatNumber);
    }

    Booking* booking =
        bookingService.book(
            customer,
            *show,
            seatNumbers
        );

    if (booking == nullptr)
        return;

    int paymentChoice;

    cout << "\n----------- PAYMENT -----------\n";
    cout << "1. UPI\n";
    cout << "2. Card\n";
    cout << "3. Cash\n";
    cout << "Enter payment method: ";
    cin >> paymentChoice;

    Payment* payment = nullptr;

    if (paymentChoice == 1) {

        string upiId;

        cout << "Enter UPI ID: ";
        cin >> upiId;

        payment = new UpiPayment(upiId);

    } else if (paymentChoice == 2) {

        string cardNumber;

        cout << "Enter Card Number: ";
        cin >> cardNumber;

        payment = new CardPayment(cardNumber);

    } else if (paymentChoice == 3) {

        payment = new CashPayment();

    } else {

        cout << "Invalid payment choice.\n";

        for (ShowSeat* seat : booking->getSeats()) {
            seat->cancelSeat();
        }

        booking->cancel();

        delete payment;
        return;
    }

    // Runtime polymorphism.
    bool successful =
        bookingService.makePayment(
            *booking,
            *payment
        );

    delete payment;

    if (successful) {
        bookingService.printTicket(
            booking->getBookingId()
        );
    }
}

void cancelTicket(
    BookingService& bookingService) {

    int bookingId;

    cout << "Enter Booking ID: ";
    cin >> bookingId;

    bookingService.cancelBooking(bookingId);
}

int main() {

    // ----------------------------------
    // Cinema setup
    // ----------------------------------

    Cinema cinema("PVR Cinema");

    Movie movie1("Avengers", "English", 180);
    Movie movie2("3 Idiots", "Hindi", 170);
    Movie movie3("Dangal", "Hindi", 160);

    cinema.addMovie(movie1);
    cinema.addMovie(movie2);
    cinema.addMovie(movie3);

    Screen screen1(1);

    // Silver: 1-5
    for (int i = 1; i <= 5; i++) {
        screen1.addSeat(
            Seat(i, "SILVER")
        );
    }

    // Gold: 6-10
    for (int i = 6; i <= 10; i++) {
        screen1.addSeat(
            Seat(i, "GOLD")
        );
    }

    // Platinum: 11-15
    for (int i = 11; i <= 15; i++) {
        screen1.addSeat(
            Seat(i, "PLATINUM")
        );
    }

    cinema.addScreen(screen1);

    Show show1(
        1,
        &cinema.getMovies()[0],
        &cinema.getScreens()[0],
        "10:00 AM"
    );

    Show show2(
        2,
        &cinema.getMovies()[0],
        &cinema.getScreens()[0],
        "06:00 PM"
    );

    Show show3(
        3,
        &cinema.getMovies()[1],
        &cinema.getScreens()[0],
        "02:00 PM"
    );

    Show show4(
        4,
        &cinema.getMovies()[2],
        &cinema.getScreens()[0],
        "08:00 PM"
    );

    show1.createShowSeats();
    show2.createShowSeats();
    show3.createShowSeats();
    show4.createShowSeats();

    cinema.addShow(show1);
    cinema.addShow(show2);
    cinema.addShow(show3);
    cinema.addShow(show4);

    // Dependency Injection for BookingService.
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

    BookingService bookingService(
        priceCalculator,
        ticketPrinter
    );

    // ----------------------------------
    // Main Menu
    // ----------------------------------

    int choice;

    do {
        cout << "\n========================================\n";
        cout << "       MOVIE TICKET BOOKING SYSTEM\n";
        cout << "========================================\n";
        cout << "1. List all movies\n";
        cout << "2. List shows for a movie\n";
        cout << "3. Display seat layout\n";
        cout << "4. Book ticket\n";
        cout << "5. Print ticket\n";
        cout << "6. Cancel booking\n";
        cout << "7. Exit\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            listMovies(cinema);
            break;

        case 2:
            listShows(cinema);
            break;

        case 3:
            showSeats(cinema);
            break;

        case 4:
            bookTicket(
                cinema,
                bookingService
            );
            break;

        case 5: {
            int bookingId;

            cout << "Enter Booking ID: ";
            cin >> bookingId;

            bookingService.printTicket(
                bookingId
            );

            break;
        }

        case 6:
            cancelTicket(
                bookingService
            );
            break;

        case 7:
            cout << "\nThank you for using "
                 << "Movie Ticket Booking System.\n";
            break;

        default:
            // Invalid menu choice is handled without crashing.
            cout << "Invalid menu choice. "
                 << "Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
