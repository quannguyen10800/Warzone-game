//
// Created by Mehrsa Yazdani on 2021-10-03.
//

#include <iostream>
#include "string"
#include "list"
#include "Player.h"
#include "../Map/Map.h"

//initializing  the number to zerp
int *Player::number = new int(0);



Player ::Player() {
    this->territories = vector<Territory *>();
    this->orders = new OrdersList();
   // this->hand = new Hand();

    *number=*number+1;
    this->Pname="";
    //function
    // this->initial;
    territories.push_back(initial);

}
Player ::Player(string s) {
    this->territories = vector<Territory *>();
    this->orders = new OrdersList();
  //  this->hand = new Hand();

    *number=*number+1;
    this->Pname=s;
    //function
   // this->initial;
    territories.push_back(initial);

}
//
//Player ::Player(string s,vector<Territory*> territories, HandsofCards *handofcard,OrdersList *orders) {
//
//    this->territories = territories;
//    this->orders = orders;
//    this->hand = handofcard;
//
//    *number=*number+1;
//    this->Pname=s;
//    //function
//    this->initial;
//    territories.push_back(initial);
//
//}
//copy constructor
Player::Player(const Player &p){
    this->territories = p.territories;
    for (int i = 0; i < territories.size(); i++){
        this->territories.at(i) = p.territories.at(i);
    }
    this->orders = p.orders;
   // this->hand = p.hand;
    this->Pname = p.Pname;


}
//operator
Player& Player::operator=(const Player& p) {

    this->territories = p.territories;
    this->orders = p.orders;
   // this->hand = p.hand;

    return *this;

}

//decontruct
Player ::~Player() {

    delete orders;
   // delete hand;

    for (int i = 0; i < territories.size(); i++) {
        delete territories.at(i);

    }
    for (int i = 0; i < toDefend.size(); i++) {
     //   delete toDefend.front()

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
void Player :: addOrder(Order *order){
    orders->add(order);
}

//add a territories to the vector of the territories
void Player ::addTerritory(Territory *territory) {
    territories.push_back(territory);
}


//remove a territories from the  territories
void Player ::removeTerritory(Territory *territory) {
    for (int i = 0; i < territories.size(); i++) {
        if(territories.at(i)->getName() == territory->getName()){
            territories.erase(territories.begin()+i);

        }

    }
}


list<Territory*> Player ::to_Attact() { //TODO
    list<Territory*> aux;
    for (int i = 0; i < territories.size(); i++) {
        list<Territory*> aux;
        aux=territories.at(i)->neighbours();

    }
    list<Territory*>::iterator it = aux.begin();
    for (int i=0;i<aux.size();i++){
        for (int j=0;j<territories.size();j++){
            if(advance(it,i).getName() == territories.at(j)->getName()){
             break;
            }else
            {
                toAttact.push_back(advance(it,i));
            }
        }
    }



}

list<Territory*> Player ::to_Defend() {   //TODO
    list<Territory*> aux;
    for (int i = 0; i < territories.size(); i++) {
        list<Territory*> aux;
        aux=territories.at(i)->neighbours();

    }
    list<Territory*>::iterator it = aux.begin();
    for (int i=0;i<aux.size();i++){
        for (int j=0;j<territories.size();j++){
            if(advance(it,i).getName() == territories.at(j)->getName()){
                break;
            }else
            {
                toDefend.push_back(advance(it,i));
            }
        }
    }



}

bool Player::isNeutral() {
    return neutral;
}

// Add an enemy player to the list of diplomatic relations for this player
void Player::addDiplomaticRelation(Player* player)
{
    diplomaticRelations_.push_back(player);
}

std::vector<Player *> Player::getRelations() const
{
    return diplomaticRelations_;
}

void Player ::  issueOrder(string s ,vector<Territory*> territories,HandsofCards *handofcard,int priority){     //TODO
    Player issuer =new Player(s,territories,handofcard,orders);
    Orders m=new Orders(issuer,priority);
    orders->add(m);

}



