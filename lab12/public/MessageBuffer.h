#pragma once
#include "Message.h"
#include <cstddef>
#include <stdexcept>

// Owns a dynamic array of Message objects.
// Demonstrates Rule of Three and Rule of Five.
class MessageBuffer {
public:
    explicit MessageBuffer(std::size_t capacity);
    ~MessageBuffer();

    // Rule of Three
    MessageBuffer(const MessageBuffer& other);
    MessageBuffer& operator=(const MessageBuffer& other);

    // Rule of Five (adds move)
    MessageBuffer(MessageBuffer&& other) noexcept;
    MessageBuffer& operator=(MessageBuffer&& other) noexcept;

    void           add(const Message& msg);
    Message&       operator[](std::size_t index);
    const Message& operator[](std::size_t index) const;
    std::size_t    size()     const { return size_; }
    std::size_t    capacity() const { return capacity_; }
    void           print()    const;

private:
    Message*    data_;
    std::size_t size_;
    std::size_t capacity_;
};
