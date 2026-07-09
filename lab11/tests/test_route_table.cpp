#include <gtest/gtest.h>
#include "RouteTable.h"
#include "RouteRecord.h"
#include "DistancePolicy.h"

// --- RouteTable ---
TEST(RouteTableTest, SetAndGet) {
    RouteTable<int, 3> t;
    t.set(0, 10);
    t.set(1, 20);
    EXPECT_EQ(t.get(0), 10);
    EXPECT_EQ(t.get(1), 20);
}

TEST(RouteTableTest, LongestShortest) {
    RouteTable<int, 4> t;
    t.set(0, 5); t.set(1, 15); t.set(2, 3); t.set(3, 9);
    EXPECT_EQ(t.longest(), 15);
    EXPECT_EQ(t.shortest(), 3);
}

TEST(RouteTableTest, Average) {
    RouteTable<int, 4> t;
    t.set(0, 10); t.set(1, 20); t.set(2, 30); t.set(3, 40);
    EXPECT_DOUBLE_EQ(t.average(), 25.0);
}

TEST(RouteTableTest, OutOfRangeThrows) {
    RouteTable<int, 3> t;
    t.set(0, 5);
    EXPECT_THROW(t.get(5), std::out_of_range);
    EXPECT_THROW(t.get(-1), std::out_of_range);
    EXPECT_THROW(t.set(3, 10), std::out_of_range);
}

TEST(RouteTableTest, EmptyThrows) {
    RouteTable<double, 5> t;
    EXPECT_THROW(t.longest(), std::logic_error);
    EXPECT_THROW(t.shortest(), std::logic_error);
    EXPECT_THROW(t.average(), std::logic_error);
}

TEST(RouteTableTest, DoubleType) {
    RouteTable<double, 3> t;
    t.set(0, 1.5); t.set(1, 2.5); t.set(2, 3.0);
    EXPECT_DOUBLE_EQ(t.shortest(), 1.5);
    EXPECT_NEAR(t.average(), 7.0 / 3.0, 1e-9);
}

// --- RouteRecord ---
TEST(RouteRecordTest, StringInt) {
    RouteRecord<std::string, int> r("X->Y", 300);
    EXPECT_EQ(r.code(), "X->Y");
    EXPECT_EQ(r.metric(), 300);
}

TEST(RouteRecordTest, IntDouble) {
    RouteRecord<int, double> r(1, 3.14);
    EXPECT_EQ(r.code(), 1);
    EXPECT_DOUBLE_EQ(r.metric(), 3.14);
}

// --- DistancePolicy ---
TEST(DistancePolicyTest, IntExact) {
    EXPECT_TRUE(DistancePolicy<int>::equal(42, 42));
    EXPECT_FALSE(DistancePolicy<int>::equal(42, 43));
    EXPECT_EQ(DistancePolicy<int>::epsilon(), 0);
}

TEST(DistancePolicyTest, DoubleApproximate) {
    // within epsilon
    EXPECT_TRUE(DistancePolicy<double>::equal(1.0, 1.0 + 1e-10));
    // outside epsilon
    EXPECT_FALSE(DistancePolicy<double>::equal(1.0, 1.0 + 1e-8));
}

TEST(DistancePolicyTest, FloatApproximate) {
    EXPECT_TRUE(DistancePolicy<float>::equal(1.0f, 1.0f + 1e-6f));
    EXPECT_FALSE(DistancePolicy<float>::equal(1.0f, 1.0f + 1.0f));
}

// Compiler investigation: distinct instantiations have distinct sizes
TEST(SizeofTest, DifferentInstantiationsHaveDifferentSizes) {
    EXPECT_LT(sizeof(RouteTable<int, 5>), sizeof(RouteTable<int, 10>));
    EXPECT_LT(sizeof(RouteTable<int, 5>), sizeof(RouteTable<double, 5>));
}
