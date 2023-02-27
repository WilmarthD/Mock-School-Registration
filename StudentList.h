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
        
        bool searchStudent(string studentBnum);
        void addStudent(string studentBnum, string studentId, string studentFirst, string studentLast);
        void removeStudent(string studentBnum);
};

#endif