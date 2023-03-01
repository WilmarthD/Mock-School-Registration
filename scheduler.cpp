#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <regex>

#include "Parser.h"
#include "CourseList.h"
#include "StudentList.h"

using namespace std;

void Parse(string inputString, vector<string> &tokensVector);
void showPrompt();
void ErrorOutput(int error);

int main()
{
    string userInput = "";
    string inputWhitespaceChecked ="";
    string inputOuterWhitespaceChecked ="";
    vector<string> inputArgs;

    //Classes
    StudentList allStudents;
    CourseList allCourses;

    //Regex checking input(need to add second '\' before d compared to regex101)
    regex buildCheck("build \\d{6} [A-Z]{2,4} [100-700]{3} [a-zA-Z0-9]+( [a-zA-Z0-9_]+)*");
    regex cancelCheck("cancel \\d{6}");
    regex enrollCheck("enroll B[0-9]{8} [a-z][a-zA-Z0-9]* [a-zA-Z]* [a-zA-Z]*");
    regex addCheck("add B[0-9]{8} [0-9]{6}");
    regex dropCheck("drop B[0-9]{8} [0-9]{6}");
    regex rosterCheck("roster [0-9]{6}");
    regex scheduleCheck("schedule B[0-9]{8}");

    //Give user prompt on commands
    showPrompt();

    //Loop for each instruction in the line split by spaces
    while(getline(cin, userInput))
    {
        //Replace the arbitrary whitespace in user input
        inputWhitespaceChecked = regex_replace(userInput, regex("\\s+"), " "); //Replace all whitespace between elements with a single space
        inputOuterWhitespaceChecked = regex_replace(inputWhitespaceChecked, regex("^\\s+|\\s+$"), ""); //Clear preceding & proceeding whitespace

        //Split input into seperate strings
        Parse(inputOuterWhitespaceChecked, inputArgs);

        //If input statments
        if (inputArgs.empty())
        {
            showPrompt();
            cout << ": ";
            continue;
        }

        if(inputArgs.at(0) == "quit")
        {
            //Exit program
            break;
        }
        else if(inputArgs.at(0) == "build")
        {
            if((int)inputArgs.size() < 5)
            {
                cout << "Failure: too many or too few arguments" << endl;
            }
            else if(regex_match(inputOuterWhitespaceChecked, buildCheck))
            {
                //Check if course exists, if it doesn't the function should return a diffrent crn
                if(allCourses.searchByCrn(inputArgs.at(1))->GetCrn() == inputArgs.at(1))
                {
                    cout << "Failure: crn " << inputArgs.at(1) << " already exists" << endl;
                }
                else{
                    string courseName = "";
                    //Create for loop to set all words in name to a string
                    for(int index = 4; index < (int)inputArgs.size(); index++)
                    {
                        courseName += inputArgs.at(index) + " ";
                    }
                    allCourses.addCourse(courseName, inputArgs.at(1), inputArgs.at(3), inputArgs.at(2));

                    //Output that it was successful
                    cout << "Success: build course " << inputArgs.at(1) << " " << inputArgs.at(2) << " ";
                    cout << inputArgs.at(3) << " " << inputArgs.at(4);
                    for(int i = 5; i < (int)inputArgs.size(); i++)
                    {
                        cout << " " << inputArgs.at(i);
                    } 
                    cout << endl;
                }
            }
            else if(!regex_match(inputArgs.at(1), regex("\\d{6}")))
            {
                //Malformed crn
                cout << "Failure: Malformed CRN " << inputArgs.at(1) << endl;
            }
            else if(!regex_match(inputArgs.at(2), regex("[A-Z]{2,4}")))
            {
                //Malformed department
                cout << "Failure: Malformed department " << inputArgs.at(2) << endl;
            }
            else if(!regex_match(inputArgs.at(3), regex("[100-700]{3}")))
            {
                //Malformed course number
                cout << "Failure: Malformed course number " << inputArgs.at(3) << endl;
            }
            else if(!regex_match(inputArgs.at(4), regex("[a-zA-Z0-9]+( [a-zA-Z0-9_]+)*")))
            {
                //Malformed course name
                cout << "Failure: Malformed course name " << inputArgs.at(4) << endl;
            }
        }
        else if(inputArgs.at(0) == "cancel")
        {
            if((int)inputArgs.size() != 2)
            {
                cout << "Failure: too many or too few arguments" << endl;
            }
            if(regex_match(inputOuterWhitespaceChecked, cancelCheck))
            {
                //Check if course exists
                if(allCourses.searchByCrn(inputArgs.at(1))->GetCrn() != inputArgs.at(1))
                {
                    cout << "Failure: crn " << inputArgs.at(1) << " doesn't exist" << endl;
                }
                else{
                    //Remove course from student schedule
                    allStudents.removeStudentsInCourse(inputArgs.at(1));
                    allCourses.removeCourse(inputArgs.at(1));
    
                    cout << "Success: cancel course " << inputArgs.at(1) << endl;
                }
            }
            else if(!regex_match(inputArgs.at(1), regex("\\d{6}")))
            {
                //Malformed crn
                cout << "Failure: Malformed CRN " << inputArgs.at(1) << endl;
            }
        }
        else if(inputArgs.at(0) == "enroll")
        {
            if((int)inputArgs.size() != 5)
            {
                cout << "Failure: too many or too few arguments" << endl;
            }
            if(regex_match(inputOuterWhitespaceChecked, enrollCheck))
            {
                //Check if student exists, if not it will return the default b number
                if(allStudents.searchStudent(inputArgs.at(1))->GetBnumber() == inputArgs.at(1))
                {
                    cout << "Fail: student " << inputArgs.at(1) << " already exists" << endl;
                }
                else{
                    allStudents.enrollStudent(inputArgs.at(1), inputArgs.at(2), inputArgs.at(3), inputArgs.at(4));
                    cout << "Success: enroll student " << inputArgs.at(1) << " (" << inputArgs.at(2) << ") " << inputArgs.at(4) << ", " << inputArgs.at(3) << endl;
                }
            }
            else if(!regex_match(inputArgs.at(1), regex("B[0-9]{8}")))
            {
                //Malformed Bnumber
                cout << "Fail: Malformed Bnumber " << inputArgs.at(1) << endl;
                //continue;
            }
            else if(!regex_match(inputArgs.at(2), regex("[a-z][a-zA-Z0-9]*")))
            {
                //Malformed userId
                cout << "Failure: Malformed userId " << inputArgs.at(2) << endl;
                //continue;
            }
            else if(!regex_match(inputArgs.at(3), regex("[a-zA-Z]*")))
            {
                //Malformed first name
                cout << "Failure: Malformed first name " << inputArgs.at(3) << endl;
                //continue;
            }
            else if(!regex_match(inputArgs.at(4), regex("[a-zA-Z]*")))
            {
                //Malformed last name
                cout << "Failure: Malformed last name " << inputArgs.at(4) << endl;
            }
        }
        else if(inputArgs.at(0) == "add")
        {
            if((int)inputArgs.size() != 3)
            {
                cout << "Failure: too many or too few arguments" << endl;
            }
            if(regex_match(inputOuterWhitespaceChecked, addCheck))
            {
                //Check if student is already enrolled in course
                Course* tempAddCourse = allCourses.searchByCrn(inputArgs.at(2));
                Student* tempAddStudent = allStudents.searchStudent(inputArgs.at(1));

                if(tempAddStudent->GetBnumber() != inputArgs.at(1))
                {
                    cout << "Fail: student " << inputArgs.at(1) << " doesn't exist" << endl;
                }
                else if(tempAddCourse->GetCrn() != inputArgs.at(2))
                {
                    cout << "Fail: course " << inputArgs.at(2) << " doesn't exist" << endl;
                }
                else{
                    //Add student to course roster
                    allCourses.addNewStudent(tempAddStudent, inputArgs.at(2));
                    //Add course to student schedule
                    allStudents.addNewCourse(tempAddCourse, inputArgs.at(1));

                    //Output that it was successful
                    cout << "Success: add student " << inputArgs.at(1) << " into course " << inputArgs.at(2) << endl;
                }
                
            }
            else if(!regex_match(inputArgs.at(1), regex("B[0-9]{8}")))
            {
                //Malformed Bnumber
                cout << "Failure: Malformed CRN " << inputArgs.at(1) << endl;
            }
            else if(!regex_match(inputArgs.at(2), regex("[0-9]{6}")))
            {
                //Malformed crn
                cout << "Failure: Malformed CRN " << inputArgs.at(2) << endl;
            }
        }
        else if(inputArgs.at(0) == "drop")
        {
            if((int)inputArgs.size() != 3)
            {
                cout << "Failure: too many or too few arguments" << endl;
            }

            if(regex_match(inputOuterWhitespaceChecked, dropCheck))
            {
                Student* tempOldStudent = allStudents.searchStudent(inputArgs.at(1));
                Course* tempOldCourse = allCourses.searchByCrn(inputArgs.at(2));

                if(tempOldStudent->GetBnumber() != inputArgs.at(1))
                {
                    cout << "Fail: student " << inputArgs.at(1) << " doesn't exist" << endl;
                }
                else if(tempOldCourse->GetCrn() != inputArgs.at(2))
                {
                    cout << "Fail: course " << inputArgs.at(2) << " doesn't exist" << endl;
                }
                else if(!allCourses.enrolledInCourse(inputArgs.at(2), inputArgs.at(1)))
                {
                    cout << "Fail: the student " << inputArgs.at(1) << " is not in course " << inputArgs.at(2) << endl;
                }
                else{
                    //Remove student from course roster
                    allCourses.dropStudent(tempOldStudent, inputArgs.at(2));
                    //Remove course from student schedule
                    allStudents.dropCourse(tempOldCourse, inputArgs.at(1));

                    cout << "Success: remove student " << inputArgs.at(1) << " from course " << inputArgs.at(2) << endl;
                }

            }
            else if(!regex_match(inputArgs.at(1), regex("B[0-9]{8}")))
            {
                //Malformed Bnumber
                cout << "Failure: Malformed Bnumber " << inputArgs.at(1) << endl;
            }
            else if(!regex_match(inputArgs.at(2), regex("[0-9]{6}")))
            {
                //Malformed crn
                cout << "Failure: Malformed CRN " << inputArgs.at(2) << endl;
                //continue;
            }
        }
        else if(inputArgs.at(0) == "roster")
        {
            if((int)inputArgs.size() != 2)
            {
                cout << "Failure: too many or too few arguments" << endl;
            }
            if(regex_match(inputOuterWhitespaceChecked, rosterCheck))
            {
                //Check if course exists, if it doesn't the function should return a diffrent crn
                if(allCourses.searchByCrn(inputArgs.at(1))->GetCrn() != inputArgs.at(1))
                {
                    cout << "Failure: crn " << inputArgs.at(1) << " doesn't exists" << endl;
                }
                else{
                    cout << "Success: roster of course " << inputArgs.at(1) << endl;
                    allCourses.printCourseRoster(inputArgs.at(1));
                }
            }
            else if(!regex_match(inputArgs.at(1), regex("[0-9]{6}")))
            {
                //Malformed Bnumber
                cout << "Failure: Malformed CRN " << inputArgs.at(1) << endl;
            }
        }
        else if(inputArgs.at(0) == "schedule")
        {
            if((int)inputArgs.size() != 2)
            {
                cout << "Failure: too many or too few arguments" << endl;
            }
            if(regex_match(inputOuterWhitespaceChecked, scheduleCheck))
            {
                //Check if student exists, if not it will return the default b number
                if(allStudents.searchStudent(inputArgs.at(1))->GetBnumber() != inputArgs.at(1))
                {
                    cout << "Fail: student " << inputArgs.at(1) << " doesn't exists" << endl;
                }
                else{
                    cout << "Success: schedule of student " << inputArgs.at(1) << endl;    
                    allStudents.printStudentSchedule(inputArgs.at(1)); 
                } 
            }
            else if(!regex_match(inputArgs.at(1), regex("B[0-9]{8}")))
            {
                //Malformed Bnumber
                cout << "Failure: Malformed Bnumber " << inputArgs.at(1) << endl;
                //continue;
            }
        }
        else if(inputArgs.at(0) == " ")
        {
            cout << endl << ": ";
            
        }
        else
        {
            cout << "Failure: Command not recognized" << endl;
        }
        
        //Clear all tokens out of vector
        inputArgs.clear();

        //Give user prompt on commands
        showPrompt();
    }

    
    return 0;
}

