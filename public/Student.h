#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <memory>

class Course;

class Student {
public:
    Student(const std::string& name, const std::string& studentID);
    void enrollInCourse(std::shared_ptr<Course> course);
    std::string getName() const;
    std::string getStudentID() const;
    const std::vector<std::shared_ptr<Course>>& getEnrolledCourses() const;

private:
    std::string name;
    std::string studentID;
    std::vector<std::shared_ptr<Course>> enrolledCourses;
};

#endif
