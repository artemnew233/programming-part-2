#include <gtest/gtest.h>
#include "route_utils.h"


TEST(LongerSegmentTest, IntFirstLonger) {
    EXPECT_EQ(longerSegment(10, 3), 10);
}
TEST(LongerSegmentTest, IntSecondLonger) {
    EXPECT_EQ(longerSegment(3, 10), 10);
}
TEST(LongerSegmentTest, IntEqual) {
    EXPECT_EQ(longerSegment(7, 7), 7);
}
TEST(LongerSegmentTest, DoubleValues) {
    EXPECT_DOUBLE_EQ(longerSegment(5.5, 2.3), 5.5);
}


TEST(CountSegmentsTest, IntBasic) {
    int arr[] = {1, 5, 10, 15, 20};
    EXPECT_EQ(countSegmentsInRange(arr, 5, 5, 15), 3);
}
TEST(CountSegmentsTest, BoundaryValues) {
    int arr[] = {1, 5, 10, 15, 20};

    EXPECT_EQ(countSegmentsInRange(arr, 5, 5, 5), 1);
    EXPECT_EQ(countSegmentsInRange(arr, 5, 20, 20), 1);
}
TEST(CountSegmentsTest, NoMatch) {
    int arr[] = {1, 2, 3};
    EXPECT_EQ(countSegmentsInRange(arr, 3, 50, 100), 0);
}
TEST(CountSegmentsTest, DoubleValues) {
    double arr[] = {1.0, 3.5, 5.0};
    EXPECT_EQ(countSegmentsInRange(arr, 3, 3.5, 5.0), 2);
}

TEST(AverageSpeedTest, IntegerDivision) {
    EXPECT_EQ(averageSpeed(100, 5), 20);
}
TEST(AverageSpeedTest, MixedTypes) {
    EXPECT_DOUBLE_EQ(averageSpeed(150.0, 3), 50.0);
}
TEST(AverageSpeedTest, FloatAndDouble) {
    auto result = averageSpeed(90.0f, 3.0);
    EXPECT_NEAR(result, 30.0, 1e-5);
}
TEST(AverageSpeedTest, ZeroTimeThrows) {
    EXPECT_THROW(averageSpeed(100, 0), std::invalid_argument);
}
TEST(AverageSpeedTest, ZeroTimeDoubleThrows) {
    EXPECT_THROW(averageSpeed(100.0, 0.0), std::invalid_argument);
}
