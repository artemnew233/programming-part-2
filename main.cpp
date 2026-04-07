#include <iostream>
#include <memory>
#include "public/University.h"
#include "public/Department.h"
#include "public/Professor.h"
#include "public/Student.h"
#include "public/Course.h"

int main() {
    std::cout << "Laboratory Work 5: Aggregation" << std::endl;
    std::cout << "Variant 1: University Structure" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    // Create University
    auto myUniversity = std::make_shared<University>("NTU Kharkiv Polytechnic Institute");

    // Create Department
    auto csDepartment = std::make_shared<Department>("Computer Science");
    myUniversity->addDepartment(csDepartment);

    // Create Professors
    auto prof1 = std::make_shared<Professor>("Dr. Smith", "Professor");
    auto prof2 = std::make_shared<Professor>("Dr. Johnson", "Associate Professor");
    csDepartment->addProfessor(prof1);
    csDepartment->addProfessor(prof2);

    // Create Courses
    auto course1 = std::make_shared<Course>("Object-Oriented Programming", "CS101");
    auto course2 = std::make_shared<Course>("Data Structures", "CS102");
    course1->setProfessor(prof1);
    course2->setProfessor(prof2);
    csDepartment->addCourse(course1);
    csDepartment->addCourse(course2);

    // Create Students
    auto student1 = std::make_shared<Student>("Alice", "S001");
    auto student2 = std::make_shared<Student>("Bob", "S002");

    // Students enroll in courses (Aggregation)
    student1->enrollInCourse(course1);
    student1->enrollInCourse(course2);
    student2->enrollInCourse(course1);

    // Courses add students
    course1->addStudent(student1);
    course1->addStudent(student2);
    course2->addStudent(student1);

    // Display Information
    std::cout << "University: " << myUniversity->getName() << std::endl;
    for (const auto& dept : myUniversity->getDepartments()) {
        std::cout << "  Department: " << dept->getName() << std::endl;
        
        std::cout << "    Professors:" << std::endl;
        for (const auto& prof : dept->getProfessors()) {
            std::cout << "      - " << prof->getName() << " (" << prof->getRank() << ")" << std::endl;
        }

        std::cout << "    Courses:" << std::endl;
        for (const auto& course : dept->getCourses()) {
            std::cout << "      - " << course->getName() << " [" << course->getCode() << "]" << std::endl;
            if (course->getProfessor()) {
                std::cout << "        Taught by: " << course->getProfessor()->getName() << std::endl;
            }
            std::cout << "        Students enrolled: " << course->getStudents().size() << std::endl;
        }
    }

    std::cout << "\nStudent Enrollment Verification:" << std::endl;
    std::cout << "Student: " << student1->getName() << " is enrolled in:" << std::endl;
    for (const auto& course : student1->getEnrolledCourses()) {
        std::cout << "  - " << course->getName() << std::endl;
    }

    return 0;
}
