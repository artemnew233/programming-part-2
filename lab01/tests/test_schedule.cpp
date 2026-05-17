#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "schedule.hpp"

TEST(ScheduleTest, AddClassIncreasesCount) {
    std::vector<std::string> s;
    addClass(s, "Math");
    addClass(s, "Physics");
    EXPECT_EQ(countPeriods(s), 2);
}

TEST(ScheduleTest, EmptyNameIgnored) {
    std::vector<std::string> s;
    addClass(s, "");
    EXPECT_EQ(countPeriods(s), 0);
}

TEST(ScheduleTest, RemoveClassDecreasesCount) {
    std::vector<std::string> s;
    addClass(s, "Math");
    addClass(s, "Physics");
    EXPECT_TRUE(removeClass(s, "Math"));
    EXPECT_EQ(countPeriods(s), 1);
}

TEST(ScheduleTest, RemoveNonExistentReturnsFalse) {
    std::vector<std::string> s;
    addClass(s, "Math");
    EXPECT_FALSE(removeClass(s, "Biology"));
    EXPECT_EQ(countPeriods(s), 1);
}

TEST(ScheduleTest, HasClassFindsExisting) {
    std::vector<std::string> s;
    addClass(s, "C++ Programming");
    EXPECT_TRUE(hasClass(s, "C++ Programming"));
}

TEST(ScheduleTest, HasClassReturnsFalseForMissing) {
    std::vector<std::string> s;
    addClass(s, "Math");
    EXPECT_FALSE(hasClass(s, "Biology"));
}

TEST(ScheduleTest, GetClassAtReturnsCorrectName) {
    std::vector<std::string> s;
    addClass(s, "Math");
    addClass(s, "Physics");
    EXPECT_EQ(getClassAt(s, 0), "Math");
    EXPECT_EQ(getClassAt(s, 1), "Physics");
}

TEST(ScheduleTest, GetClassAtOutOfBoundsReturnsEmpty) {
    std::vector<std::string> s;
    addClass(s, "Math");
    EXPECT_EQ(getClassAt(s, 5),  "");
    EXPECT_EQ(getClassAt(s, -1), "");
}

TEST(ScheduleTest, CountPeriodsOnEmptyIsZero) {
    std::vector<std::string> s;
    EXPECT_EQ(countPeriods(s), 0);
}
