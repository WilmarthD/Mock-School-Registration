#include "StudentList.h"

StudentList::StudentList()
{
    studentCapacity = 0;
    students = new Student[studentCapacity];
}
StudentList::StudentList(int newCapacity){
    studentCapacity = newCapacity;
    students = new Student[studentCapacity];
}
StudentList::~StudentList(){
    delete[] students;
}
Student* StudentList::searchStudent(string studentBnum){
    Student* tempStudent = new Student;
    for(int i = 0; i < studentCapacity; i++)
    {
        if(students[i].GetBnumber() == studentBnum)
        {
            tempStudent = &(students[i]);
        }
    }
    return tempStudent;
}
void StudentList::enrollStudent(string studentBnum, string studentId, string studentFirst, string studentLast){
    //Create temp pointer
    Student* tempStudents = students;
    
    //Update capacity
    studentCapacity++;

    //Set new course list
    students = new Student[studentCapacity];
    
    //Add new course to front of new list
    students[0] = Student(studentFirst, studentLast, studentId, studentBnum);

    for(int i = 1; i < studentCapacity; i++)
    {
        students[i] = tempStudents[i-1];
    }
    
    //Delete new pointer
    //delete tempCourses; // Causes an error when deleting, could be double free?
}
void StudentList::removeStudentsInCourse(string oldCrn){
    //bool studentExists = false;
    //Student tempStudent;

    for(int i = 0; i < studentCapacity; i++)
    {
        students[i].DropCourse(oldCrn);
    }
    /*for(int i = 0; i < studentCapacity; i++)
    {
        if(students[i].GetBnumber() == studentBnum) //studentBnum was passed by string before change
        {
            if(i < studentCapacity-1)
            {
                for(int index = i; index < studentCapacity; index++)
                {
                    students[index] = students[index+1];
                }
            }
            students[studentCapacity-1] = tempStudent;
            studentCapacity--;
            studentExists = true;
        }
    }*/
    //return studentExists;
}
void StudentList::addNewCourse(Course* newCourse, string studentBnum){
    Student* tempStudent = searchStudent(studentBnum);
    tempStudent->AddCourse(newCourse);
}
void StudentList::dropCourse(Course* newCourse, string studentBnum){
    Student* tempStudent = searchStudent(studentBnum);
    tempStudent->DropCourse(newCourse->GetCrn());
}

void StudentList::printStudentSchedule(string studentBnum){
    searchStudent(studentBnum)->ShowCourses();
}     
