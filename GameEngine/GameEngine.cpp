
#ifndef ASSIGNMENT1_GAMEENGINE_H
#define ASSIGNMENT1_GAMEENGINE_H

#include <string>
#include <algorithm>
#include "GameEngine.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include <cstdlib>
#include <ctime>


GameEngine::GameEngine(){
    //default state will be start
    state = new char[6];
    strcpy(state,"start");
    isGameEnd = false;
}

GameEngine::GameEngine(char* initialState){

    //IF PASSED STATE IS NULL THEN START STATE
    if(NULL==initialState){
        this->state = new char[6];
        strcpy(state,"start");
        return;
    }

    int size = strlen(initialState);
    state = new char[size+1];
    strcpy(state,initialState);
    isGameEnd = false;
}

GameEngine::GameEngine(const GameEngine &ge){
    if (state)
        delete[] state;
    int len = strlen(ge.state);
    state = new char[len+1];
    strcpy(state,ge.state);
    isGameEnd = ge.isGameEnd;

}
const GameEngine& GameEngine::operator=(const GameEngine& ge){
    if(this == &ge)
        return *this;
    delete[] state;   //First, release the original space of the state
    int len = strlen(ge.state);
    state = new char[len + 1];
    strcpy(state,ge.state);
    return *this;

}

char* GameEngine::getState(){
    return state;
}
bool GameEngine::getEndStatus(){
    return isGameEnd;
}

bool GameEngine::isValidState(char *state){

    //CHECKING FOR ALL THE VALID STATES OF GAME ENGINE
    if (strcmp(state,"start") == 0) return true;
    if (strcmp(state,"map loaded") == 0) return true;
    if (strcmp(state,"map validated") == 0) return true;
    if (strcmp(state,"players added") == 0) return true;
    if (strcmp(state,"assign reinforcement") == 0) return true;
    if (strcmp(state,"issue orders") == 0) return true;
    if (strcmp(state,"execute orders") == 0) return true;
    if (strcmp(state,"win") == 0) return true;

    return false;
}



bool GameEngine::transition(const char* command){

    //FIRST CHECK CURRENT STATE OF GAME
    //THEN CHECK ALL THE VALID COMMANDS FOR THAT CURRENT STATE
    // AND CHANGE CURRENT STATE ACCORDINGLY
    if (strcmp(state,"start") == 0){

        if (strcmp(command,"loadmap") == 0){

            //CHANGING STATE
            delete[] state;
            state = new char[11];
            strcpy(state,"map loaded");
            return true;
        }
        return false;

    }
    if (strcmp(state,"map loaded") == 0){
        if (strcmp(command,"validatemap") == 0){
            delete[] state;
            state = new char[14];
            strcpy(state,"map validated");
            return true;
        }
        if (strcmp(command,"loadmap") == 0)
            return true;
        return false;

    }

    if (strcmp(state,"map validated") == 0){
        if (strcmp(command,"addplayer") == 0){
            delete[] state;
            state = new char[14];
            strcpy(state,"players added");
            return true;
        }
        return false;

    }
    if (strcmp(state,"players added") == 0){
        if (strcmp(command,"assigncountries") == 0){
            delete[] state;
            state = new char[21];
            strcpy(state,"assign reinforcement");
            return true;
        }
        if (strcmp(command,"addplayer") == 0)
            return true;
        return false;

    }


    if (strcmp(state,"assign reinforcement") == 0){
        if (strcmp(command,"issueorder") == 0){
            delete[] state;
            state = new char[13];
            strcpy(state,"issue orders");
            return true;
        }
        return false;

    }

    if (strcmp(state,"issue orders") == 0){
        if (strcmp(command,"endissueorders") == 0){
            delete[] state;
            state = new char[15];
            strcpy(state,"execute orders");
            return true;
        }
        if (strcmp(command,"issueorder") == 0)
            return true;
        return false;

    }

    if (strcmp(state,"execute orders") == 0){
        if (strcmp(command,"win") == 0){
            delete[] state;
            state = new char[4];
            strcpy(state,"win");
            return true;
        }
        if (strcmp(command,"endexecorders") == 0){
            delete[] state;
            state = new char[21];
            strcpy(state,"assign reinforcement");
            return true;
        }

        if (strcmp(command,"endexecorder") == 0)
            return true;
        return false;

    }

    if (strcmp(state,"win") == 0){
        if (strcmp(command,"play") == 0){
            delete[] state;
            state = new char[6];
            strcpy(state,"start");
            return true;
        }
        if (strcmp(command,"end") == 0){
            isGameEnd = 1;
            return true;
        }

        return false;

    }

    return false;
}

istream& operator >> (istream &in,  GameEngine &ge){

    //LOOP UNTIL USER ENTERS CORRECT STATE
    do{
        cout << "Enter the state of Game Engine: ";
        in >> ge.state;
        if (!ge.isValidState(ge.state))
            cout<<"Incorrect state!!! Enter Again\n";
    }while(!ge.isValidState(ge.state));

    return in;
}








GameEngine::~GameEngine(){
    delete[] state;
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


#endif //ASSIGNMENT1_GAMEENGINE_H