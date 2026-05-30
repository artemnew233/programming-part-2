#include "MessageBuffer.h"
#include <algorithm>
#include <iostream>

MessageBuffer::MessageBuffer(std::size_t capacity)
    : data_(new Message[capacity]{}), size_(0), capacity_(capacity) {
    std::cout << "[MessageBuffer] Constructed (capacity=" << capacity << ")\n";
}

MessageBuffer::~MessageBuffer() {
    delete[] data_;
    std::cout << "[MessageBuffer] Destroyed\n";
}

// Deep copy: allocate a new array and copy every element, just how i learned about it today XD.
MessageBuffer::MessageBuffer(const MessageBuffer& other)
    : data_(new Message[other.capacity_]{}),
      size_(other.size_),
      capacity_(other.capacity_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
    std::cout << "[MessageBuffer] Copy constructed\n";
}

MessageBuffer& MessageBuffer::operator=(const MessageBuffer& other) {
    if (this == &other) return *this;
    Message* newData = new Message[other.capacity_]{};
    std::copy(other.data_, other.data_ + other.size_, newData);
    delete[] data_;
    data_     = newData;
    size_     = other.size_;
    capacity_ = other.capacity_;
    std::cout << "[MessageBuffer] Copy assigned\n";
    return *this;
}

// transfer ownership without copying shi.
// The moved-from object is left in an empty state and i think it is also "valid" state, maybe, mayhaps.
MessageBuffer::MessageBuffer(MessageBuffer&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_     = nullptr;
    other.size_     = 0;
    other.capacity_ = 0;
    std::cout << "[MessageBuffer] Move constructed\n";
}

MessageBuffer& MessageBuffer::operator=(MessageBuffer&& other) noexcept {
    if (this == &other) return *this;
    delete[] data_;
    data_           = other.data_;
    size_           = other.size_;
    capacity_       = other.capacity_;
    other.data_     = nullptr;
    other.size_     = 0;
    other.capacity_ = 0;
    std::cout << "[MessageBuffer] Move assigned\n";
    return *this;
}

void MessageBuffer::add(const Message& msg) {
    if (size_ >= capacity_)
        throw std::runtime_error("MessageBuffer: buffer is full");
    data_[size_++] = msg;
}

Message& MessageBuffer::operator[](std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("MessageBuffer: index out of range");
    return data_[index];
}

const Message& MessageBuffer::operator[](std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("MessageBuffer: index out of range");
    return data_[index];
}

void MessageBuffer::print() const {
    std::cout << "MessageBuffer (" << size_ << "/" << capacity_ << "):\n";
    for (std::size_t i = 0; i < size_; ++i)
        data_[i].print();
}
