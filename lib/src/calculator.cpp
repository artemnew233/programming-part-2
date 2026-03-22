#include "calculator.hpp"
#include <stdexcept>

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0.0)
        throw std::invalid_argument("Division by zero");
    return a / b;
}
