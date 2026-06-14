#include "file_record.hpp"
#include "simple_vector.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <stdexcept>

TEST(SimpleVectorTest, DefaultEmpty) {
    SimpleVector<FileRecord> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
}

TEST(SimpleVectorTest, PushBackAndAccess) {
    SimpleVector<FileRecord> v;
    v.push_back({1, "a", ".txt", 100, false});
    v.push_back({2, "b", ".json", 200, true});
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.front().id, 1);
    EXPECT_EQ(v.back().id, 2);
    EXPECT_EQ(v[0].name, "a");
    EXPECT_EQ(v.at(1).extension, ".json");
}

TEST(SimpleVectorTest, AtOutOfRangeThrows) {
    SimpleVector<FileRecord> v;
    v.push_back({1, "a", ".txt", 100, false});
    EXPECT_THROW((void)v.at(5), std::out_of_range);
}

TEST(SimpleVectorTest, PopBack) {
    SimpleVector<FileRecord> v;
    v.push_back({1, "a", ".txt", 100, false});
    v.push_back({2, "b", ".txt", 200, false});
    v.pop_back();
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v.back().id, 1);
}

TEST(SimpleVectorTest, PopBackEmptyThrows) {
    SimpleVector<FileRecord> v;
    EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(SimpleVectorTest, ReserveDoesNotChangeSize) {
    SimpleVector<FileRecord> v;
    v.reserve(10);
    EXPECT_GE(v.capacity(), 10u);
    EXPECT_EQ(v.size(), 0u);
}

TEST(SimpleVectorTest, ResizeGrows) {
    SimpleVector<FileRecord> v;
    v.resize(3);
    EXPECT_EQ(v.size(), 3u);
}

TEST(SimpleVectorTest, ResizeShrinks) {
    SimpleVector<FileRecord> v;
    v.push_back({1, "a", ".txt", 100, false});
    v.push_back({2, "b", ".txt", 200, false});
    v.resize(1);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0].id, 1);
}

TEST(SimpleVectorTest, RangeFor) {
    SimpleVector<FileRecord> v;
    v.push_back({1, "a", ".txt", 100, false});
    v.push_back({2, "b", ".txt", 200, true});
    int count = 0;
    for (const auto& r : v) { EXPECT_GT(r.id, 0); ++count; }
    EXPECT_EQ(count, 2);
}

TEST(SimpleVectorTest, CopyConstructor) {
    SimpleVector<FileRecord> v;
    v.push_back({1, "a", ".txt", 100, false});
    SimpleVector<FileRecord> copy = v;
    EXPECT_EQ(copy.size(), 1u);
    copy[0].id = 99;
    EXPECT_EQ(v[0].id, 1);
}

TEST(SimpleVectorTest, MoveConstructor) {
    SimpleVector<FileRecord> v;
    v.push_back({1, "a", ".txt", 100, false});
    SimpleVector<FileRecord> moved = std::move(v);
    EXPECT_EQ(moved.size(), 1u);
    EXPECT_EQ(v.size(), 0u);
}

TEST(SimpleVectorTest, RemoveIfAndResize) {
    SimpleVector<FileRecord> v;
    v.push_back({1, "a", ".txt", 2048, false});
    v.push_back({2, "b", ".zip", 51200, true});
    v.push_back({3, "c", ".jpg", 20480, false});

    auto new_end = std::remove_if(v.begin(), v.end(),
        [](const FileRecord& r) { return r.readonly; });
    v.resize(static_cast<std::size_t>(std::distance(v.begin(), new_end)));
    EXPECT_EQ(v.size(), 2u);
    for (const auto& r : v) EXPECT_FALSE(r.readonly);
}

TEST(SimpleVectorTest, InitializerList) {
    SimpleVector<FileRecord> v{
        {1, "a", ".txt", 100, false},
        {2, "b", ".txt", 200, true}
    };
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0].id, 1);
}

TEST(SimpleVectorTest, ReallocationMovesData) {
    SimpleVector<FileRecord> v;
    v.reserve(1);
    v.push_back({1, "a", ".txt", 100, false});
    const FileRecord* before = v.data();
    v.push_back({2, "b", ".txt", 200, false});
    EXPECT_NE(v.data(), before);
}
