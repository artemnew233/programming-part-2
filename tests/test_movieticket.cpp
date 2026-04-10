#include <gtest/gtest.h>
#include "MovieTicket.hpp"

// ── Constructor ──────────────────────────────────────────────────────────────

TEST(MovieTicketConstructorTest, StoresValidValues) {
    MovieTicket t(2, 14, 12.50, false, 148);
    EXPECT_EQ(t.getHallNumber(), 2);
    EXPECT_EQ(t.getSeatNumber(), 14);
    EXPECT_DOUBLE_EQ(t.getPrice(), 12.50);
    EXPECT_FALSE(t.getBooked());
    EXPECT_EQ(t.getDurationMinutes(), 148);
}

TEST(MovieTicketConstructorTest, InvalidHallDefaultsToOne) {
    MovieTicket t(-3, 5, 10.0, false, 90);
    EXPECT_EQ(t.getHallNumber(), 1);
}

TEST(MovieTicketConstructorTest, InvalidSeatDefaultsToOne) {
    MovieTicket t(1, 0, 10.0, false, 90);
    EXPECT_EQ(t.getSeatNumber(), 1);
}

TEST(MovieTicketConstructorTest, NegativePriceDefaultsToZero) {
    MovieTicket t(1, 1, -5.0, false, 90);
    EXPECT_DOUBLE_EQ(t.getPrice(), 0.0);
}

TEST(MovieTicketConstructorTest, InvalidDurationDefaultsToZero) {
    MovieTicket t(1, 1, 10.0, false, -10);
    EXPECT_EQ(t.getDurationMinutes(), 0);
}

// ── Getters and Setters ──────────────────────────────────────────────────────

TEST(MovieTicketGetterSetterTest, SetHallNumberValid) {
    MovieTicket t(1, 1, 10.0, false, 90);
    t.setHallNumber(5);
    EXPECT_EQ(t.getHallNumber(), 5);
}

TEST(MovieTicketGetterSetterTest, SetHallNumberIgnoresInvalid) {
    MovieTicket t(2, 1, 10.0, false, 90);
    t.setHallNumber(-1);
    EXPECT_EQ(t.getHallNumber(), 2);
}

TEST(MovieTicketGetterSetterTest, SetPriceValid) {
    MovieTicket t(1, 1, 10.0, false, 90);
    t.setPrice(20.0);
    EXPECT_DOUBLE_EQ(t.getPrice(), 20.0);
}

TEST(MovieTicketGetterSetterTest, SetPriceIgnoresNegative) {
    MovieTicket t(1, 1, 10.0, false, 90);
    t.setPrice(-5.0);
    EXPECT_DOUBLE_EQ(t.getPrice(), 10.0);
}

TEST(MovieTicketGetterSetterTest, SetDurationMinutes) {
    MovieTicket t(1, 1, 10.0, false, 90);
    t.setDurationMinutes(180);
    EXPECT_EQ(t.getDurationMinutes(), 180);
}

// ── book() / cancelBooking() ─────────────────────────────────────────────────

TEST(MovieTicketMethodTest, BookSetsBookedTrue) {
    MovieTicket t(1, 1, 10.0, false, 90);
    t.book();
    EXPECT_TRUE(t.getBooked());
}

TEST(MovieTicketMethodTest, CancelBookingSetsBookedFalse) {
    MovieTicket t(1, 1, 10.0, true, 90);
    t.cancelBooking();
    EXPECT_FALSE(t.getBooked());
}

TEST(MovieTicketMethodTest, BookThenCancelCycle) {
    MovieTicket t(1, 1, 10.0, false, 90);
    t.book();
    EXPECT_TRUE(t.getBooked());
    t.cancelBooking();
    EXPECT_FALSE(t.getBooked());
}

// ── isPremium() ──────────────────────────────────────────────────────────────

TEST(MovieTicketMethodTest, IsPremiumTrueWhenHallAndPriceQualify) {
    MovieTicket t(3, 1, 15.0, false, 90);
    EXPECT_TRUE(t.isPremium());
}

TEST(MovieTicketMethodTest, IsPremiumFalseWhenHallTooLow) {
    MovieTicket t(2, 1, 20.0, false, 90);
    EXPECT_FALSE(t.isPremium());
}

TEST(MovieTicketMethodTest, IsPremiumFalseWhenPriceTooLow) {
    MovieTicket t(5, 1, 14.99, false, 90);
    EXPECT_FALSE(t.isPremium());
}

// ── discountedPrice() ────────────────────────────────────────────────────────

TEST(MovieTicketMethodTest, DiscountedPriceTwentyPercent) {
    MovieTicket t(1, 1, 10.0, false, 90);
    EXPECT_DOUBLE_EQ(t.discountedPrice(20.0), 8.0);
}

TEST(MovieTicketMethodTest, DiscountedPriceZeroPercent) {
    MovieTicket t(1, 1, 10.0, false, 90);
    EXPECT_DOUBLE_EQ(t.discountedPrice(0.0), 10.0);
}

TEST(MovieTicketMethodTest, DiscountedPriceHundredPercent) {
    MovieTicket t(1, 1, 10.0, false, 90);
    EXPECT_DOUBLE_EQ(t.discountedPrice(100.0), 0.0);
}

// ── isLongMovie() ────────────────────────────────────────────────────────────

TEST(MovieTicketMethodTest, IsLongMovieTrueAbove120) {
    MovieTicket t(1, 1, 10.0, false, 121);
    EXPECT_TRUE(t.isLongMovie());
}

TEST(MovieTicketMethodTest, IsLongMovieFalseAt120) {
    MovieTicket t(1, 1, 10.0, false, 120);
    EXPECT_FALSE(t.isLongMovie());
}

// ── Boundary cases ───────────────────────────────────────────────────────────

TEST(MovieTicketBoundaryTest, ExactPremiumHallAndPrice) {
    // hall == 3 and price == 15.0 is exactly the premium threshold
    MovieTicket t(3, 1, 15.0, false, 90);
    EXPECT_TRUE(t.isPremium());
}

TEST(MovieTicketBoundaryTest, DiscountClampedAbove100) {
    MovieTicket t(1, 1, 10.0, false, 90);
    EXPECT_DOUBLE_EQ(t.discountedPrice(150.0), 0.0);
}

TEST(MovieTicketBoundaryTest, DiscountClampedBelow0) {
    MovieTicket t(1, 1, 10.0, false, 90);
    EXPECT_DOUBLE_EQ(t.discountedPrice(-10.0), 10.0);
}
