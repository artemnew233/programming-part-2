#include "MovieTicket.hpp"

MovieTicket::MovieTicket(int hallNumber, int seatNumber, double price, bool booked, int durationMinutes)
    : m_hallNumber(hallNumber > 0 ? hallNumber : 1),
      m_seatNumber(seatNumber > 0 ? seatNumber : 1),
      m_price(price >= 0.0 ? price : 0.0),
      m_booked(booked),
      m_durationMinutes(durationMinutes > 0 ? durationMinutes : 0) {}

int    MovieTicket::getHallNumber()      const { return m_hallNumber; }
int    MovieTicket::getSeatNumber()      const { return m_seatNumber; }
double MovieTicket::getPrice()           const { return m_price; }
bool   MovieTicket::getBooked()          const { return m_booked; }
int    MovieTicket::getDurationMinutes() const { return m_durationMinutes; }

void MovieTicket::setHallNumber(int value)      { if (value > 0) m_hallNumber = value; }
void MovieTicket::setSeatNumber(int value)      { if (value > 0) m_seatNumber = value; }
void MovieTicket::setPrice(double value)        { if (value >= 0.0) m_price = value; }
void MovieTicket::setBooked(bool value)         { m_booked = value; }
void MovieTicket::setDurationMinutes(int value) { if (value > 0) m_durationMinutes = value; }

void MovieTicket::book() {
    m_booked = true;
}

void MovieTicket::cancelBooking() {
    m_booked = false;
}


bool MovieTicket::isPremium() const {
    return m_hallNumber >= 3 && m_price >= 15.0;
}

double MovieTicket::discountedPrice(double percent) const {
    if (percent < 0.0) percent = 0.0;
    if (percent > 100.0) percent = 100.0;
    return m_price * (1.0 - percent / 100.0);
}


bool MovieTicket::isLongMovie() const {
    return m_durationMinutes > 120;
}
