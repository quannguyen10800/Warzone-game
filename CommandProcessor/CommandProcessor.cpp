//
// Created by Tam Nhu Tran on 2021-11-12.
//

#include "CommandProcessor.h"
#include <string>
#include <sstream>

/*
CommandProcessor - start
*/
string CommandProcessor::readCommand() {
    string command;
    cout << "Enter command: \n";
    //take the string until hit enter
    getline(cin, command);
    return command;
}
CommandProcessor::CommandProcessor() {}
CommandProcessor::~CommandProcessor() {
    for (Command* command1 : cmList) {
        delete command1;
        command1 = NULL;
    }
    cmList.erase(cmList.begin(), cmList.end());
}

/*
CommandProcessor -end
*/


//************************************
/*
Command - start
*/

/*
Command -end
*/


//************************************
/*
FileLineReader - start
*/

/*
FileLineReader -end
*/


//************************************
/*
FileLineReader - start
*/

/*
FileLineReader -end
*/