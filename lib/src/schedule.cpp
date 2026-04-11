#include "schedule.hpp"
#include <algorithm>

void addClass(std::vector<std::string>& schedule, const std::string& name) {
    if (!name.empty())
        schedule.push_back(name);
}

bool removeClass(std::vector<std::string>& schedule, const std::string& name) {
    auto it = std::find(schedule.begin(), schedule.end(), name);
    if (it == schedule.end())
        return false;
    schedule.erase(it);
    return true;
}

int countPeriods(const std::vector<std::string>& schedule) {
    return static_cast<int>(schedule.size());
}

bool hasClass(const std::vector<std::string>& schedule, const std::string& name) {
    return std::find(schedule.begin(), schedule.end(), name) != schedule.end();
}

std::string getClassAt(const std::vector<std::string>& schedule, int index) {
    if (index < 0 || index >= static_cast<int>(schedule.size()))
        return "";
    return schedule[index];
}
