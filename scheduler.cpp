#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <regex>
#include "Parser.h"

using namespace std;

void Parse(string inputString, vector<string> &tokensVector);
void showPrompt();
int DeterminErrors(vector<string>& input);
void ErrorOutput(int errorNumber);

int main()
{
    string userInput = "";
    string inputWhitespaceChecked ="";
    vector<string> inputArgs;

    //Regex checking input(need to add second '\' before d compared to regex101)
    regex buildCheck("/build \\d{6} [A-Z]{2,4} [100-700]{3} [a-zA-Z0-9]+( [a-zA-Z0-9_]+)*/g");
    regex cancelCheck("/cancel \\d{6}/g");
    regex enrollCheck("/enroll B[0-9]{8} [a-z][a-zA-Z0-9]* [a-zA-Z]* [a-zA-Z]*/g");
    regex addCheck("/add B[0-9]{8} [0-9]{6}/g");
    regex dropCheck("/drop B[0-9]{8} [0-9]{6}/g");
    regex rosterCheck("/roster [0-9]{6}/g");
    regex scheduleCheck("/schedule B[0-9]{8}/g");

    regex whiteSpaceChecker("(\t)( )");

    //Give user prompt on commands
    showPrompt();

    //Loop for each instruction in the line split by spaces
    while(getline(cin, userInput))
    {
        //Replace the arbitrary whitespace in user input
        inputWhitespaceChecked = regex_replace(userInput, whiteSpaceChecker, " ");
        
        //Split input into seperate strings
        Parse(userInput, inputArgs);

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
                ErrorOutput(2);
                continue;
            }

            
            /*else if(inputArgs.at(1).size() != 6)
            {
                ErrorOutput(3);
                continue;
            }
            for(int i = 0; i < (int)inputArgs.at(1).size();i++)
            {
                if(!isdigit(inputArgs.at(1).at(i)))
                {
                    ErrorOutput(3);
                    continue;
                }
            }*/
            
            cout << "build course " << inputArgs.at(1) << " " << inputArgs.at(2) << " ";
            cout << inputArgs.at(3) << " " << inputArgs.at(4) << endl;
        }
        else if(inputArgs.at(0) == "cancel")
        {
            cout << "cancel course " << inputArgs.at(1) << endl;
        }
        else if(inputArgs.at(0) == "enroll")
        {
            cout << "enroll student " << inputArgs.at(1) << " (" << inputArgs.at(2) << ") " << inputArgs.at(4) << ", " << inputArgs.at(3) << endl;
        }
        else if(inputArgs.at(0) == "add")
        {
            cout << "add student " << inputArgs.at(1) << " into course " << inputArgs.at(2) << endl;
        }
        else if(inputArgs.at(0) == "drop")
        {
            cout << "remove student " << inputArgs.at(1) << " from course " << inputArgs.at(2) << endl;
        }
        else if(inputArgs.at(0) == "roster")
        {

            cout << "roster of the course " << inputArgs.at(1) << endl;
        }
        else if(inputArgs.at(0) == "schedule")
        {
            cout << "schedule of student " << inputArgs.at(1) << endl;
        }
        else if(inputArgs.at(0) == " ")
        {
            cout << endl << ": ";
        }
        else
        {
            cout << "Command not recognized, please try again." << endl;
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
//Function to determine if there is an error from user, outputting the
// respective error number*****************************************************************might not use
int DeterminErrors(vector<string>& input)
{
    int errorNum = 0;



    return errorNum;
}
//Function to output diffrent error messages depending on int
//Key: 1 = unrecognized command
//     2 = too many/few arguments
//     3 = Malformed B number/CRN
//     4 = Incorrect types
//     5 = empty lines
//     6 = Irregular whitespace input
//     etc... (to be announced)
void ErrorOutput(int errorNumber)
{
    if(errorNumber != 0)
    {
        cout << "Error: ";

        switch(errorNumber)
        {
            case 1:
                cout << "Unrecognized commands" << endl;
                break;
            case 2:
                cout << "Too many or too few arguments" << endl;
                break;
            case 3:
                cout << "Malformed B number or CRN" << endl;
                break;
            case 4:
                cout << "Incorrect types (such as letters inserted where numbers were expected)" << endl;
                break;
            case 5:
                cout << "Empty lines" << endl;
                break;
            case 6:
                cout << "Irregular whitespace in input" << endl;
                break;
        }
    }
    
    
}
