#include "file_record.hpp"
#include "simple_forward_list.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

TEST(ForwardListBasic, EmptyReportsEmpty) {
    SimpleForwardList<FileRecord> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
    EXPECT_THROW((void)list.front(), std::out_of_range);
}

TEST(ForwardListBasic, PushFrontAndSize) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, false});
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.front().id, 2);
}

TEST(ForwardListBasic, PopFront) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, false});
    list.pop_front();
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.front().id, 1);
}

TEST(ForwardListBasic, PopFrontEmptyThrows) {
    SimpleForwardList<FileRecord> list;
    EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(ForwardListBasic, RangeFor) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, true});
    int count = 0;
    for (const auto& r : list) { EXPECT_GT(r.id, 0); ++count; }
    EXPECT_EQ(count, 2);
}

TEST(ForwardListBasic, InsertAfter) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, false});
    auto it = list.insert_after(list.begin(), {3, "c", ".txt", 300, false});
    EXPECT_EQ(it->id, 3);
    EXPECT_EQ(list.size(), 3u);
}

TEST(ForwardListBasic, EraseAfter) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, false});
    list.push_front({3, "c", ".txt", 300, false});
    auto next = list.erase_after(list.begin());
    EXPECT_EQ(next->id, 1);
    EXPECT_EQ(list.size(), 2u);
}

TEST(ForwardListBasic, InsertAfterEndThrows) {
    SimpleForwardList<FileRecord> list;
    EXPECT_THROW(list.insert_after(list.end(), {1, "a", ".txt", 100, false}),
                 std::out_of_range);
}

TEST(ForwardListBasic, EraseAfterLastThrows) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    EXPECT_THROW(list.erase_after(list.begin()), std::out_of_range);
}

TEST(ForwardListBasic, CopyConstructor) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    SimpleForwardList<FileRecord> copy = list;
    EXPECT_EQ(copy.size(), 1u);
    EXPECT_EQ(copy.front().id, 1);
}

TEST(ForwardListBasic, MoveConstructor) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    SimpleForwardList<FileRecord> moved = std::move(list);
    EXPECT_EQ(moved.size(), 1u);
    EXPECT_EQ(list.size(), 0u);
}

TEST(ForwardListBasic, EmplaceFront) {
    SimpleForwardList<FileRecord> list;
    auto& ref = list.emplace_front(FileRecord{1, "a", ".txt", 100, false});
    EXPECT_EQ(ref.id, 1);
    EXPECT_EQ(list.size(), 1u);
}

TEST(ForwardListBasic, Clear) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, false});
    list.clear();
    EXPECT_TRUE(list.empty());
}
