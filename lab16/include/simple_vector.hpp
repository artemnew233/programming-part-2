#pragma once
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <typename T, typename Allocator = std::allocator<T>>
class SimpleVector {
public:
    using value_type      = T;
    using allocator_type  = Allocator;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer   = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator        = T*;
    using const_iterator  = const T*;

    SimpleVector() = default;

    SimpleVector(std::initializer_list<T> values) {
        reserve(values.size());
        try {
            for (const auto& v : values) emplace_back(v);
        } catch (...) {
            clear();
            release_storage();
            throw;
        }
    }

    SimpleVector(const SimpleVector& other) {
        reserve(other.size_);
        try {
            for (const auto& v : other) emplace_back(v);
        } catch (...) {
            clear();
            release_storage();
            throw;
        }
    }

    SimpleVector(SimpleVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_     = nullptr;
        other.size_     = 0;
        other.capacity_ = 0;
    }

    SimpleVector& operator=(SimpleVector other) noexcept(std::is_nothrow_swappable_v<T>) {
        swap(other);
        return *this;
    }

    ~SimpleVector() {
        clear();
        release_storage();
    }

    void swap(SimpleVector& other) noexcept {
        using std::swap;
        swap(data_,     other.data_);
        swap(size_,     other.size_);
        swap(capacity_, other.capacity_);
    }

    [[nodiscard]] size_type size()     const noexcept { return size_; }
    [[nodiscard]] size_type capacity() const noexcept { return capacity_; }
    [[nodiscard]] bool      empty()    const noexcept { return size_ == 0; }

    pointer       data()       noexcept { return data_; }
    const_pointer data() const noexcept { return data_; }

    reference       operator[](size_type i)       noexcept { return data_[i]; }
    const_reference operator[](size_type i) const noexcept { return data_[i]; }

    reference at(size_type i) {
        if (i >= size_) throw std::out_of_range("SimpleVector::at");
        return data_[i];
    }
    const_reference at(size_type i) const {
        if (i >= size_) throw std::out_of_range("SimpleVector::at");
        return data_[i];
    }

    reference       front()       { return data_[0]; }
    const_reference front() const { return data_[0]; }
    reference       back()        { return data_[size_ - 1]; }
    const_reference back()  const { return data_[size_ - 1]; }

    void reserve(size_type new_capacity) {
        if (new_capacity <= capacity_) return;
        pointer   new_data    = traits::allocate(allocator_, new_capacity);
        size_type constructed = 0;
        try {
            for (; constructed < size_; ++constructed)
                traits::construct(allocator_, new_data + constructed,
                                  std::move_if_noexcept(data_[constructed]));
        } catch (...) {
            destroy_range(new_data, constructed);
            traits::deallocate(allocator_, new_data, new_capacity);
            throw;
        }
        clear();
        release_storage();
        data_     = new_data;
        size_     = constructed;
        capacity_ = new_capacity;
    }

    void resize(size_type new_size) {
        if (new_size < size_) {
            for (size_type i = new_size; i < size_; ++i)
                traits::destroy(allocator_, data_ + i);
            size_ = new_size;
            return;
        }
        if (new_size > capacity_) reserve(growth_capacity(new_size));
        for (; size_ < new_size; ++size_)
            traits::construct(allocator_, data_ + size_);
    }

    void push_back(const T& value) { emplace_back(value); }
    void push_back(T&& value)      { emplace_back(std::move(value)); }

    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (size_ == capacity_) reserve(growth_capacity(size_ + 1));
        traits::construct(allocator_, data_ + size_, std::forward<Args>(args)...);
        ++size_;
        return back();
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("SimpleVector::pop_back");
        --size_;
        traits::destroy(allocator_, data_ + size_);
    }

    void clear() noexcept {
        for (size_type i = 0; i < size_; ++i)
            traits::destroy(allocator_, data_ + i);
        size_ = 0;
    }

    iterator       begin()  noexcept { return data_; }
    iterator       end()    noexcept { return data_ + size_; }
    const_iterator begin()  const noexcept { return data_; }
    const_iterator end()    const noexcept { return data_ + size_; }
    const_iterator cbegin() const noexcept { return data_; }
    const_iterator cend()   const noexcept { return data_ + size_; }

private:
    using traits = std::allocator_traits<Allocator>;

    pointer   data_{};
    size_type size_{};
    size_type capacity_{};
    Allocator allocator_{};

    static size_type growth_capacity(size_type required) {
        size_type next = required < 2 ? 2 : required;
        while (next < required) next *= 2;
        return next;
    }

    void destroy_range(pointer d, size_type count) noexcept {
        for (size_type i = 0; i < count; ++i)
            traits::destroy(allocator_, d + i);
    }

    void release_storage() noexcept {
        if (data_) {
            traits::deallocate(allocator_, data_, capacity_);
            data_     = nullptr;
            capacity_ = 0;
        }
    }
};

template <typename T, typename A>
void swap(SimpleVector<T, A>& l, SimpleVector<T, A>& r) noexcept { l.swap(r); }
