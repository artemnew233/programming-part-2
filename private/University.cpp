#include "../public/University.h"

University::University(const std::string& name) : name(name) {}

void University::addDepartment(std::shared_ptr<Department> department) {
    departments.push_back(department);
}

std::string University::getName() const {
    return name;
}

const std::vector<std::shared_ptr<Department>>& University::getDepartments() const {
    return departments;
}
