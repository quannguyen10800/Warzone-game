//
// Created by Kai Tran on 2021-09-28
//

#include <iostream>
#include <string.h>
#include <algorithm>
#include "GameEngine.h"

using namespace std;

int main(){


    GameEngine ge;

    //LOOP UNTIL GAME ENGINE REACHES END
    do{
        cout<<"Current Game status = "<<ge.getState()<<endl;
        string command;
        cout<<"Please Enter a command = ";
        cin>>command;
        if (ge.transition(command.c_str()) == false){
            cout<<"Invalid command!!!"<<endl;
        }

    }while (ge.getEndStatus() == false);  //CHECKING END STATUS

}


// g++ GameEngine.cpp GameEngineDriver.cpp -o main
// ./main





//Quan Nguyen
void GameEngine::clearPlayerList() {

}

std::vector<Player*> GameEngine::players_;

Player *GameEngine::getOwnerOf(Territory *pTerritory) {
    for (const auto &player : players_ ) {
        std::vector<Territory*> territories = player->getTerritories();
        if(find(territories.begin(), territories.end(), territories) != territories.end()) {
            return player;
        }
    }
    return nullptr;
}

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


    auto isNeutralPlayer = [](const auto &player) {return player->isNeutral(); };
    int players_;
    auto iterator = find_if(players_.begin());

