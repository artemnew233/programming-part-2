#include "MovieTicket.hpp"

// ---------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------

MovieTicket::MovieTicket(int hallNumber, int seatNumber, double price,
                         bool booked, int durationMinutes)
    : m_hallNumber(hallNumber >= 1 ? hallNumber : 1),
      m_seatNumber(seatNumber >= 1 ? seatNumber : 1),
      m_price(price > 0.0 ? price : 0.0),
      m_booked(booked),
      m_durationMinutes(durationMinutes > 0 ? durationMinutes : 1)
{}

// ---------------------------------------------------------------
// Getters
// ---------------------------------------------------------------

int MovieTicket::getHallNumber() const {
    return m_hallNumber;
}

int MovieTicket::getSeatNumber() const {
    return m_seatNumber;
}

double MovieTicket::getPrice() const {
    return m_price;
}

bool MovieTicket::getBooked() const {
    return m_booked;
}

int MovieTicket::getDurationMinutes() const {
    return m_durationMinutes;
}

// ---------------------------------------------------------------
// Setters
// ---------------------------------------------------------------

void MovieTicket::setHallNumber(int value) {
    if (value >= 1) {
        m_hallNumber = value;
    }
}

void MovieTicket::setSeatNumber(int value) {
    if (value >= 1) {
        m_seatNumber = value;
    }
}

void MovieTicket::setPrice(double value) {
    if (value > 0.0) {
        m_price = value;
    }
}

void MovieTicket::setBooked(bool value) {
    m_booked = value;
}

void MovieTicket::setDurationMinutes(int value) {
    if (value > 0) {
        m_durationMinutes = value;
    }
}

// ---------------------------------------------------------------
// Main methods
// ---------------------------------------------------------------

void MovieTicket::book() {
    if (!m_booked) {
        m_booked = true;
    }
}

void MovieTicket::cancelBooking() {
    if (m_booked) {
        m_booked = false;
    }
}

bool MovieTicket::isPremium() const {
    // A ticket is considered premium when the price exceeds 200.0
    return m_price > 200.0;
}

double MovieTicket::discountedPrice(double percent) const {
    if (percent < 0.0)   percent = 0.0;
    if (percent > 100.0) percent = 100.0;
    return m_price * (1.0 - percent / 100.0);
}

bool MovieTicket::isLongMovie() const {
    // A movie is "long" if it runs for more than 120 minutes (> 2 hours)
    return m_durationMinutes > 120;
}
