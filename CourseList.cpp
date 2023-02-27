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
void CourseList::addCourse(string newName, string newCrn, string newCourseNum, string newDepartment){
    //Create temp pointer
    Course* tempCourses = courses;
    
    //Update capacity
    courseCapacity++;

    //Set new course list
    courses = new Course[courseCapacity];
    
    //Add new course to front of new list
    courses[0] = Course(newName, newCrn, newCourseNum, newDepartment);

    for(int i = 0; i < courseCapacity; i++)
    {
        courses[i+1] = tempCourses[i];
    }
    //Delete new pointer
    //delete tempCourses;
}
void CourseList::removeCourse(string courseCrn){
    bool crnExists = false;
    Course tempCourse;

    for(int i = 0; i < courseCapacity; i++)
    {
        if(courses[i].GetCrn() == courseCrn)
        {
            courses[i] = courses[courseCapacity-1];
            courses[courseCapacity-1] = tempCourse;
            crnExists = true;
        }
    }
    if(crnExists)
    {
        cout << courseCrn << " was successfully removed" << endl;
    }
    else
    {
        cout << courseCrn << " does not exist" << endl;
    }
}