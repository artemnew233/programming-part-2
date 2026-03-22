#include "Student.hpp"

Student::Student(int id, int course, double averageGrade, bool scholarship, int absences)
    : m_id(id),
      m_course(course > 0 ? course : 1),
      m_averageGrade(averageGrade >= 0.0 && averageGrade <= 100.0 ? averageGrade : 0.0),
      m_scholarship(scholarship),
      m_absences(absences >= 0 ? absences : 0) {}

int    Student::getId()           const { return m_id; }
int    Student::getCourse()       const { return m_course; }
double Student::getAverageGrade() const { return m_averageGrade; }
bool   Student::getScholarship()  const { return m_scholarship; }
int    Student::getAbsences()     const { return m_absences; }

void Student::setId(int value)              { m_id = value; }
void Student::setCourse(int value)          { if (value > 0) m_course = value; }
void Student::setAverageGrade(double value) { if (value >= 0.0 && value <= 100.0) m_averageGrade = value; }
void Student::setScholarship(bool value)    { m_scholarship = value; }
void Student::setAbsences(int value)        { if (value >= 0) m_absences = value; }

void Student::promoteToNextCourse() {
    m_course++;
}

void Student::updateAverageGrade(double value) {
    if (value >= 0.0 && value <= 100.0)
        m_averageGrade = value;
}

bool Student::isExcellentStudent() const {
    return m_averageGrade >= 90.0;
}

bool Student::canReceiveScholarship() const {
    return m_averageGrade >= 75.0 && m_absences <= 5;
}

void Student::addAbsence() {
    m_absences++;
}
