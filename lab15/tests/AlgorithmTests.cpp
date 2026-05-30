#include <gtest/gtest.h>
#include "Algorithms.hpp"
#include "Record.hpp"
#include <algorithm>

static std::vector<FileRecord> sample() { return generateRecords(20, 42); }

// ── Non-modifying ─────────────────────────────────────────────────────

TEST(AlgoTest, TotalSizePositive) {
    EXPECT_GT(totalSize(sample()), 0LL);
}

TEST(AlgoTest, TotalSizeEmpty) {
    std::vector<FileRecord> empty;
    EXPECT_EQ(totalSize(empty), 0LL);
}

TEST(AlgoTest, CountByExtInRange) {
    auto v = sample();
    int n = countByExt(v, ".txt");
    EXPECT_GE(n, 0);
    EXPECT_LE(n, (int)v.size());
}

TEST(AlgoTest, CountByExtUnknown) {
    EXPECT_EQ(countByExt(sample(), ".xyz"), 0);
}

TEST(AlgoTest, AnyReadonly) {
    // seed 42 produces some readonly records
    EXPECT_TRUE(anyReadonly(sample()));
}

TEST(AlgoTest, AnyReadonlyFalse) {
    auto v = sample();
    for (auto& r : v) r.readonly = false;
    EXPECT_FALSE(anyReadonly(v));
}

TEST(AlgoTest, AllPositiveSize) {
    EXPECT_TRUE(allPositiveSize(sample()));
}

TEST(AlgoTest, AllPositiveSizeFalse) {
    auto v = sample();
    v[3].size = -1;
    EXPECT_FALSE(allPositiveSize(v));
}

TEST(AlgoTest, FindByIdFound) {
    auto v = sample();
    auto* r = findById(v, 5);
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->id, 5);
}

TEST(AlgoTest, FindByIdNotFound) {
    EXPECT_EQ(findById(sample(), 9999), nullptr);
}

TEST(AlgoTest, FindLargest) {
    auto v = sample();
    auto* r = findLargest(v);
    ASSERT_NE(r, nullptr);
    for (const auto& rec : v)
        EXPECT_LE(rec.size, r->size);
}

TEST(AlgoTest, FindLargestEmpty) {
    std::vector<FileRecord> empty;
    EXPECT_EQ(findLargest(empty), nullptr);
}

// ── Modifying ─────────────────────────────────────────────────────────

TEST(AlgoTest, FilterByExtCount) {
    auto v = sample();
    int cnt = countByExt(v, ".png");
    auto filtered = filterByExt(v, ".png");
    EXPECT_EQ((int)filtered.size(), cnt);
}

TEST(AlgoTest, FilterByExtCorrect) {
    auto filtered = filterByExt(sample(), ".csv");
    for (const auto& r : filtered)
        EXPECT_EQ(r.extension, ".csv");
}

TEST(AlgoTest, FilterReadonly) {
    auto ro = filterReadonly(sample());
    for (const auto& r : ro)
        EXPECT_TRUE(r.readonly);
}

TEST(AlgoTest, ExtractNamesCount) {
    auto v = sample();
    EXPECT_EQ(extractNames(v).size(), v.size());
}

TEST(AlgoTest, ExtractNamesContainExt) {
    auto v = sample();
    auto names = extractNames(v);
    for (std::size_t i = 0; i < v.size(); ++i)
        EXPECT_NE(names[i].find(v[i].extension), std::string::npos);
}

TEST(AlgoTest, ScaleSize) {
    auto v = sample();
    long long before = v[0].size;
    scaleSize(v, 2.0);
    EXPECT_EQ(v[0].size, before * 2);
}

TEST(AlgoTest, MarkAllReadonly) {
    auto v = sample();
    markAllReadonly(v);
    EXPECT_TRUE(std::all_of(v.begin(), v.end(),
        [](const FileRecord& r) { return r.readonly; }));
}

TEST(AlgoTest, RemoveDuplicateIds) {
    auto v = sample();
    v.push_back(v[0]);  // add duplicate
    v.push_back(v[1]);
    auto deduped = removeDuplicateIds(v);
    // all ids must be unique
    std::vector<int> ids;
    for (const auto& r : deduped) ids.push_back(r.id);
    auto it = std::adjacent_find(ids.begin(), ids.end());
    EXPECT_EQ(it, ids.end());
}

// ── Sorting ───────────────────────────────────────────────────────────

TEST(AlgoTest, SortById) {
    auto v = sample();
    sortById(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.id < b.id; }));
}

TEST(AlgoTest, SortBySizeAsc) {
    auto v = sample();
    sortBySizeAsc(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.size < b.size; }));
}

TEST(AlgoTest, SortBySizeDesc) {
    auto v = sample();
    sortBySizeDesc(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.size > b.size; }));
}

TEST(AlgoTest, SortByExt) {
    auto v = sample();
    sortByExt(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) {
            return a.extension < b.extension;
        }));
}

// ── Partitioning ──────────────────────────────────────────────────────

TEST(AlgoTest, PartitionSizes) {
    auto v = sample();
    auto [ro, rw] = partitionByReadonly(v);
    EXPECT_EQ(ro.size() + rw.size(), v.size());
}

TEST(AlgoTest, PartitionContents) {
    auto [ro, rw] = partitionByReadonly(sample());
    for (const auto& r : ro) EXPECT_TRUE(r.readonly);
    for (const auto& r : rw) EXPECT_FALSE(r.readonly);
}

// ── Set operations ────────────────────────────────────────────────────

TEST(AlgoTest, CollectIdsSorted) {
    auto ids = collectIds(sample());
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}

TEST(AlgoTest, IntersectSubset) {
    auto v = sample();
    auto ids1 = collectIds(v);
    auto ids2 = std::vector<int>{1, 3, 5, 7};
    auto inter = intersectIds(ids1, ids2);
    for (int id : inter) {
        EXPECT_NE(std::find(ids1.begin(), ids1.end(), id), ids1.end());
        EXPECT_NE(std::find(ids2.begin(), ids2.end(), id), ids2.end());
    }
}

TEST(AlgoTest, DifferenceExcludes) {
    auto ids1 = std::vector<int>{1, 2, 3, 4, 5};
    auto ids2 = std::vector<int>{3, 4};
    auto diff = differenceIds(ids1, ids2);
    EXPECT_EQ(diff, (std::vector<int>{1, 2, 5}));
}
