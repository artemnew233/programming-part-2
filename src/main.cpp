#include <iostream>
#include "Student.hpp"

int main() {
    Student s(1, 2, 85.0, true, 2);

    std::cout << "=== Student Info ===\n";
    std::cout << "ID:            " << s.getId() << "\n";
    std::cout << "Course:        " << s.getCourse() << "\n";
    std::cout << "Average grade: " << s.getAverageGrade() << "\n";
    std::cout << "Scholarship:   " << (s.getScholarship() ? "yes" : "no") << "\n";
    std::cout << "Absences:      " << s.getAbsences() << "\n";

    std::cout << "\n=== Methods ===\n";
    std::cout << "Excellent student: " << (s.isExcellentStudent() ? "yes" : "no") << "\n";
    std::cout << "Can receive scholarship: " << (s.canReceiveScholarship() ? "yes" : "no") << "\n";

    s.addAbsence();
    s.addAbsence();
    s.addAbsence();
    std::cout << "After 3 absences: " << s.getAbsences() << "\n";

    s.updateAverageGrade(92.5);
    std::cout << "After grade update: " << s.getAverageGrade() << "\n";
    std::cout << "Excellent now: " << (s.isExcellentStudent() ? "yes" : "no") << "\n";

    s.promoteToNextCourse();
    std::cout << "After promotion, course: " << s.getCourse() << "\n";

    return 0;
}
