//
// Created by Kai Tran on 2021-09-28
//

#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include <iostream>
#include <string.h>
#include "../Player/Player.h"

using namespace std;

class GameEngine{
    char* state;
    bool isGameEnd; //TURNS TRUE WHEN GAME ENDS

public:

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


    static void addPlayersToList(Player *pPlayer);

    static void clearPlayerList();

    static Player *getOwnerOf(Territory *pTerritory);

    static std::vector<PLayer *> players_;

    static void assignToNeutralPlayer(Territory *territory);
};

#endif // GAMEENGINE_H_INCLUDED
