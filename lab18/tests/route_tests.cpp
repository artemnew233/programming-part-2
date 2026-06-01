#include "lab18/route.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

using lab18::Point;
using lab18::Route;

TEST(RouteTest, EmptyRouteIsEmpty) {
    Route r({});
    EXPECT_TRUE(r.empty());
    EXPECT_EQ(r.size(), 0u);
    EXPECT_DOUBLE_EQ(r.totalLength(), 0.0);
    EXPECT_DOUBLE_EQ(r.longestSegment(), 0.0);
}

TEST(RouteTest, SinglePointNoLength) {
    Route r({{"A", 1.0, 2.0}});
    EXPECT_FALSE(r.empty());
    EXPECT_EQ(r.size(), 1u);
    EXPECT_DOUBLE_EQ(r.totalLength(), 0.0);
}

TEST(RouteTest, TwoPointsLength) {
    Route r({{"A", 0.0, 0.0}, {"B", 3.0, 4.0}});
    EXPECT_DOUBLE_EQ(r.totalLength(), 5.0);
    EXPECT_DOUBLE_EQ(r.longestSegment(), 5.0);
}

TEST(RouteTest, ThreePointsTotalLength) {
    Route r({{"A", 0.0, 0.0}, {"B", 3.0, 4.0}, {"C", 3.0, 4.0 + 5.0}});
    EXPECT_DOUBLE_EQ(r.totalLength(), 10.0);
}

TEST(RouteTest, LongestSegmentDetected) {
    Route r({
        {"A", 0.0, 0.0},
        {"B", 3.0, 4.0},
        {"C", 3.0, 4.0 + 100.0},
    });
    EXPECT_DOUBLE_EQ(r.longestSegment(), 100.0);
    EXPECT_EQ(r.longestSegmentIndex(), 1u);
}

TEST(RouteTest, LongestSegmentIndexThrowsOnEmpty) {
    Route r({});
    EXPECT_THROW((void)r.longestSegmentIndex(), std::out_of_range);
}

TEST(RouteTest, LongestSegmentIndexThrowsOnSinglePoint) {
    Route r({{"A", 0.0, 0.0}});
    EXPECT_THROW((void)r.longestSegmentIndex(), std::out_of_range);
}

TEST(RouteTest, AddPointGrowsRoute) {
    Route r({{"A", 0.0, 0.0}, {"B", 3.0, 4.0}});
    const double before = r.totalLength();
    r.addPoint({"C", 6.0, 4.0});
    EXPECT_GT(r.totalLength(), before);
    EXPECT_EQ(r.size(), 3u);
}

TEST(RouteTest, StaticDistance) {
    EXPECT_DOUBLE_EQ(Route::distance({"A", 0.0, 0.0}, {"B", 3.0, 4.0}), 5.0);
    EXPECT_DOUBLE_EQ(Route::distance({"X", 1.0, 1.0}, {"X", 1.0, 1.0}), 0.0);
}

TEST(RouteTest, PointsSpanSize) {
    Route r({{"A", 0.0, 0.0}, {"B", 1.0, 0.0}});
    EXPECT_EQ(r.points().size(), 2u);
}
