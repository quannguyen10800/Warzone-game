//
// Created by mehrsa yazdani on 2021-11-07.
//


#ifndef ASSIGNMENT1_GAMEENGINE_H
#define ASSIGNMENT1_GAMEENGINE_H
#include <string>
#include <algorithm>
#include "GameEngine.h"
#include "Map.h"
#include <cstdlib>
#include <ctime>
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

void GameEngine::startupPhase() {
    Map* map =new Map();
    string nameofthemap;
    cout << "please enter the name of the map"<<endl;
    cin >> nameofthemap;
    map=MapLoader::parse(nameofthemap,map);

    if(!Map::validate(map)){
        cout << "the map is validate to be incorrect , please start over" <<endl;
        exit(0);


    }else{
        int numOfPlayers;

        cout << "please enter the number of players " <<endl;
        cin >> numOfPlayers;
        while(numOfPlayers > 6  || numOfPlayers <2){
            cout <<"the number entered is incorrect please try again" <<endl;
            cin >> numOfPlayers;
        }

        for (int i = 0; i < numOfPlayers ; i++) {
            string name;
            cout << "please enter the name of the player "<<i<<endl;
            cin  >> name;
            Player* p1=new Player(name);
            addPlayersToList(p1);
        }
        int numberofterritoris=map->territories.size();
        //int numberofterritoriesforeachplayer;
        int helper=numberofterritoris/numOfPlayers;
        int helper3=helper*4;
        int helper2=numberofterritoris-(helper3);

        for (int i = 0; i < players_.size(); i++) {
            for (int j = 0; j < helper; j++) {
                static int indexofterritories=0;
                players_.at(i)->addTerritory(map->territories.at(indexofterritories));
                indexofterritories++;

            }

        }

        for (int i = 0; i < helper2 ; i++) {
            for (int j = 0; j < map->territories.size(); j++) {

                players_.at(i)->addTerritory(map->territories.at(helper3));
                helper3++;


            }

        }

        bool order;
        string StringStateOfTheGame="starting";
        int turn;
        turn =getTheTurn(numOfPlayers);
        cout << "it is the turn for player number " <<turn <<endl;


        for (int i = 0; i <numOfPlayers ; i++) {
            players_.at(i)->setTheNumberOFArmies(50);

        }

        for (int i = 0; i <numOfPlayers ; i++) {
            for (int j = 0; j < 2; j++) {
                players_.at(i).draw();

            }

        }
     StringStateOfTheGame="play";



    }




}

 int  GameEngine :: getTheTurn(int numb){
     srand(time(0));
    int turn =(rand() % numb + 1);
     return turn;



}





string CommandProcessor::getCommand() {
    return command;
}


#endif //ASSIGNMENT1_GAMEENGINE_H