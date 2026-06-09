#pragma once

/**
 * @class MovieTicket
 * @brief Represents a cinema ticket in a cinema booking system.
 *
 * Encapsulates hall/seat assignment, price, booking status,
 * and movie duration. All fields are private; state is
 * accessed and modified through the public interface.
 */
class MovieTicket {
public:
    /**
     * @brief Constructs a MovieTicket with all required fields.
     * @param hallNumber   Positive hall identifier (clamped to 1 if invalid).
     * @param seatNumber   Positive seat identifier (clamped to 1 if invalid).
     * @param price        Ticket price (must be > 0.0; clamped to 0.0 otherwise).
     * @param booked       Initial booking status.
     * @param durationMinutes Movie duration in minutes (must be > 0; clamped to 1).
     */
    MovieTicket(int hallNumber, int seatNumber, double price,
                bool booked, int durationMinutes);

    // ---------------------------------------------------------------
    // Getters
    // ---------------------------------------------------------------
    int    getHallNumber()      const;
    int    getSeatNumber()      const;
    double getPrice()           const;
    bool   getBooked()          const;
    int    getDurationMinutes() const;

    // ---------------------------------------------------------------
    // Setters
    // ---------------------------------------------------------------
    void setHallNumber(int value);
    void setSeatNumber(int value);
    void setPrice(double value);
    void setBooked(bool value);
    void setDurationMinutes(int value);

    // ---------------------------------------------------------------
    // Main methods
    // ---------------------------------------------------------------

    /**
     * @brief Books the ticket if it is not already booked.
     *        Has no effect if the ticket is already booked.
     */
    void book();

    /**
     * @brief Cancels the booking if the ticket is currently booked.
     *        Has no effect if the ticket is not booked.
     */
    void cancelBooking();

    /**
     * @brief Returns true if this is a premium-priced ticket (price > 200.0).
     */
    bool isPremium() const;

    /**
     * @brief Calculates the ticket price after applying a percentage discount.
     * @param percent Discount percentage in [0, 100]; clamped if out of range.
     * @return Discounted price.
     */
    double discountedPrice(double percent) const;

    /**
     * @brief Returns true if the movie duration exceeds 120 minutes (> 2 hours).
     */
    bool isLongMovie() const;

private:
    int    m_hallNumber;
    int    m_seatNumber;
    double m_price;
    bool   m_booked;
    int    m_durationMinutes;
};
