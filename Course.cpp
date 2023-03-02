#include "Course.h"
#include "Student.h"

Course::Course()
{
    courseName = "No Name Given";
    crn = "1234567";
    courseNum = "1234";
    department = "No Department Given";
    capacity = 0;
    size = 0;
    students = new Student[capacity];
    //studentBnumbers = new string[capacity];
}
Course::Course(string newName, string newCrn, string newCourseNum, string newDepartment)
{
    courseName = newName;
    crn = newCrn;
    courseNum = newCourseNum;
    department = newDepartment;
    capacity = 0;
    size = 0;
    students = new Student[capacity];
    //studentBnumbers = new string[capacity];
}
Course::Course(const Course& rhs){
    courseName = rhs.courseName;
    crn = rhs.crn;
    courseNum = rhs.courseNum;
    department = rhs.department;
    capacity = rhs.capacity;
    size = rhs.size;

    // studentBnumbers = new string[capacity];
    // for (int i = 0; i < rhs.size; i++)
    // {
    //     studentBnumbers[i] = rhs.studentBnumbers[i];
    // }
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
    //delete[] studentBnumbers;
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

        /* string* tempBnumber = new string[capacity];
         for(int i = 0; i < size; i++)
         {
             tempBnumber[i] = rhs.studentBnumbers[i];
         }
         delete[] studentBnumbers;
         studentBnumbers = tempBnumber;*/


        //Student* tempStudents = new Student[capacity];
        delete[] students;
        students = new Student[capacity];
        for(int i = 0; i < size; i++)
        {
            students[i] = rhs.students[i];
        }
        //delete[] students;
        //students = tempStudents;
    }
    return *this;
}
void Course::AddStudent(Student* newStudent){
    if(size < capacity)
    {
        students[size] = *newStudent;
        //studentBnumbers[size] = *newStudent;
        size++;
    }
    else{
        if(capacity == 0)
        {
            capacity++;
        }
        else{
            capacity *= 2;
        }

        Student* tempStudents = new Student[capacity];
        for(int i = 0; i < size; i++)
        {
            tempStudents[i] = students[i];
        }
        delete [] students;
        students = tempStudents;

        //Assign new students
        students[size] = *newStudent;
        size++;

    }
}
void Course::RemoveStudent(Student* newStudent){
    Student tempStudent;
    for(int i = 0; i < size; i++)
    {
        if(students[i].GetBnumber() == newStudent->GetBnumber())
        {
            if(i != size-1)
            {
                for(int index = i; index < size-1; index++)
                {
                    students[index] = students[index+1];
                }
            }
            size--;
            students[size] = tempStudent;
        }
    }
}
string Course::GetCourseFullName(){
    string tempString = "";
    tempString = crn + " " + department + " " + courseNum + " " + courseName;
    return tempString;
}
string Course::GetName(){
    return courseName;
}
string Course::GetCrn(){
    return crn;
}
void Course::ShowStudents(){
    for(int i = 0; i < size; i++)
    {
        cout << students[i].GetBnumber() << " " << students[i].GetName() << endl;
    }
}
int Course::GetRosterSize(){
    return size;
}
bool Course::CheckStudentEnrolled(string studentBnumber){
    bool studentExists = false;
    for(int i = 0; i < size; i++)
    {
        if(students[i].GetBnumber() == studentBnumber)
        {
            studentExists = true;
        }
    }
    return studentExists;
}