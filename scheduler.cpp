#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "Parser.h"

using namespace std;

void Parse(string inputString, vector<string> &tokensVector);

int main(int argc, char *argv[])
{
    string userInput = "";
    vector<string> inputArgs;

    //In loop accept commands from user, only stopping with "quit"
    //cin.getline(userInput);

    //Loop for each instruction in the line split by spaces
    while(getline(cin, userInput))
    {
        Parse(userInput, inputArgs);
        if(inputArgs)
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