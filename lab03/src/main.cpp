#include <iostream>
#include "MovieTicket.hpp"

int main() {
    // ------------------------------------------------------------------
    // 1. Create an initial ticket: Hall 3, Seat 15, price 120.0,
    //    not booked, 95-minute movie.
    // ------------------------------------------------------------------
    MovieTicket ticket(3, 15, 120.0, false, 95);

    std::cout << "=== Initial ticket state ===\n";
    std::cout << "Hall number    : " << ticket.getHallNumber()      << '\n';
    std::cout << "Seat number    : " << ticket.getSeatNumber()       << '\n';
    std::cout << "Price          : " << ticket.getPrice()            << '\n';
    std::cout << "Booked         : " << (ticket.getBooked() ? "yes" : "no") << '\n';
    std::cout << "Duration (min) : " << ticket.getDurationMinutes()  << '\n';
    std::cout << "Premium        : " << (ticket.isPremium()    ? "yes" : "no") << '\n';
    std::cout << "Long movie     : " << (ticket.isLongMovie()  ? "yes" : "no") << '\n';

    // ------------------------------------------------------------------
    // 2. Book the ticket and try to book it a second time.
    // ------------------------------------------------------------------
    std::cout << "\n=== Booking the ticket ===\n";
    ticket.book();
    std::cout << "Booked after book()        : " << (ticket.getBooked() ? "yes" : "no") << '\n';
    ticket.book();   // second call — should have no effect
    std::cout << "Booked after 2nd book()    : " << (ticket.getBooked() ? "yes" : "no") << '\n';

    // ------------------------------------------------------------------
    // 3. Calculate discounted prices.
    // ------------------------------------------------------------------
    std::cout << "\n=== Discounted prices (base: " << ticket.getPrice() << ") ===\n";
    std::cout << "10% discount  : " << ticket.discountedPrice(10.0) << '\n';
    std::cout << "25% discount  : " << ticket.discountedPrice(25.0) << '\n';
    std::cout << "50% discount  : " << ticket.discountedPrice(50.0) << '\n';

    // ------------------------------------------------------------------
    // 4. Modify some fields via setters, then check derived predicates.
    // ------------------------------------------------------------------
    std::cout << "\n=== After setPrice(250.0) ===\n";
    ticket.setPrice(250.0);
    std::cout << "New price : " << ticket.getPrice() << '\n';
    std::cout << "Premium   : " << (ticket.isPremium() ? "yes" : "no") << '\n';

    std::cout << "\n=== After setDurationMinutes(148) ===\n";
    ticket.setDurationMinutes(148);
    std::cout << "Duration (min) : " << ticket.getDurationMinutes() << '\n';
    std::cout << "Long movie     : " << (ticket.isLongMovie() ? "yes" : "no") << '\n';

    // ------------------------------------------------------------------
    // 5. Cancel booking.
    // ------------------------------------------------------------------
    std::cout << "\n=== Cancelling the booking ===\n";
    ticket.cancelBooking();
    std::cout << "Booked after cancelBooking()       : "
              << (ticket.getBooked() ? "yes" : "no") << '\n';
    ticket.cancelBooking();   // second call — should have no effect
    std::cout << "Booked after 2nd cancelBooking()   : "
              << (ticket.getBooked() ? "yes" : "no") << '\n';

    // ------------------------------------------------------------------
    // 6. Edge case: invalid constructor arguments are clamped to minimums.
    // ------------------------------------------------------------------
    std::cout << "\n=== Edge-case ticket (invalid arguments) ===\n";
    MovieTicket bad(-5, 0, -99.0, false, -10);
    std::cout << "Hall (expected 1)     : " << bad.getHallNumber()      << '\n';
    std::cout << "Seat (expected 1)     : " << bad.getSeatNumber()       << '\n';
    std::cout << "Price (expected 0.0)  : " << bad.getPrice()            << '\n';
    std::cout << "Duration (expected 1) : " << bad.getDurationMinutes()  << '\n';

    return 0;
}
