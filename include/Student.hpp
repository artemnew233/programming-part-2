#pragma once

class Student {
public:
    Student(int id, int course, double averageGrade, bool scholarship, int absences);

    int    getId()           const;
    int    getCourse()       const;
    double getAverageGrade() const;
    bool   getScholarship()  const;
    int    getAbsences()     const;

    void setId(int value);
    void setCourse(int value);
    void setAverageGrade(double value);
    void setScholarship(bool value);
    void setAbsences(int value);

    void promoteToNextCourse();
    void updateAverageGrade(double value);
    bool isExcellentStudent()    const;
    bool canReceiveScholarship() const;
    void addAbsence();

private:
    int    m_id;
    int    m_course;
    double m_averageGrade;
    bool   m_scholarship;
    int    m_absences;
};
