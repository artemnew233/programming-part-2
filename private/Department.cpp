#include "../public/Department.h"
#include "../public/Professor.h"
#include "../public/Course.h"

Department::Department(const std::string& name) : name(name) {}

void Department::addProfessor(std::shared_ptr<Professor> professor) {
    professors.push_back(professor);
}

void Department::addCourse(std::shared_ptr<Course> course) {
    courses.push_back(course);
}

std::string Department::getName() const {
    return name;
}

const std::vector<std::shared_ptr<Professor>>& Department::getProfessors() const {
    return professors;
}

const std::vector<std::shared_ptr<Course>>& Department::getCourses() const {
    return courses;
}
