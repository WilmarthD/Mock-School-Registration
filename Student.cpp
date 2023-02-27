#include "Student.h"
#include "Course.h"
Student::Student()
{
    firstName = "Na";
    lastName = "Body";
    userId = "noOneHere";
    Bnumber = "D00000001";

    courseCapacity = 0;
    courseCount = 0;
    courses = new Course[0];
}
Student::Student(string newFirstName, string newLastName, string newId, string newBnumber)
{
    firstName = newFirstName;
    lastName = newLastName;
    userId = newId;
    Bnumber = newBnumber;
    
    courseCapacity = 5;
    courseCount = 0;
    courses = new Course[courseCapacity];
}
Student::Student(const Student& rhs){
    firstName = rhs.firstName;
    lastName = rhs.lastName;
    userId = rhs.userId;
    Bnumber = rhs.Bnumber;
    courseCapacity = rhs.courseCapacity;
    courseCount = rhs.courseCount;

    courses = new Course[courseCapacity];
    for(int i = 0; i < rhs.courseCount; i++)
    {
        courses[i] = rhs.courses[i];
    }
    //delete courses;
    //courses = tempCourses;
}
Student::~Student()
{
    //TA said this won't be a data leak unless implemented wrong
    delete[] courses;
}
Student& Student::operator=(const Student& rhs){
    if(this != &rhs)
    {
        firstName = rhs.firstName;
        lastName = rhs.lastName;
        userId = rhs.userId;
        Bnumber = rhs.Bnumber;
        courseCapacity = rhs.courseCapacity;
        courseCount = rhs.courseCount;

        Course* tempCourses = new Course[courseCapacity];
        for(int i = 0; i < courseCount; i++)
        {
            courses[i] = rhs.courses[i];
        }
        delete[] courses;
        courses = tempCourses;
    }
    return *this;
}
string Student::GetName()
{
    string studentName = firstName + " " + lastName;
    return studentName;
}
string Student::GetBnumber(){
    return Bnumber;
}
void Student::ShowCourses()
{
    for(int i = 0; i < courseCount; i++)
    {
        cout << courses[i].GetName() << endl;
    }
}