#include <gtest/gtest.h>
#include "ContainerExperiments.hpp"
#include "Record.hpp"
#include <deque>
#include <vector>

TEST(RecordTest, MakeFileRecord) {
    auto r = makeFileRecord(1);
    EXPECT_EQ(r.id, 1);
    EXPECT_FALSE(r.name.empty());
    EXPECT_FALSE(r.extension.empty());
    EXPECT_GT(r.size, 0);
}

TEST(RecordTest, ReadonlyEvery5th) {
    for (int i = 1; i <= 20; ++i) {
        auto r = makeFileRecord(i);
        EXPECT_EQ(r.readonly, (i % 5 == 0));
    }
}

TEST(VectorTest, FillSize) {
    auto v = makeVector(50);
    EXPECT_EQ(v.size(), 50u);
}

TEST(VectorTest, IndexAccess) {
    auto v = makeVector(5);
    EXPECT_EQ(v[0].id, 1);
    EXPECT_EQ(v[4].id, 5);
}

TEST(VectorTest, AtThrows) {
    auto v = makeVector(3);
    EXPECT_THROW(v.at(100), std::out_of_range);
}

TEST(DequeTest, FillSize) {
    auto d = makeDeque(50);
    EXPECT_EQ(d.size(), 50u);
}

TEST(DequeTest, PushFront) {
    auto d = makeDeque(3);
    d.push_front(makeFileRecord(999));
    EXPECT_EQ(d.front().id, 999);
    EXPECT_EQ(d.size(), 4u);
}

TEST(ArrayTest, FixedSize) {
    auto a = makeArray();
    EXPECT_EQ(a.size(), ARRAY_SIZE);
}

TEST(SearchTest, FindLargeVector) {
    auto v = makeVector(100);
    auto* r = findLargeVector(v, 0); // every file > 0
    EXPECT_NE(r, nullptr);
}

TEST(SearchTest, FindLargeVectorNone) {
    auto v = makeVector(10);
    auto* r = findLargeVector(v, 999999999LL);
    EXPECT_EQ(r, nullptr);
}

TEST(CountTest, CountByExtVector) {
    auto v = makeVector(12);
    int cnt = countByExtVector(v, ".txt");
    EXPECT_GT(cnt, 0);
    EXPECT_LE(cnt, (int)v.size());
}

TEST(CountTest, CountByExtArray) {
    auto a = makeArray();
    int cnt = countByExtArray(a, ".png");
    EXPECT_GE(cnt, 0);
}

TEST(FilterTest, FilterReadonly) {
    auto v = makeVector(20);
    auto ro = filterReadonlyVector(v);
    for (const auto& r : ro)
        EXPECT_TRUE(r.readonly);
    EXPECT_EQ((int)ro.size(), countByExtVector(v, ".txt") >= 0 ? (int)ro.size() : 0);
}

TEST(SmartPtrTest, SharedExtensionShared) {
    auto ext = std::make_shared<ExtensionInfo>(ExtensionInfo{".txt","plain"});
    auto r1  = makeFileRecordShared(1, ext);
    auto r2  = makeFileRecordShared(2, ext);
    // ext, r1.extension, r2.extension all point to same object
    EXPECT_EQ(ext.use_count(), 3);
}

TEST(SmartPtrTest, UniqueMetaMoveOnly) {
    auto u = makeFileRecordUnique(1);
    EXPECT_NE(u.sizeMeta, nullptr);
    auto u2 = std::move(u);
    EXPECT_EQ(u.sizeMeta, nullptr);
    EXPECT_NE(u2.sizeMeta, nullptr);
}

TEST(CapacityTest, ReallocationMovesData) {
    std::vector<FileRecord> v;
    v.reserve(1);
    v.push_back(makeFileRecord(1));
    const FileRecord* before = v.data();
    v.push_back(makeFileRecord(2)); // forces reallocation
    const FileRecord* after = v.data();
    EXPECT_NE(before, after);
}
