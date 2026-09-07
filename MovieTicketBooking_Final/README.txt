MOVIE TICKET BOOKING SYSTEM
System Design - Assignment 1
B.Tech CSE Semester 5
Subject Code: TCS-504

REQUIREMENTS IMPLEMENTED
1. List movies currently playing.
2. List shows with screen and start time.
3. Display AVAILABLE / BOOKED seats.
4. Book one or more seats.
5. SILVER = Rs.150, GOLD = Rs.250, PLATINUM = Rs.400.
6. UPI, Card and Cash payment.
7. Failed payment does not confirm booking and releases seats.
8. Print ticket with booking ID, movie, screen, time, seats and total amount.
9. Cancel confirmed booking and make seats AVAILABLE again.
10. Invalid menu choices, invalid seats and duplicate seats are handled.

OOP CONCEPTS
- Encapsulation: private data members and public methods.
- Abstraction: abstract Payment class.
- Inheritance: UpiPayment, CardPayment and CashPayment inherit Payment.
- Runtime polymorphism: Payment* / Payment& calls pay().
- Compile-time polymorphism: overloaded PriceCalculator::calculateTotal().
- Static member: Booking::nextBookingId.
- this keyword: constructors.
- Composition: Cinema-Screen, Screen-Seat, Show-ShowSeat.
- Aggregation: Show-Movie and Booking-ShowSeat references.
- Association: Customer/BookingService and Booking references.

SOLID
- Single Responsibility: separate Movie, Seat, Payment, PriceCalculator, TicketPrinter and BookingService responsibilities.
- Open/Closed: a new Payment subclass can be added without changing BookingService.
- Liskov Substitution: every Payment subclass can be used through Payment.
- Dependency Inversion: BookingService receives PriceCalculator and TicketPrinter through its constructor.

INTENTIONALLY NOT DONE
- No database, GUI, online gateway or multi-cinema support is added because the assignment scope says to build exactly the small single-cinema console system.

COMPILATION
Open terminal in this folder and run:

g++ main.cpp -o movie_booking

Then:

Windows:
movie_booking.exe

Linux/macOS:
./movie_booking

IMPORTANT
The assignment says one class per file and no header files. Therefore main.cpp includes the .cpp class files directly.
