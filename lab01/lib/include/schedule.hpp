#pragma once
#include <string>
#include <vector>

void        addClass(std::vector<std::string>& schedule, const std::string& name);
bool        removeClass(std::vector<std::string>& schedule, const std::string& name);
int         countPeriods(const std::vector<std::string>& schedule);
bool        hasClass(const std::vector<std::string>& schedule, const std::string& name);
std::string getClassAt(const std::vector<std::string>& schedule, int index);
