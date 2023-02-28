#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;
//Forward declaration of course class
class Course;
class Student {
    private:
        string firstName;
        string lastName;
        string userId;
        string Bnumber;
        int courseCapacity;
        int courseCount;
        Course *courses;
    
    public:
        Student();
        Student(string newFirstName, string newLastName, string newId, string newBnumber);
        Student(const Student& rhs);
        ~Student();

        Student& operator=(const Student& rhs);
        void ShowCourses();
        string GetName();
        string GetBnumber();
        void AddCourse(Course* newCourse);
};

#endif