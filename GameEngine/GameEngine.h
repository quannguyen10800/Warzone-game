//
// Created by Kai Tran on 2021-09-28
//

#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include <iostream>
#include <string.h>

using namespace std;

class GameEngine{
    char* state;
    int gameEnd;

public:

    GameEngine();
    GameEngine(char* initialState);
    GameEngine(const GameEngine &ge);
    const GameEngine& operator=(const GameEngine& ge);
    char *getState();
    int getEndStatus();
    bool isValidState(char *state);
    bool transition(const char* command);
    friend istream & operator >> (istream &in,  GameEngine &ge);
    ~GameEngine();


};

#endif // GAMEENGINE_H_INCLUDED
