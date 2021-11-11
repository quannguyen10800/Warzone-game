//
// Created by mehrsa yazdani on 2021-11-09.
//



#ifndef UNTITLED1_GAMEENGINE_H
#define UNTITLED1_GAMEENGINE_H

#define ASSIGNMENT1_GAMEENGINE_H
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
public:
    GameEngine();
    GameEngine& operator = (GameEngine const &anotherGameEngine);
    friend ostream& operator << (ostream &stream, const GameEngine &gameEngine);
    static Player* getOwnerOf(Territory* territory);
    static void assignToNeutralPlayer(Territory* territory);
    static void addPlayersToList(Player* player);
    static void clearPlayerList();
    static std::vector<Player*> players_;
    void startupPhase();
    void gameStart();
    int getTheTurn(int numb);
private:
};


#endif //UNTITLED1_GAMEENGINE_H

