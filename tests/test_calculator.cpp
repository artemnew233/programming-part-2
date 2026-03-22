#include <gtest/gtest.h>
#include "calculator.hpp"

TEST(CalculatorTest, AddWorks) {
    EXPECT_DOUBLE_EQ(add(2, 3), 5);
    EXPECT_DOUBLE_EQ(add(-1, 1), 0);
    EXPECT_DOUBLE_EQ(add(0, 0), 0);
}

TEST(CalculatorTest, SubWorks) {
    EXPECT_DOUBLE_EQ(sub(7, 4), 3);
    EXPECT_DOUBLE_EQ(sub(0, 5), -5);
}

TEST(CalculatorTest, MulWorks) {
    EXPECT_DOUBLE_EQ(mul(3, 4), 12);
    EXPECT_DOUBLE_EQ(mul(0, 99), 0);
}

TEST(CalculatorTest, DivWorks) {
    EXPECT_DOUBLE_EQ(divide(10, 2), 5);
    EXPECT_DOUBLE_EQ(divide(7, 2), 3.5);
}

TEST(CalculatorTest, DivByZeroThrows) {
    EXPECT_THROW(divide(5, 0), std::invalid_argument);
}
