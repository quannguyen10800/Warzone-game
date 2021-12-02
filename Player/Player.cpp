//
// Created by mehrsa yazdani on 2021-11-07.
//

#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Card/Card.h"
#include <iostream>
#include "string"
#include "list"
//initializing  the number to zerp
int *Player::number = new int(0);



Player ::Player() {

    this->territories = vector<Territory *>();
    this->orders = new OrdersList();
    this->handofcard = new Hand();
    *number=*number+1;
    this->Pname="";
    //function



}
Player ::Player(string s) {
    this->territories = vector<Territory *>();
    this->orders = new OrdersList();
    this->handofcard = new Hand();
    *number=*number+1;
    this->Pname=s;
    //function

}

Player  ::Player(string s,vector<Territory*> territories,Hand *handofcard,OrdersList *orders) {

    this->territories = territories;
    this->orders = orders;
    this->handofcard = handofcard;
    *number=*number+1;
    this->Pname=s;
    //functio

}
//copy constructor
Player::Player(const Player &p){
    this->territories = p.territories;
    for (int i = 0; i < p.territories.size(); i++){
        this->territories.at(i) = p.territories.at(i);
    }
    orders =p.orders;
    handofcard = p.handofcard;
    Pname = p.Pname;


}
//operator
Player& Player::operator=(const Player& p) {

    this->territories = p.territories;
    for (int i = 0; i < p.territories.size(); i++){
        this->territories.at(i) = p.territories.at(i);
    }
    this->orders = p.orders;
    this->handofcard = p.handofcard;

    return *this;

}

//decontruct
Player ::~Player() {

    delete orders;
    delete handofcard;

    for (int i = 0; i < territories.size(); i++) {
        delete territories.at(i);

    }
    for (int i = 0; i < toDefend.size(); i++) {
        delete toDefend.front();

    }
    for (int i = 0; i < toAttact.size(); i++) {
        delete toAttact.front();

    }
}

//setname
void Player :: setpName(string *n){
    this->Pname=*n;

}
//get the name
string Player ::getPName() {
    return Pname;
}


//get the territories
vector<Territory*> Player  :: getTerritories() {
    return territories;
}

//get the orderslist
OrdersList* Player ::getOrdersList()  {
    return orders;

}
//add to otderlist
void Player ::  issueOrder(Order* ord){

    orders->add(ord);

}

Hand* Player:: getHand(){
    return handofcard;
}


//add a territories to the vector of the territories
void Player ::addTerritory(Territory *territory) {
    territories.push_back(territory);
}


//remove a territories from the  territories
void Player ::removeTerritory(Territory *territory) {
    for (int i = 0; i < territories.size(); i++) {
        if(territories.at(i)->get_name() == territory->get_name()){
            territories.erase(territories.begin()+i);

        }

    }
}


vector<Territory*> Player ::to_Attact() {
    vector<Territory*> aux;

    for (int i = 0; i < territories.size(); i++) {
        for (int j = 0; j < territories.at(i)->get_bordering_territory().size(); j++) {
            aux.push_back(territories.at(i)->get_bordering_territory().at(j));


        }

    }


    for (int i=0;i<aux.size();i++){
        for (int j=0;j<territories.size();j++){
            if(aux.at(i)->get_name() == territories.at(j)->get_name()){
                break;
            }else
            {
                toDefend.push_back(aux.at(i));
            }
        }
    }



    return toAttact;




}

vector<Territory*> Player ::to_Defend() {
    vector<Territory*> aux;

    for (int i = 0; i < territories.size(); i++) {
        for (int j = 0; j < territories.at(i)->get_bordering_territory().size(); j++) {
            aux.push_back(territories.at(i)->get_bordering_territory().at(j));


        }

    }

    for (int i=0;i<aux.size();i++){
        for (int j=0;j<territories.size();j++){
            if(aux.at(i)->get_name() == territories.at(j)->get_name()){
                break;
            }else
            {
                toAttact.push_back(aux.at(i));
            }
        }
    }


    return toDefend;

}





//Territory * Player::random_territory(string continent_name,Map* map){
//    for(Continent *continent : map->continents){
//        if (continent->get_name() == continent_name){
//            int r = rand() % (continent->get_territories().size() -1);
//            return continent->get_territories().at(r);
//        }
//    }
//}
//
//
//void Player :: AssignFirstTerritory(Map *map){
//    int  random=rand() % map->continents.size() -1;
//    territories.push_back(random_territory(map->continents.at(random)->get_name(),map));
//
//
//}

int Player::getTheNumberOFArmies() {
    return numberofarmies;
}
void Player::setTheNumberOFArmies(int num) {
    numberofarmies=num;
}


void Player :: printVector(vector<Territory*> a){

    for (int i = 0; i < a.size() ; i++) {
        cout << a.at(i) <<endl;

    }

}

void Player::setPlayerCards(Hand *&PlayerCards) {
    this->playerCards = PlayerCards;
}


// Get a list of territories with available armies for moving
std::vector<Territory*> Player::getOwnTerritoriesWithMovableArmies() const
{
    std::vector<Territory*> territories;
    for (const auto &territory : ownedTerritories_)
    {
        if (territory->getNumberOfMovableArmies() > 0)
        {
            territories.push_back(territory);
        }
    }

    return territories;
}