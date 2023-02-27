#include "StudentList.h"

StudentList::StudentList()
{
    studentCapacity = 1;
    students = new Student[studentCapacity];
}
StudentList::StudentList(int newCapacity){
    studentCapacity = newCapacity;
    students = new Student[studentCapacity];
}
StudentList::~StudentList(){
    delete students;
}
bool StudentList::searchStudent(string studentBnum){
    for(int i = 0; i < studentCapacity; i++)
    {
        if(students[i].GetBnumber() == studentBnum)
        {
            return true;
        }
    }
    return false;
}
void StudentList::addStudent(string studentBnum, string studentId, string studentFirst, string studentLast){

}
void StudentList::removeStudent(string studentBnum){

}