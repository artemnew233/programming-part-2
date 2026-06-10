#include <iostream>
#include "MovieTicket.hpp"

int main() {
    // create ticket
    MovieTicket ticket(3, 15, 120.0, false, 95);

    std::cout << "=== Initial ticket state ===\n";
    std::cout << "Hall number    : " << ticket.getHallNumber()      << '\n';
    std::cout << "Seat number    : " << ticket.getSeatNumber()       << '\n';
    std::cout << "Price          : " << ticket.getPrice()            << '\n';
    std::cout << "Booked         : " << (ticket.getBooked() ? "yes" : "no") << '\n';
    std::cout << "Duration (min) : " << ticket.getDurationMinutes()  << '\n';
    std::cout << "Premium        : " << (ticket.isPremium()    ? "yes" : "no") << '\n';
    std::cout << "Long movie     : " << (ticket.isLongMovie()  ? "yes" : "no") << '\n';

    // booking
    std::cout << "\n=== Booking the ticket ===\n";
    ticket.book();
    std::cout << "Booked after book()        : " << (ticket.getBooked() ? "yes" : "no") << '\n';
    ticket.book();
    std::cout << "Booked after 2nd book()    : " << (ticket.getBooked() ? "yes" : "no") << '\n';

    // discount
    std::cout << "\n=== Discounted prices (base: " << ticket.getPrice() << ") ===\n";
    std::cout << "10% discount  : " << ticket.discountedPrice(10.0) << '\n';
    std::cout << "25% discount  : " << ticket.discountedPrice(25.0) << '\n';
    std::cout << "50% discount  : " << ticket.discountedPrice(50.0) << '\n';

    // change values
    std::cout << "\n=== After setPrice(250.0) ===\n";
    ticket.setPrice(250.0);
    std::cout << "New price : " << ticket.getPrice() << '\n';
    std::cout << "Premium   : " << (ticket.isPremium() ? "yes" : "no") << '\n';

    std::cout << "\n=== After setDurationMinutes(148) ===\n";
    ticket.setDurationMinutes(148);
    std::cout << "Duration (min) : " << ticket.getDurationMinutes() << '\n';
    std::cout << "Long movie     : " << (ticket.isLongMovie() ? "yes" : "no") << '\n';

    // cancel
    std::cout << "\n=== Cancelling the booking ===\n";
    ticket.cancelBooking();
    std::cout << "Booked after cancelBooking()       : "
              << (ticket.getBooked() ? "yes" : "no") << '\n';
    ticket.cancelBooking();
    std::cout << "Booked after 2nd cancelBooking()   : "
              << (ticket.getBooked() ? "yes" : "no") << '\n';

    // edge case
    std::cout << "\n=== Edge-case ticket (invalid arguments) ===\n";
    MovieTicket bad(-5, 0, -99.0, false, -10);
    std::cout << "Hall (expected 1)     : " << bad.getHallNumber()      << '\n';
    std::cout << "Seat (expected 1)     : " << bad.getSeatNumber()       << '\n';
    std::cout << "Price (expected 0.0)  : " << bad.getPrice()            << '\n';
    std::cout << "Duration (expected 1) : " << bad.getDurationMinutes()  << '\n';

    return 0;
}
