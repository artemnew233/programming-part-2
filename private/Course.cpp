#include "../public/Course.h"
#include "../public/Professor.h"
#include "../public/Student.h"

Course::Course(const std::string& name, const std::string& code) : name(name), code(code) {}

void Course::setProfessor(std::shared_ptr<Professor> prof) {
    professor = prof;
}

void Course::addStudent(std::shared_ptr<Student> student) {
    students.push_back(student);
}

std::string Course::getName() const {
    return name;
}

std::string Course::getCode() const {
    return code;
}

std::shared_ptr<Professor> Course::getProfessor() const {
    return professor;
}

const std::vector<std::shared_ptr<Student>>& Course::getStudents() const {
    return students;
}
