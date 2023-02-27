#include "Course.h"
#include "Student.h"

Course::Course()
{
    courseName = "No Name Given";
    crn = "1234567";
    courseNum = "1234";
    department = "No Department Given";
    capacity = 10;
    size = 0;
    students = new Student[capacity];
}
Course::Course(string newName, string newCrn, string newCourseNum, string newDepartment)
{
    courseName = newName;
    crn = newCrn;
    courseNum = newCourseNum;
    department = newDepartment;
    capacity = 10;
    size = 0;
    students = new Student[capacity];
}
Course::Course(const Course& rhs){
    courseName = rhs.courseName;
    crn = rhs.crn;
    courseNum = rhs.courseNum;
    department = rhs.department;
    capacity = rhs.capacity;
    size = rhs.size;

    students = new Student[capacity];

    for(int i = 0; i < rhs.size; i++)
    {
        students[i] = rhs.students[i];
    }
    //delete students;
    //students = tempStudents;
}

Course::~Course(){
    //TA said this won't be a data leak unless implemented wrong
    delete[] students;
}
Course& Course::operator=(const Course& rhs){
    if(this != &rhs)
    {
        courseName = rhs.courseName;
        crn = rhs.crn;
        courseNum = rhs.courseNum;
        department = rhs.department;
        capacity = rhs.capacity;
        size = rhs.size;
        Student* tempStudents = new Student[capacity];

        for(int i = 0; i < size; i++)
        {
            tempStudents[i] = rhs.students[i];
        }
        delete[] students;
        students = tempStudents;
    }
    return *this;
}

string Course::GetName()
{
    return courseName;
}
string Course::GetCrn()
{
    return crn;
}
void Course::ShowStudents()
{
    for(int i = 0; i < capacity; i++)
    {
        cout << students[i].GetName() << endl;
    }
}