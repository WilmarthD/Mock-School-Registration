#include "Student.h"
#include "Course.h"
Student::Student()
{
    firstName = "Na";
    lastName = "Body";
    userId = "noOneHere";
    Bnumber = "D00000001";
    courseCount = 0;
    courses = new Course[0];
}
Student::Student(string newFirstName, string newLastName, string newId, string newBnumber)
{
    firstName = newFirstName;
    lastName = newLastName;
    userId = newId;
    Bnumber = newBnumber;
    
    courseCount = 0;
    courses = new Course[0];
}
Student::~Student()
{
    //TA said this won't be a data leak unless implemented wrong
    delete[] courses;
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