//
// Created by mehrsa yazdani on 2021-11-09.
//
#pragma once
class Player;
class Territory;


#include <vector>
#include <string>
#include <iostream>
using namespace std;


class CommandProcessor{
private:
    string command;
public:
    string getCommand();
};

class GameEngine {
    char* state;
    bool isGameEnd; //TURNS TRUE WHEN GAME ENDS

public:


     std::vector<Player*> players_;



    //DEFAULT CONSTRUCTOR
    GameEngine();

    //PARAMETERIZED CONSTRUCTOR
    //PARAMETERS: CHAR*
    GameEngine(char* initialState);

    //COPY CONSTRUCTOR
    GameEngine(const GameEngine &ge);

    //ASSIGNMENT OPERATOR OVERLOAD FUNCTION
    const GameEngine& operator=(const GameEngine& ge);

    //RETURN CURRENT STATE OF GAME
    char *getState();

    //RETURN END STATUS OF THE GAME
    bool getEndStatus();

    //RETURNS TRUE IF PASSED CHAR* STATE
    //IS VALID STATE OF OUR GAME ENGINE
    bool isValidState(char* state);

    //CHANGE THE CURRENT STATE OF GAME ENGINE
    //AND RETURN TRUE IF CORRECT COMMAND ENTERED
    //ELSE STATE WILL REMAIN SAME AND FALSE RETURNED
    bool transition(const char* command);

    //INSERTION OPERATOR OVERLOAD FUNCTION
    friend istream & operator >> (istream &in,  GameEngine &ge);

    //DESTRUCTOR
    ~GameEngine();

    void   addPlayersToList(Player* p1);

    void startupPhase();
    int getTheTurn(int numb);
private:



};

