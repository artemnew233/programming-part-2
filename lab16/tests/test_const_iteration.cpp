#include "file_record.hpp"
#include "simple_forward_list.hpp"

#include <gtest/gtest.h>

TEST(ForwardListConst, ConstRefTraversal) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, true});

    const SimpleForwardList<FileRecord>& cref = list;
    int count = 0;
    for (const auto& r : cref) { EXPECT_GT(r.id, 0); ++count; }
    EXPECT_EQ(count, 2);
}

TEST(ForwardListConst, CbeginCend) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, true});

    const SimpleForwardList<FileRecord>& cref = list;
    auto it = cref.cbegin();
    ASSERT_NE(it, cref.cend());
    EXPECT_EQ(it->id, 2);
    ++it;
    ASSERT_NE(it, cref.cend());
    EXPECT_EQ(it->id, 1);
    ++it;
    EXPECT_EQ(it, cref.cend());
}

TEST(ForwardListConst, ConstIteratorPostfixIncrement) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});
    list.push_front({2, "b", ".txt", 200, true});

    auto it  = list.cbegin();
    auto old = it++;
    EXPECT_EQ(old->id, 2);
    EXPECT_EQ(it->id, 1);
}

TEST(ForwardListConst, ImplicitConversionFromIterator) {
    SimpleForwardList<FileRecord> list;
    list.push_front({1, "a", ".txt", 100, false});

    SimpleForwardList<FileRecord>::iterator       it  = list.begin();
    SimpleForwardList<FileRecord>::const_iterator cit = it;
    EXPECT_EQ(cit->id, 1);
}

TEST(ForwardListConst, EmptyConstList) {
    const SimpleForwardList<FileRecord> list;
    EXPECT_EQ(list.begin(), list.end());
    EXPECT_EQ(list.cbegin(), list.cend());
}
