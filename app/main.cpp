#include <fmt/core.h>
#include "calculator.hpp"

int main() {
    fmt::print("Console Calculator\n");
    fmt::print("------------------\n");
    fmt::print("10 + 3 = {}\n", add(10, 3));
    fmt::print("10 - 3 = {}\n", sub(10, 3));
    fmt::print("10 * 3 = {}\n", mul(10, 3));
    fmt::print("10 / 3 = {:.4f}\n", divide(10, 3));
    return 0;
}
