🎬 Movie Ticket Booking System
A console-based Movie Ticket Booking System developed in C++ using Object-Oriented Programming (OOP) and SOLID design principles.
The system allows users to browse movies and shows, check seat availability, book tickets, make payments using different methods, print tickets, and cancel confirmed bookings.

📌 Features
• List movies currently playing
• List shows with screen number and start time
• Display available/booked seats
• Book one or more seats
• Automatic ticket price calculation
• UPI, Card, and Cash payment options
• Failed payments release the selected seats
• Print ticket with booking details
• Cancel confirmed bookings
• Cancelled seats become available again
• Handle invalid seat numbers
• Handle duplicate seat selections
• Automatically generate unique booking IDs

💰 Seat Pricing
SILVER → ₹150
GOLD → ₹250
PLATINUM → ₹400

🏗️ Project Structure
main.cpp
Movie.cpp
Seat.cpp
Screen.cpp
Show.cpp
ShowSeat.cpp
Cinema.cpp
Customer.cpp
Booking.cpp
BookingService.cpp
Payment.cpp
UpiPayment.cpp
CardPayment.cpp
CashPayment.cpp
PriceCalculator.cpp
TicketPrinter.cpp
README.md

🧩 OOP Concepts Used
Encapsulation
Private data members are used and accessed through public methods.
Abstraction
The Payment class provides an abstract payment interface using a pure virtual function.
Inheritance
UpiPayment, CardPayment, and CashPayment inherit from the Payment class.
Runtime Polymorphism
Payment pointers/references are used to call the appropriate payment implementation at runtime.
Compile-Time Polymorphism
PriceCalculator demonstrates method overloading using calculateTotal().
Composition
Composition is used in relationships such as Cinema-Screen, Screen-Seat, and Show-ShowSeat.
Aggregation
Aggregation is used where objects maintain references to existing objects, such as Show-Movie and Booking-ShowSeat.
Association
Association is used between Customer, Booking, Show, and other related classes.

🏛️ SOLID Principles
Single Responsibility Principle:
Different classes have separate responsibilities such as movie management, seat management, price calculation, ticket printing, and booking management.
Open/Closed Principle:
New payment methods can be added by creating another Payment subclass without modifying the main booking logic.
Liskov Substitution Principle:
All payment subclasses can be used through the Payment interface.
Dependency Inversion Principle:
BookingService receives PriceCalculator and TicketPrinter through its constructor using Dependency Injection.

🔄 Booking Flow
Start → Select Show → Display Seats → Select Seats → Validate Seats → Reserve Seats → Calculate Total → Select Payment → Payment Successful? → Confirm Booking → Print Ticket
If payment fails:
Payment Failed → Release Seats → Cancel Booking
The system validates all requested seats before reserving them, preventing partial seat reservations.

💳 Payment Methods
UPI:
The user enters a UPI ID and confirms whether the payment was successful.
Card:
The user enters a card number. The system displays only the last four digits and asks for payment confirmation.
Cash:
The system asks whether the cash has been received.
If payment fails, the booking is not confirmed and all selected seats are released.

🎫 Ticket Details
The printed ticket contains:
• Booking ID
• Movie name
• Screen number
• Show time
• Selected seats
• Total amount
• Booking status

🎬 Sample Data
Cinema: PVR Cinema
Movies:
• Avengers — English — 180 minutes
• 3 Idiots — Hindi — 170 minutes
• Dangal — Hindi — 160 minutes
Seats:
• 1–5 → Silver
• 6–10 → Gold
• 11–15 → Platinum
Shows:
• Avengers → 10:00 AM
• Avengers → 06:00 PM
• 3 Idiots → 02:00 PM
• Dangal → 08:00 PM

🛠️ Technologies Used
Language: C++
Interface: Console / CLI
Compiler: G++
Concepts: OOP, SOLID Principles, Polymorphism, Composition, Aggregation, Association

⚙️ How to Run
Open the terminal in the project folder.
Compile:
g++ main.cpp -o movie_booking
Run on Linux/macOS:
./movie_booking
Run on Windows:
movie_booking.exe

⚠️ Project Scope
This project is intentionally designed as a small, single-cinema console-based system.
It currently does not include:
• Database
• GUI
• Real online payment gateway
• Multi-cinema support
• Online/cloud deployment

🚀 Future Improvements
• Database integration
• GUI or web interface
• User authentication
• Real payment gateway integration
• Multiple cinemas and locations
• Movie search and filtering
• Booking history
• Email/SMS ticket confirmation
• Admin dashboard
• REST API backend

👨‍💻 Project Information
Movie Ticket Booking System
B.Tech CSE – Semester 5
Subject: System Design
Subject Code: TCS-504
Developed for educational and academic purposes.
