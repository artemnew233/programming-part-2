#pragma once

class MovieTicket {
public:
    MovieTicket(int hallNumber, int seatNumber, double price, bool booked, int durationMinutes);

    int    getHallNumber()      const;
    int    getSeatNumber()      const;
    double getPrice()           const;
    bool   getBooked()          const;
    int    getDurationMinutes() const;

    void setHallNumber(int value);
    void setSeatNumber(int value);
    void setPrice(double value);
    void setBooked(bool value);
    void setDurationMinutes(int value);

    void   book();
    void   cancelBooking();
    bool   isPremium()                      const;
    double discountedPrice(double percent)  const;
    bool   isLongMovie()                    const;

private:
    int    m_hallNumber;
    int    m_seatNumber;
    double m_price;
    bool   m_booked;
    int    m_durationMinutes;
};
