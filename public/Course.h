#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <memory>

class Professor;
class Student;

class Course {
public:
    Course(const std::string& name, const std::string& code);
    void setProfessor(std::shared_ptr<Professor> professor);
    void addStudent(std::shared_ptr<Student> student);
    std::string getName() const;
    std::string getCode() const;
    std::shared_ptr<Professor> getProfessor() const;
    const std::vector<std::shared_ptr<Student>>& getStudents() const;

private:
    std::string name;
    std::string code;
    std::shared_ptr<Professor> professor;
    std::vector<std::shared_ptr<Student>> students;
};

#endif
