#include <gtest/gtest.h>
#include "DomainTypes.h"
#include "Message.h"
#include "MessageBuffer.h"
#include "SimplePtr.h"
#include <memory>

// ── MessageBuffer ─────────────────────────────────────────────────────

TEST(MessageBufferTest, InitialState) {
    MessageBuffer buf(4);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_EQ(buf.capacity(), 4u);
}

TEST(MessageBufferTest, AddAndSize) {
    MessageBuffer buf(3);
    buf.add({1, "Alice", "Hi"});
    buf.add({2, "Bob",   "Hello"});
    EXPECT_EQ(buf.size(), 2u);
}

TEST(MessageBufferTest, IndexAccess) {
    MessageBuffer buf(3);
    buf.add({1, "Alice", "Hi"});
    EXPECT_EQ(buf[0].sender, "Alice");
    EXPECT_EQ(buf[0].id,     1);
}

TEST(MessageBufferTest, OutOfBoundsThrows) {
    MessageBuffer buf(2);
    buf.add({1, "A", "msg"});
    EXPECT_THROW(buf[5], std::out_of_range);
}

TEST(MessageBufferTest, FullThrows) {
    MessageBuffer buf(1);
    buf.add({1, "A", "msg"});
    EXPECT_THROW(buf.add({2, "B", "msg2"}), std::runtime_error);
}

// ── Rule of Three ─────────────────────────────────────────────────────

TEST(MessageBufferTest, DeepCopyConstructor) {
    MessageBuffer buf1(3);
    buf1.add({1, "A", "original"});
    MessageBuffer buf2 = buf1;
    buf2[0].content    = "modified";
    EXPECT_EQ(buf1[0].content, "original");
    EXPECT_EQ(buf2[0].content, "modified");
}

TEST(MessageBufferTest, DeepCopyAssignment) {
    MessageBuffer buf1(3);
    buf1.add({1, "A", "original"});
    MessageBuffer buf2(2);
    buf2 = buf1;
    buf2[0].content = "modified";
    EXPECT_EQ(buf1[0].content, "original");
}

TEST(MessageBufferTest, SelfAssignment) {
    MessageBuffer buf(2);
    buf.add({1, "A", "msg"});
    buf = buf;
    EXPECT_EQ(buf[0].sender, "A");
}

// ── Rule of Five ──────────────────────────────────────────────────────

TEST(MessageBufferTest, MoveConstructor) {
    MessageBuffer buf1(3);
    buf1.add({1, "A", "msg"});
    MessageBuffer buf2 = std::move(buf1);
    EXPECT_EQ(buf2.size(), 1u);
    EXPECT_EQ(buf1.size(), 0u);
}

TEST(MessageBufferTest, MoveAssignment) {
    MessageBuffer buf1(3);
    buf1.add({1, "A", "msg"});
    MessageBuffer buf2(2);
    buf2 = std::move(buf1);
    EXPECT_EQ(buf2[0].sender, "A");
    EXPECT_EQ(buf1.size(), 0u);
}

// ── SimplePtr ─────────────────────────────────────────────────────────

TEST(SimplePtrTest, Dereference) {
    SimplePtr<Message> p(new Message(1, "Alice", "hello"));
    EXPECT_EQ(p->sender, "Alice");
    EXPECT_EQ((*p).id, 1);
}

TEST(SimplePtrTest, MoveTransfersOwnership) {
    SimplePtr<Message> p1(new Message(1, "A", "msg"));
    SimplePtr<Message> p2 = std::move(p1);
    EXPECT_EQ(p2->sender, "A");
    EXPECT_EQ(p1.get(), nullptr);
}

// ── Custom deleter ────────────────────────────────────────────────────

TEST(CustomDeleterTest, DeleterCalled) {
    bool deleted = false;
    auto deleter = [&deleted](int* p) { deleted = true; delete p; };
    { std::unique_ptr<int, decltype(deleter)> p(new int(42), deleter); }
    EXPECT_TRUE(deleted);
}

TEST(CustomDeleterTest, CloseMessageQueueRuns) {
    std::unique_ptr<MessageQueueHandle, decltype(&closeMessageQueue)>
        h(new MessageQueueHandle(1, "test"), &closeMessageQueue);
    EXPECT_TRUE(h->open);
    // destructor runs closeMessageQueue — no crash = pass
}

// ── shared_ptr / weak_ptr ─────────────────────────────────────────────

TEST(SharedPtrTest, UseCount) {
    auto room = std::make_shared<ChatRoom>("test");
    EXPECT_EQ(room.use_count(), 1);
    { auto r2 = room; EXPECT_EQ(room.use_count(), 2); }
    EXPECT_EQ(room.use_count(), 1);
}

TEST(WeakPtrTest, ExpiresAfterOwnerGone) {
    std::weak_ptr<ChatRoom> weak;
    { auto room = std::make_shared<ChatRoom>("temp"); weak = room; }
    EXPECT_TRUE(weak.expired());
}

TEST(WeakPtrTest, NodeCycleDestroyedCleanly) {
    std::weak_ptr<Node> wa, wb;
    {
        auto a = std::make_shared<Node>(1);
        auto b = std::make_shared<Node>(2);
        a->next     = b;
        b->previous = a;
        wa = a; wb = b;
    }
    EXPECT_TRUE(wa.expired());
    EXPECT_TRUE(wb.expired());
}
