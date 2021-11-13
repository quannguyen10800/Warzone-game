//
// Created by Tam Nhu Tran on 2021-11-12.
//

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class GameEngine;
class Player;


class CommandProcessor {
private:
    //READ COMMAND FROM THE CONSOLE
    virtual string readCommand();

    string command;
    string effect;
    vector<Command*> cmList;
public:
    //CONSTRUCTOR & DESTRUCTOR
    CommandProcessor();
    ~CommandProcessor();

    //MUTATORS & ACCESSORS
    string getCommand();
    void setCommand(string command);
    string getEffect();
    void setEffect(string effect);
};


class Command {
private:
    string command;
    string effect;
public:
    //CONSTRUCTOR & DESTRUCTOR
    Command();
    ~Command();

    void SaveEffect();
};


class FileLineReader {
private:
    string file;
    string line;
public:
    //CONSTRUCTOR & DESTRUCTOR
    FileLineReader();
    ~FileLineReader();
    void readLineFromFile();

};


class FileCommandProcessorAdapter : public CommandProcessor {
private:
    string readCommand();
    FileLineReader* flr;

public:
    //CONSTRUCTOR & DESTRUCTOR
    FileCommandProcessorAdapter();
    ~FileCommandProcessorAdapter();

    Command* getCommand();


};


