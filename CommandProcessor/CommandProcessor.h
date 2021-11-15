//
// Created by Tam Nhu Tran on 2021-11-12.
//

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../LoggingObserver/LoggingObserver.h"
using namespace std;

class GameEngine;
class Player;


class Command: public Iloggable{
private:
    string command;
    string effect;
public:
    //CONSTRUCTOR & DESTRUCTOR
    Command();
    ~Command();

    string getEffect();
    void saveEffect(string ef);
    string getCommand();
    void setCommand(string cm);
};


class FileLineReader {
private:
    string file;
    string line;
    fstream* fileInputStream;
public:
    //CONSTRUCTOR & DESTRUCTOR
    FileLineReader();
    ~FileLineReader();
    FileLineReader(string file);


    bool readLineFromFile();
    string getLine();
};


class CommandProcessor : public Command {
private:
    string command;
    string effect;
    vector<Command*> cmList;
public:
    //CONSTRUCTOR & DESTRUCTOR
    CommandProcessor();
    ~CommandProcessor();

    //READ COMMAND FROM THE CONSOLE
    static string readCommand();
    void saveCommand(string cm);
    Command* getLastCommand();

    //MUTATORS & ACCESSORS
    Command* getCommand();
    void setCommand(string cm);

};


class FileCommandProcessorAdapter : public CommandProcessor {
private:

    FileLineReader* flr;

public:
    //CONSTRUCTOR & DESTRUCTOR
    FileCommandProcessorAdapter();
    ~FileCommandProcessorAdapter();

    Command* getCommand();
    string readCommand();
};


