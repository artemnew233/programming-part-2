#pragma once
#include <stdexcept>
#include <type_traits>

template <typename T>
T longerSegment(T a, T b) {
    return (a >= b) ? a : b;
}


template <typename T>
int countSegmentsInRange(const T* arr, int n, T lo, T hi) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= lo && arr[i] <= hi) ++count;
    }
    return count;
}


template <typename D, typename T>
auto averageSpeed(D distance, T time)
    -> decltype(distance / time)
{
    static_assert(std::is_arithmetic<D>::value, "distance must be arithmetic");
    static_assert(std::is_arithmetic<T>::value, "time must be arithmetic");

    if (time == T{0}) {
        throw std::invalid_argument("averageSpeed: time must not be zero");
    }
    return distance / time;
}
