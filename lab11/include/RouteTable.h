#pragma once
#include <stdexcept>
#include <algorithm>

// Part 1: RouteTable<T, N> — fixed-capacity table of route distances/times.
// Uses a raw array internally; tracks logical size separately.
template <typename T, int N>
class RouteTable {
    static_assert(N > 0, "RouteTable capacity must be positive");
public:
    RouteTable() : size_(0) {}

    // Add a route metric; throws if full.
    void set(int index, T value) {
        if (index < 0 || index >= N)
            throw std::out_of_range("RouteTable::set: index out of range");
        data_[index] = value;
        if (index >= size_) size_ = index + 1;
    }

    T get(int index) const {
        if (index < 0 || index >= size_)
            throw std::out_of_range("RouteTable::get: index out of range");
        return data_[index];
    }

    int count() const { return size_; }
    bool empty() const { return size_ == 0; }
    int capacity() const { return N; }

    T longest() const {
        if (size_ == 0) throw std::logic_error("RouteTable is empty");
        T best = data_[0];
        for (int i = 1; i < size_; ++i) if (data_[i] > best) best = data_[i];
        return best;
    }

    T shortest() const {
        if (size_ == 0) throw std::logic_error("RouteTable is empty");
        T best = data_[0];
        for (int i = 1; i < size_; ++i) if (data_[i] < best) best = data_[i];
        return best;
    }

    double average() const {
        if (size_ == 0) throw std::logic_error("RouteTable is empty");
        double sum = 0.0;
        for (int i = 0; i < size_; ++i) sum += static_cast<double>(data_[i]);
        return sum / size_;
    }

private:
    T data_[N];
    int size_;
};
