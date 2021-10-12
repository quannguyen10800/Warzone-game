//
// Created by Thong Tran on 2021-10-11.
//
#include <string>
#include <algorithm>
#include "GameEngine.h"
void GameEngine::assignToNeutralPlayer(Territory* territory)
{
    Player* owner = getOwnerOf(territory);
    owner->removeTerritory(territory);

    auto isNeutralPlayer = [](const auto &player) { return player->isNeutral(); };
    auto iterator = find_if(players_.begin(), players_.end(), isNeutralPlayer);
    if (iterator == players_.end())
    {
        Player* neutralPlayer = new Player();
        neutralPlayer->addTerritory(territory);
        players_.push_back(neutralPlayer);
    }
    else
    {
        Player* neutralPlayer = *iterator;
        neutralPlayer->addTerritory(territory);
    }
}

// Find the player who owns the specified territory. Return nullptr if the territory is unowned.
Player* GameEngine::getOwnerOf(Territory* territory)
{
    for (const auto &player : players_)
    {
        std::vector<Territory*> territories = player->getTerritories();
        if (find(territories.begin(), territories.end(), territory) != territories.end())
        {
            return player;
        }
    }
    return nullptr;
}

// Default constructor
GameEngine::GameEngine(){
}




// Assignment operator
GameEngine &GameEngine::operator=(const GameEngine &anotherGameEngine) {
    for (auto player : anotherGameEngine.players_){
        Player* player_temp = new Player(*player);
        this->players_.push_back(player_temp);
    }
    return *this;
}

// Stream insertion
ostream &operator<<(ostream &stream, const GameEngine &gameEngine) {
    string toPrint = "Here are the players currently playing: \n";
    for (auto player : gameEngine.players_){
        toPrint.append(player->getPName()).append("\n");
    }
    stream << toPrint;
    return stream;
}

//
//const vector<Player *> &GameEngine::getPlayers() {
//    return players_;
//}

void GameEngine::addPlayersToList(Player* player) {
    players_.push_back(player);
}

void GameEngine::clearPlayerList() {
    for (auto player : players_){
        player = NULL;
        delete player;
    }
    players_.clear();
}