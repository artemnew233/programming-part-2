#include "../public/Student.h"
#include "../public/Course.h"

Student::Student(const std::string& name, const std::string& studentID) : name(name), studentID(studentID) {}

void Student::enrollInCourse(std::shared_ptr<Course> course) {
    enrolledCourses.push_back(course);
}

std::string Student::getName() const {
    return name;
}

std::string Student::getStudentID() const {
    return studentID;
}

const std::vector<std::shared_ptr<Course>>& Student::getEnrolledCourses() const {
    return enrolledCourses;
}
