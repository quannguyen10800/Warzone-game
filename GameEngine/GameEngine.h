//
// Created by Thong Tran on 2021-10-11.
//

#ifndef ASSIGNMENT1_GAMEENGINE_H
#define ASSIGNMENT1_GAMEENGINE_H
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Card/Card.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Player;
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
private:
};


#endif //ASSIGNMENT1_GAMEENGINE_H
