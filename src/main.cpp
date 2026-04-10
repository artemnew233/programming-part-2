#include <iostream>
#include "MovieTicket.hpp"

int main() {
    MovieTicket ticket(2, 14, 12.50, false, 148);

    std::cout << "=== MovieTicket Info ===\n";
    std::cout << "Hall:     " << ticket.getHallNumber() << "\n";
    std::cout << "Seat:     " << ticket.getSeatNumber() << "\n";
    std::cout << "Price:    " << ticket.getPrice() << "\n";
    std::cout << "Booked:   " << (ticket.getBooked() ? "yes" : "no") << "\n";
    std::cout << "Duration: " << ticket.getDurationMinutes() << " min\n";

    std::cout << "\n=== Methods ===\n";
    std::cout << "Is premium:  " << (ticket.isPremium() ? "yes" : "no") << "\n";
    std::cout << "Is long:     " << (ticket.isLongMovie() ? "yes" : "no") << "\n";
    std::cout << "Price -20%:  " << ticket.discountedPrice(20.0) << "\n";

    ticket.book();
    std::cout << "\nAfter book(): booked = " << (ticket.getBooked() ? "yes" : "no") << "\n";

    ticket.cancelBooking();
    std::cout << "After cancelBooking(): booked = " << (ticket.getBooked() ? "yes" : "no") << "\n";

    // move to premium hall and check again
    ticket.setHallNumber(5);
    ticket.setPrice(18.0);
    std::cout << "\nAfter hall=5, price=18.0:\n";
    std::cout << "Is premium: " << (ticket.isPremium() ? "yes" : "no") << "\n";
    std::cout << "Price -10%: " << ticket.discountedPrice(10.0) << "\n";

    return 0;
}
