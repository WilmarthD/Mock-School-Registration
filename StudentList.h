#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "Student.h"

class StudentList{
    private:
        int studentCapacity;
        Student *students;
    public:
        StudentList();
        StudentList(int newCapacity);
        ~StudentList();
        
        Student* searchStudent(string studentBnum);
        void enrollStudent(string studentBnum, string studentId, string studentFirst, string studentLast);
        void removeStudentsInCourse(string oldCrn);
        void addNewCourse(Course* newCourse, string studentBnum);
        void dropCourse(Course* newCourse, string studentBnum);
        void printStudentSchedule(string studentBnum);

};

#endif