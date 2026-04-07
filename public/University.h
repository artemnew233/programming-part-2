#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <vector>
#include <memory>
#include "Department.h"

class University {
public:
    University(const std::string& name);
    void addDepartment(std::shared_ptr<Department> department);
    std::string getName() const;
    const std::vector<std::shared_ptr<Department>>& getDepartments() const;

private:
    std::string name;
    std::vector<std::shared_ptr<Department>> departments;
};

#endif
