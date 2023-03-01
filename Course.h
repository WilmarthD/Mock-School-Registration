#ifndef COURSE_H
#define COURSE_H

#include "Student.h"
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

//Forward declaration of student class
class Student;
class Course {
    private:
        //Member variables
        string courseName;
        string crn;
        string courseNum;
        string department;
        int capacity;
        int size;
        Student *students;
        //string *studentBnumbers;
    
    public:
        //Constructors and destructors
        Course();
        Course(string newName, string newCrn, string newCourseNum, string newDepartment);
        Course(const Course& rhs);
        ~Course();

        Course& operator=(const Course& rhs);
        void AddStudent(Student* newStudent);
        void RemoveStudent(Student* newStudent);
        string GetName();
        string GetCrn();
        void ShowStudents();
        bool CheckStudentEnrolled(string studentBnumber);
};

#endif