//
// Created by Tam Nhu Tran on 2021-11-12.
//

#include "CommandProcessor.h"
#include <string>
#include <sstream>


//************************************
// Command - start
Command::Command() {
    command = "none";
    effect = "none";
}
Command::~Command() = default;

string Command::getEffect() {
    return effect;
}
void Command::saveEffect(string ef) {
    this->effect = ef;
    Notify(this);
}
string Command::getCommand() {
    return command;
}
void Command::setCommand(string cm) {
    this->command = cm;
}
// Command -end
//************************************


//************************************
//FileLineReader - start
FileLineReader::FileLineReader() {
    fileInputStream = nullptr;
}
FileLineReader::~FileLineReader() {
    fileInputStream->close();
    delete fileInputStream;
    fileInputStream = nullptr;
}
FileLineReader::FileLineReader(string file) {
    //check whethere file is open
    this->file = file;
    fileInputStream = new fstream();
    if (!fileInputStream->is_open()){
        cout << "File not found." << endl;
        exit(0);
    }
}

bool FileLineReader::readLineFromFile() {
    string lineUnderRead;
    getline(*fileInputStream, lineUnderRead);
    if (lineUnderRead.compare("") != 0) {
        return true;
    }
    else {
        return false;
    }
}
string FileLineReader::getLine() {
    return line;
}
//FileLineReader -end
//************************************


//************************************
//CommandProcessor - start

CommandProcessor::CommandProcessor() {}
CommandProcessor::~CommandProcessor() {
    for (Command* cm : cmList) {
        delete cm;
        cm = nullptr;
    }
    cmList.erase(cmList.begin(), cmList.end());
}

string CommandProcessor::readCommand() {
    string cmString;
    cout << "Enter command: \n";
    //take the string until hit enter
    getline(cin, cmString);
    return cmString;
}
void CommandProcessor::saveCommand(string cm){
    Command* cmObject = new Command();
    cmObject->setCommand(cm);
    cmList.push_back(cmObject);
    Notify(this);
}
Command* CommandProcessor::getLastCommand() {
    return cmList.back();
}

Command* CommandProcessor::getCommand() {
    string cm = this->readCommand();
    saveCommand(cm);
    return getLastCommand();
}

void CommandProcessor::setCommand(string cm) {
    this->command = cm;
}
//CommandProcessor -end
//************************************


//************************************
//FileCommandProcessorAdapter - start
string FileCommandProcessorAdapter::readCommand() {
    if (flr->readLineFromFile()) {

    }
}

//FileCommandProcessorAdapter -end
*///************************************

//----------------------------
// -------
//Implementation of Logging mechanism
//-----------------------------------

string Command::stringToLog(){
    return "Command: " + command;
}

string CommandProcessor::stringToLog(){
    return "Command effect: " + effect;
}