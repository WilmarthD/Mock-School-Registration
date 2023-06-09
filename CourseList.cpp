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
    delete[] courses;
}

Course* CourseList::searchByCrn(string courseCrn){
    Course* tempCourse = new Course;
    for(int i = 0; i < courseCapacity; i++)
    {
        if(courses[i].GetCrn() == courseCrn)
        {
            tempCourse = &(courses[i]);
        }
    }
    return tempCourse;
}
void CourseList::printCourseRoster(string crn){
    searchByCrn(crn)->ShowStudents();
}
int CourseList::getStudentCount(string crn){
    Course* tempCourse = searchByCrn(crn);
    return tempCourse->GetRosterSize();
}
void CourseList::addNewStudent(Student* newStudent, string crn){
    Course* tempCourse = searchByCrn(crn);
    tempCourse->AddStudent(newStudent);
}
void CourseList::dropStudent(Student* oldStudent, string crn){
    Course* tempCourse = searchByCrn(crn);
    tempCourse->RemoveStudent(oldStudent);
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
void CourseList::removeCourse(string courseCrn){
    //bool crnExists = false;
    //Create dummy course
    Course tempCourse;

    for(int i = 0; i < courseCapacity; i++)
    {
        if(courses[i].GetCrn() == courseCrn)
        {
            //Course found
            if(i < courseCapacity-1)
            {
                for(int index = i; index < courseCapacity; index++)
                {
                    courses[index] = courses[index+1];
                }            
            }
            courses[courseCapacity-1] = tempCourse;
            courseCapacity--;
            //crnExists = true;
        }
    }
    //return crnExists;
}
bool CourseList::enrolledInCourse(string courseCrn, string studentBnum){

    Course* tempCourse = searchByCrn(courseCrn);
    return tempCourse[0].CheckStudentEnrolled(studentBnum);
}
