#include "file_record.hpp"
#include "simple_forward_list.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <ranges>

static_assert(std::forward_iterator<SimpleForwardList<FileRecord>::iterator>);
static_assert(std::forward_iterator<SimpleForwardList<FileRecord>::const_iterator>);
static_assert(std::ranges::forward_range<SimpleForwardList<FileRecord>>);

static SimpleForwardList<FileRecord> makeList() {
    SimpleForwardList<FileRecord> list;
    list.push_front({5, "video",   ".mp4", 102400, false});
    list.push_front({4, "archive", ".zip",  51200, true});
    list.push_front({3, "photo",   ".jpg",  20480, false});
    list.push_front({2, "config",  ".json",   512, true});
    list.push_front({1, "report",  ".txt",   2048, false});
    return list;
}

TEST(ForwardListAlgorithms, CountIfReadonly) {
    auto list = makeList();
    const auto n = std::count_if(list.begin(), list.end(),
        [](const FileRecord& r) { return r.readonly; });
    EXPECT_EQ(n, 2);
}

TEST(ForwardListAlgorithms, FindIfLargeFile) {
    auto list = makeList();
    auto it   = std::find_if(list.begin(), list.end(),
        [](const FileRecord& r) { return r.size > 50000; });
    ASSERT_NE(it, list.end());
    EXPECT_GT(it->size, 50000);
}

TEST(ForwardListAlgorithms, FindIfNotFound) {
    auto list = makeList();
    auto it   = std::find_if(list.begin(), list.end(),
        [](const FileRecord& r) { return r.size > 1000000; });
    EXPECT_EQ(it, list.end());
}

TEST(ForwardListAlgorithms, RangesCountIf) {
    auto list = makeList();
    const auto n = std::ranges::count_if(list,
        [](const FileRecord& r) { return r.readonly; });
    EXPECT_EQ(n, 2);
}

TEST(ForwardListAlgorithms, RangesFindIf) {
    auto list = makeList();
    auto it   = std::ranges::find_if(list,
        [](const FileRecord& r) { return r.extension == ".jpg"; });
    ASSERT_NE(it, list.end());
    EXPECT_EQ(it->extension, ".jpg");
}

TEST(ForwardListAlgorithms, ForEachMutation) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, false});
    std::for_each(list.begin(), list.end(), [](FileRecord& r) { r.readonly = true; });
    for (const auto& r : list) EXPECT_TRUE(r.readonly);
}
