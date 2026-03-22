#include <gtest/gtest.h>
#include "Student.hpp"

TEST(StudentConstructorTest, StoresValidValues) {
    Student s(1, 2, 85.0, true, 3);
    EXPECT_EQ(s.getId(), 1);
    EXPECT_EQ(s.getCourse(), 2);
    EXPECT_DOUBLE_EQ(s.getAverageGrade(), 85.0);
    EXPECT_TRUE(s.getScholarship());
    EXPECT_EQ(s.getAbsences(), 3);
}

TEST(StudentConstructorTest, InvalidCourseDefaultsToOne) {
    Student s(1, -1, 80.0, false, 0);
    EXPECT_EQ(s.getCourse(), 1);
}

TEST(StudentConstructorTest, InvalidGradeDefaultsToZero) {
    Student s(1, 1, 150.0, false, 0);
    EXPECT_DOUBLE_EQ(s.getAverageGrade(), 0.0);
}

TEST(StudentGetterSetterTest, SetCourse) {
    Student s(1, 1, 80.0, false, 0);
    s.setCourse(3);
    EXPECT_EQ(s.getCourse(), 3);
}

TEST(StudentGetterSetterTest, SetCourseIgnoresInvalid) {
    Student s(1, 2, 80.0, false, 0);
    s.setCourse(-5);
    EXPECT_EQ(s.getCourse(), 2);
}

TEST(StudentGetterSetterTest, SetAverageGrade) {
    Student s(1, 1, 50.0, false, 0);
    s.setAverageGrade(95.0);
    EXPECT_DOUBLE_EQ(s.getAverageGrade(), 95.0);
}

TEST(StudentGetterSetterTest, SetAbsences) {
    Student s(1, 1, 80.0, false, 0);
    s.setAbsences(10);
    EXPECT_EQ(s.getAbsences(), 10);
}

TEST(StudentMethodTest, PromoteToNextCourse) {
    Student s(1, 2, 80.0, false, 0);
    s.promoteToNextCourse();
    EXPECT_EQ(s.getCourse(), 3);
}

TEST(StudentMethodTest, UpdateAverageGrade) {
    Student s(1, 1, 60.0, false, 0);
    s.updateAverageGrade(88.0);
    EXPECT_DOUBLE_EQ(s.getAverageGrade(), 88.0);
}

TEST(StudentMethodTest, IsExcellentStudentTrue) {
    Student s(1, 1, 92.0, false, 0);
    EXPECT_TRUE(s.isExcellentStudent());
}

TEST(StudentMethodTest, IsExcellentStudentFalse) {
    Student s(1, 1, 75.0, false, 0);
    EXPECT_FALSE(s.isExcellentStudent());
}

TEST(StudentMethodTest, CanReceiveScholarshipTrue) {
    Student s(1, 1, 80.0, false, 3);
    EXPECT_TRUE(s.canReceiveScholarship());
}

TEST(StudentMethodTest, CanReceiveScholarshipFalseGrade) {
    Student s(1, 1, 60.0, false, 0);
    EXPECT_FALSE(s.canReceiveScholarship());
}

TEST(StudentMethodTest, CanReceiveScholarshipFalseTooManyAbsences) {
    Student s(1, 1, 90.0, false, 10);
    EXPECT_FALSE(s.canReceiveScholarship());
}

TEST(StudentMethodTest, AddAbsence) {
    Student s(1, 1, 80.0, false, 2);
    s.addAbsence();
    EXPECT_EQ(s.getAbsences(), 3);
}

TEST(StudentBoundaryTest, ExactExcellentThreshold) {
    Student s(1, 1, 90.0, false, 0);
    EXPECT_TRUE(s.isExcellentStudent());
}

TEST(StudentBoundaryTest, ExactScholarshipAbsenceLimit) {
    Student s(1, 1, 80.0, false, 5);
    EXPECT_TRUE(s.canReceiveScholarship());
    s.addAbsence();
    EXPECT_FALSE(s.canReceiveScholarship());
}
