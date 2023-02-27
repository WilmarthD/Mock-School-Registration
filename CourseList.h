#ifndef COURSELIST_H
#define COURSELIST_H

#include "Course.h"

class CourseList{
    private:
        int courseCapacity;
        Course *courses;
    public:
        CourseList();
        CourseList(int newCapacity);
        ~CourseList();
        
        Course searchByCrn(string courseCrn);
        void printCourseRoster(string crn);
        void addCourse(string newName, string newCrn, string newCourseNum, string newDepartment);
        bool removeCourse(string courseCrn);
};

#endif