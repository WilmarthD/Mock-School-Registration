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
            if((int)inputArgs.size() != 5)
            {
                cout << "Failure: too many or too few arguments" << endl;
            }
            else if(regex_match(inputOuterWhitespaceChecked, buildCheck))
            {
                allCourses.addCourse(inputArgs.at(4), inputArgs.at(1), inputArgs.at(3), inputArgs.at(2));

                //Output that it was successful
                cout << "build course " << inputArgs.at(1) << " " << inputArgs.at(2) << " ";
                cout << inputArgs.at(3) << " " << inputArgs.at(4) << endl;
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
            if(regex_match(inputOuterWhitespaceChecked, cancelCheck))
            {
                cout << "cancel course " << inputArgs.at(1) << endl;
            }
            else if(!regex_match(inputArgs.at(1), regex("\\d{6}")))
            {
                //Malformed crn
                cout << "Failure: Malformed CRN " << inputArgs.at(1) << endl;
            }
        }
        else if(inputArgs.at(0) == "enroll")
        {
            if(regex_match(inputOuterWhitespaceChecked, enrollCheck))
            {
                cout << "enroll student " << inputArgs.at(1) << " (" << inputArgs.at(2) << ") " << inputArgs.at(4) << ", " << inputArgs.at(3) << endl;
            }
            else if(!regex_match(inputArgs.at(1), regex("B[0-9]{8}")))
            {
                //Malformed Bnumber
                cout << "Failure: Malformed Bnumber " << inputArgs.at(1) << endl;
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
            if(regex_match(inputOuterWhitespaceChecked, addCheck))
            {

                //Output that it was successful
                cout << "add student " << inputArgs.at(1) << " into course " << inputArgs.at(2) << endl;
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
            if(regex_match(inputOuterWhitespaceChecked, dropCheck))
            {
                cout << "remove student " << inputArgs.at(1) << " from course " << inputArgs.at(2) << endl;
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
            if(regex_match(inputOuterWhitespaceChecked, rosterCheck))
            {
                cout << "roster of the course " << inputArgs.at(1) << endl;
            }
            else if(!regex_match(inputArgs.at(1), regex("[0-9]{6}")))
            {
                //Malformed Bnumber
                cout << "Failure: Malformed CRN " << inputArgs.at(1) << endl;
            }
        }
        else if(inputArgs.at(0) == "schedule")
        {
            if(regex_match(inputOuterWhitespaceChecked, scheduleCheck))
            {
                cout << "schedule of student " << inputArgs.at(1) << endl;            
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
