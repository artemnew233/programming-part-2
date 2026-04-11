#include <fmt/core.h>
#include <vector>
#include <string>
#include "schedule.hpp"

int main() {
    std::vector<std::string> monday;

    addClass(monday, "Math");
    addClass(monday, "Physics");
    addClass(monday, "C++ Programming");
    addClass(monday, "English");
    addClass(monday, "History");

    fmt::print("Class Schedule — Monday\n");
    fmt::print("-----------------------\n");
    fmt::print("Total periods: {}\n\n", countPeriods(monday));

    for (int i = 0; i < countPeriods(monday); ++i)
        fmt::print("Period {}: {}\n", i + 1, getClassAt(monday, i));

    fmt::print("\nHas 'Physics': {}\n", hasClass(monday, "Physics") ? "yes" : "no");
    fmt::print("Has 'Biology': {}\n",  hasClass(monday, "Biology")  ? "yes" : "no");

    removeClass(monday, "History");
    fmt::print("\nAfter removing 'History':\n");
    fmt::print("Total periods: {}\n", countPeriods(monday));

    for (int i = 0; i < countPeriods(monday); ++i)
        fmt::print("Period {}: {}\n", i + 1, getClassAt(monday, i));

    return 0;
}
