#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include <memory>

class Professor;
class Course;

class Department {
public:
    Department(const std::string& name);
    void addProfessor(std::shared_ptr<Professor> professor);
    void addCourse(std::shared_ptr<Course> course);
    std::string getName() const;
    const std::vector<std::shared_ptr<Professor>>& getProfessors() const;
    const std::vector<std::shared_ptr<Course>>& getCourses() const;

private:
    std::string name;
    std::vector<std::shared_ptr<Professor>> professors;
    std::vector<std::shared_ptr<Course>> courses;
};

#endif
