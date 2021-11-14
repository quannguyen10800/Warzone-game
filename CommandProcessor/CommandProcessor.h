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


class Command {
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
public:
    //CONSTRUCTOR & DESTRUCTOR
    FileLineReader();
    ~FileLineReader();
    void readLineFromFile();

};


class CommandProcessor : Command {
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
    string readCommand();
    FileLineReader* flr;

public:
    //CONSTRUCTOR & DESTRUCTOR
    FileCommandProcessorAdapter();
    ~FileCommandProcessorAdapter();

    Command* getCommand();


};


