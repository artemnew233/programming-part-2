#include "DomainTypes.h"
#include "Message.h"
#include "MessageBuffer.h"
#include "SimplePtr.h"

#include <iostream>
#include <memory>
#include <utility>

// ── Task 2: Manual new[] / delete[] ────────────────────────────────────
static void task2_manualArray() {
    std::cout << "\n=== Task 2: Manual new[] / delete[] ===\n";
    constexpr std::size_t N = 4;
    Message* msgs = new Message[N]{
        {1, "Alice", "Hello!"},
        {2, "Bob",   "Hi Alice"},
        {3, "Alice", "How are you?"},
        {4, "Bob",   "Great, thanks!"}
    };
    for (std::size_t i = 0; i < N; ++i) msgs[i].print();
    // delete msgs;  ← WRONG: new[] requires delete[], not delete
    delete[] msgs;
    msgs = nullptr;
    std::cout << "Memory released with delete[]\n";
}

// ── Task 3: MessageBuffer ───────────────────────────────────────────────
static void task3_buffer() {
    std::cout << "\n=== Task 3: MessageBuffer ===\n";
    MessageBuffer buf(5);
    buf.add({1, "Alice", "Morning!"});
    buf.add({2, "Bob",   "Hey"});
    buf.add({3, "Carol", "What's up?"});
    buf.print();
    std::cout << "buf[1]: "; buf[1].print();
}

// ── Task 4: Rule of Three ──────────────────────────────────────────────
static void task4_ruleOfThree() {
    std::cout << "\n=== Task 4: Rule of Three (deep copy) ===\n";
    MessageBuffer buf1(3);
    buf1.add({1, "Alice", "Original"});

    MessageBuffer buf2 = buf1;            // copy constructor — deep copy
    buf2[0].content    = "Modified copy";

    // buf1 is unaffected because the copy was deep (separate arrays)
    std::cout << "buf1[0]: "; buf1[0].print();
    std::cout << "buf2[0]: "; buf2[0].print();

    MessageBuffer buf3(2);
    buf3 = buf1;                           // copy assignment
    std::cout << "buf3[0]: "; buf3[0].print();
}

// ── Task 5: Rule of Five ───────────────────────────────────────────────
static MessageBuffer makeBuffer() {
    MessageBuffer tmp(3);
    tmp.add({10, "Server", "Auto-generated message"});
    return tmp;
}

static void task5_ruleOfFive() {
    std::cout << "\n=== Task 5: Rule of Five (move) ===\n";
    MessageBuffer moved = makeBuffer();     // move/NRVO from factory
    moved.print();

    MessageBuffer other(2);
    other.add({99, "System", "ping"});
    other = std::move(moved);              // move assignment
    other.print();
    std::cout << "Moved-from size: " << moved.size() << " (valid empty state)\n";
}

// ── Task 6: SimplePtr ──────────────────────────────────────────────────
static void task6_simplePtr() {
    std::cout << "\n=== Task 6: SimplePtr ===\n";
    SimplePtr<Message> ptr(new Message(1, "Alice", "SimplePtr owns this"));
    std::cout << "operator->: "; ptr->print();
    std::cout << "operator*:  "; (*ptr).print();

    SimplePtr<Message> moved = std::move(ptr);
    std::cout << "After move, original is null: "
              << (ptr.get() == nullptr ? "yes" : "no") << '\n';
    std::cout << "Moved-into: "; moved->print();
}

// ── Task 7: unique_ptr ────────────────────────────────────────────────
static void task7_uniquePtr() {
    std::cout << "\n=== Task 7: unique_ptr ===\n";

    auto msg  = std::make_unique<Message>(1, "Alice", "unique_ptr owns this");
    auto msg2 = std::move(msg);
    std::cout << "After move, msg is null: " << (msg == nullptr ? "yes" : "no") << '\n';
    std::cout << "msg2: "; msg2->print();

    // unique_ptr for array
    auto arr = std::make_unique<Message[]>(3);
    arr[0] = {10, "A", "first"};
    arr[1] = {11, "B", "second"};
    arr[2] = {12, "C", "third"};
    for (int i = 0; i < 3; ++i) arr[i].print();
}

// ── Task 7b: class with unique_ptr field ─────────────────────────────
static void task7b_classField() {
    std::cout << "\n=== Task 7b: MessageQueue (unique_ptr field) ===\n";
    {
        MessageQueue mq("general");
        mq.send({1, "Alice", "Hello from MessageQueue!"});
        mq.printHandle();
    } // ~MessageQueue calls closeMessageQueue automatically
    std::cout << "MessageQueue out of scope — handle released\n";
}

// ── Task 8: Custom deleter ────────────────────────────────────────────
static void task8_customDeleter() {
    std::cout << "\n=== Task 8: Custom deleter (closeMessageQueue) ===\n";
    {
        std::unique_ptr<MessageQueueHandle, decltype(&closeMessageQueue)>
            handle(new MessageQueueHandle(7, "alerts"), &closeMessageQueue);
        std::cout << "Handle in use: " << handle->name << '\n';
    } // closeMessageQueue called here — NOT plain delete
    std::cout << "Scope ended — custom deleter ran\n";
}

// ── Task 9: shared_ptr ────────────────────────────────────────────────
static void task9_sharedPtr() {
    std::cout << "\n=== Task 9: shared_ptr (ChatRoom / ChatMessage) ===\n";

    auto room = std::make_shared<ChatRoom>("general");
    std::cout << "use_count after make_shared: " << room.use_count() << '\n';

    // ChatMessage stores a weak_ptr to room — use_count stays at 1
    auto m1 = std::make_shared<ChatMessage>(1, "Hello everyone!", room);
    auto m2 = std::make_shared<ChatMessage>(2, "Hey!", room);
    std::cout << "use_count (ChatMessage holds weak_ptr): "
              << room.use_count() << '\n';

    room->addMessage(m1);
    room->addMessage(m2);
    room->printMessages();

    auto room2 = room;
    std::cout << "use_count with two owners: " << room.use_count() << '\n';
    room2.reset();
    std::cout << "use_count after room2.reset(): " << room.use_count() << '\n';
}

// ── Task 10: weak_ptr — cyclic dependency ─────────────────────────────
static void task10_weakPtr() {
    std::cout << "\n=== Task 10: weak_ptr — doubly linked list cycle fix ===\n";

    // BROKEN (two shared_ptrs → cycle → leak, never shown in running code):
    // { auto a = make_shared<BadNode>(); auto b = make_shared<BadNode>();
    //   a->next = b; b->previous_shared = a; }  // a and b never destroyed

    // FIXED: Node::previous is std::weak_ptr → does not increment use_count
    {
        auto a = std::make_shared<Node>(1);
        auto b = std::make_shared<Node>(2);
        a->next     = b;   // strong: b.use_count → 2
        b->previous = a;   // weak:   a.use_count stays 1

        std::cout << "a.use_count: " << a.use_count() << " (only 'a' owns it)\n";
        std::cout << "b.use_count: " << b.use_count() << " (a->next + 'b')\n";

        if (auto prev = b->previous.lock())
            std::cout << "b->previous value: " << prev->value << '\n';
    }
    std::cout << "Both Nodes destroyed — no leak\n";
}

int main() {
    task2_manualArray();
    task3_buffer();
    task4_ruleOfThree();
    task5_ruleOfFive();
    task6_simplePtr();
    task7_uniquePtr();
    task7b_classField();
    task8_customDeleter();
    task9_sharedPtr();
    task10_weakPtr();
    return 0;
}
