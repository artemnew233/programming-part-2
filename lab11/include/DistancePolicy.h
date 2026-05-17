#pragma once
#include <cmath>

// Part 2b: DistancePolicy<T> — arithmetic precision policy.
// Primary template: integer distances use exact equality.
template <typename T>
struct DistancePolicy {
    static bool equal(T a, T b) { return a == b; }
    static constexpr T epsilon() { return T{0}; }
};

// Full specialization for double: near-zero epsilon for approximate comparisons.
template <>
struct DistancePolicy<double> {
    static bool equal(double a, double b) {
        return std::fabs(a - b) <= epsilon();
    }
    static constexpr double epsilon() { return 1e-9; }
};

// Partial specialization for float: similarly approximate.
template <>
struct DistancePolicy<float> {
    static bool equal(float a, float b) {
        return std::fabs(a - b) <= epsilon();
    }
    static constexpr float epsilon() { return 1e-5f; }
};
