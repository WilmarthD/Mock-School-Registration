#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "Parser.h"

using namespace std;

void Parse(string inputString, vector<string> &tokensVector);
void showPrompt();

int main()
{
    string userInput = "";
    vector<string> inputArgs;

    //Give user prompt on commands
    showPrompt();

    //Loop for each instruction in the line split by spaces
    while(getline(cin, userInput))
    {
        //Split input into seperate strings
        Parse(userInput, inputArgs);

        //If input statments
        if (inputArgs.empty())
        {
            showPrompt();
            continue;
        }

        if(inputArgs.at(0) == "quit")
        {
            //Exit program
            break;
        }
        else if(inputArgs.at(0) == "build")
        {
            cout << "build course ";
            for (int i = 1; i < (int)inputArgs.size(); i++)
            {
                cout << inputArgs.at(i) << " ";
            }
            cout << endl;
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
