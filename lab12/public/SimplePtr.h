#pragma once

// Teaching RAII wrapper around a raw pointer.
// Acquires ownership in the constructor, releases in the destructor.
// Copying is prohibited; move is supported.
template <typename T>
class SimplePtr {
public:
    explicit SimplePtr(T* ptr) : ptr_(ptr) {}

    ~SimplePtr() { delete ptr_; }

    SimplePtr(const SimplePtr&)            = delete;
    SimplePtr& operator=(const SimplePtr&) = delete;

    SimplePtr(SimplePtr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }
    SimplePtr& operator=(SimplePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_       = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator*()  const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get()        const { return ptr_; }

private:
    T* ptr_;
};