void Parse(string inputString, vector<string> &tokensVector)
{
    stringstream newString(inputString);
    //vector<string> inputArgs;
    string token;

    while(getline(newString, token, ' '))
    {
        tokensVector.push_back(token);
    }
}

void showPrompt() {
   cout << "Enter [\"build <crn> <department> <number> <name>\"" << std::endl <<
            "       \"cancel <crn>\"" << std::endl <<
            "       \"enroll <bnumber> <userid> <first> <last>\"" << std::endl <<
            "       \"add <bnumber> <crn>\"" << std::endl <<
            "       \"drop <bnumber> <crn>\"" << std::endl <<
            "       \"roster <crn>\"" << std::endl <<
            "       \"schedule <bnumber>\"" << std::endl <<
            "       \"quit\"]" << endl <<
            ": ";
}


//Function to output diffrent error messages depending on int
void ErrorOutput(int error)
{
    cout << "Failure: ";

    switch(error)
    {
        case 0:
            cout << "Unrecognized commands" << endl;
            break;
        case 1:
            cout << "Too many or too few arguments" << endl;
            break;
        case 2:
            cout << "Malformed CRN" << endl;
            break;
        case 3:
            cout << "Incorrect types (such as letters inserted where numbers were expected)" << endl;
            break;
        default:
            cout << "You fucked up" << endl;
    }
}
