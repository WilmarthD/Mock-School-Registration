#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "Parser.h"

using namespace std;

void Parse(string inputString, vector<string> &tokensVector);
void showPrompt();

int main(int argc, char *argv[])
{
    string userInput = "";
    vector<string> inputArgs;

    //In loop accept commands from user, only stopping with "quit"
    //cin.getline(userInput);
    showPrompt();

    //Loop for each instruction in the line split by spaces
    while(getline(cin, userInput))
    {
        //Parse iput line into tokens in a vector
        Parse(userInput, inputArgs);

        //If input statments
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
            cout << "cancel course ";
            for (int i = 1; i < (int)inputArgs.size(); i++)
            {
                cout << inputArgs.at(i) << " ";
            }
            cout << endl;
        }
        else if(inputArgs.at(0) == "enroll")//Change output top special tokens
        {
            cout << "enroll student " << inputArgs.at(1)
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
        else
        {
            cout << " Command not recognized, please try again." << endl;
        }
        
        //Clear all tokens out of vector
        inputArgs.clear();
    }

    return 0;
}

void Parse(string inputString, vector<string> &tokensVector)
{
    stringstream newString(inputString);
    //vector<string> inputArgs;
    string token = "";

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