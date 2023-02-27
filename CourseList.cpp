#include "CourseList.h"

CourseList::CourseList(){
    courseCapacity = 0;
    courses = new Course[courseCapacity];
}
CourseList::CourseList(int newCapacity){
    courseCapacity = newCapacity;
    courses = new Course[newCapacity];
}
CourseList::~CourseList(){
    delete courses;
}

Course CourseList::searchByCrn(string courseCrn){
    Course tempCourse;
    for(int i = 0; i < courseCapacity; i++)
    {
        if(courses[i].GetCrn() == courseCrn)
        {
            return courses[i];
        }
    }
    return tempCourse;
}
void CourseList::printCourseRoster(string crn){
    searchByCrn(crn).ShowStudents();
}

void CourseList::addCourse(string newName, string newCrn, string newCourseNum, string newDepartment){
    //Create temp pointer
    Course* tempCourses = courses;
    
    //Update capacity
    courseCapacity++;

    //Set new course list
    courses = new Course[courseCapacity];
    
    //Add new course to front of new list
    courses[0] = Course(newName, newCrn, newCourseNum, newDepartment);

    for(int i = 1; i < courseCapacity; i++)
    {
        courses[i] = tempCourses[i-1]; //This is now causing segfault
    }
    
    //Delete new pointer
    //delete tempCourses; // Causes an error when deleting, could be double free?
}
bool CourseList::removeCourse(string courseCrn){
    bool crnExists = false;
    //Create dummy course
    Course tempCourse;

    for(int i = 0; i < courseCapacity; i++)
    {
        if(courses[i].GetCrn() == courseCrn)
        {
            if(i < courseCapacity-1)
            {
                for(int index = i; index < courseCapacity; index++)
                {
                    courses[index] = courses[index+1];
                }            
            }
            courses[courseCapacity-1] = tempCourse;
            courseCapacity--;
            crnExists = true;
        }
    }
    return crnExists;
}