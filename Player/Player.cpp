#include "Player.h"
#include "Map.h"
#include "Map.cpp"
#include <iostream>
#include "string"
#include "list"
//initializing  the number to zerp
int *Player::number = new int(0);



Player ::Player() {

    this->territories = vector<Territory *>();
    this->orders = new OrdersList();
    this->hand = new Hand();
    *number=*number+1;
    this->Pname="";
    //function



}
Player ::Player(string s) {
    this->territories = vector<Territory *>();
    this->orders = new OrdersList();
    this->hand = new Hand();
    *number=*number+1;
    this->Pname=s;
    //function

}

Player  ::Player(string s,vector<Territory*> territories,HandsofCards *handofcard,OrdersList *orders) {

    this->territories = territories;
    this->orders = orders;
    this->hand = handofcard;
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
    this->orders = p.orders;
    this->hand = p.hand;
    this->Pname = p.Pname;


}
//operator
Player& Player::operator=(const Player& p) {

    this->territories = p.territories;
    for (int i = 0; i < p.territories.size(); i++){
        this->territories.at(i) = p.territories.at(i);
    }
    this->orders = p.orders;
    this->hand = p.hand;

    return *this;

}

//decontruct
Player ::~Player() {

    delete orders;
    delete hand;

    for (int i = 0; i < territories.size(); i++) {
        delete territories.at(i);

    }
    for (int i = 0; i < toDefend.size(); i++) {
        delete toDefend.front()

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
void Player :: addOrder(Orders *order){
    orders->add(order);
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
        for (int j = 0; j < territories.at(i)->get_neighbouring_territory().size(); j++) {
            aux.push_back(territories.at(i)->get_neighbouring_territory().at(j));


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








}

vector<Territory*> Player ::to_Defend() {
    vector<Territory*> aux;

     for (int i = 0; i < territories.size(); i++) {
        for (int j = 0; j < territories.at(i)->get_neighbouring_territory().size(); j++) {
            aux.push_back(territories.at(i)->get_neighbouring_territory().at(j));


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



}


void Player ::  issueOrder(string s ,vector<Territory*> territories,Hands *handofcard,int priority){
    Player* issuer =new Player(s,territories,handofcard,orders);
    Order* m=new Order(issuer,priority);
    orders->add(m);

}



Territory * Player::random_territory(string continent_name,Map* map){
    for(Continent *continent : map->continents){
        if (continent->get_name() == continent_name){
            int r = rand() % (continent->get_territories().size() -1);
            return continent->get_territories().at(r);
        }
    }
}


void Player :: AssignFirstTerritory(Map *map){
      int  random=rand() % map->continents.size() -1;
      territories.push_back(random_territory(map->continents.at(random)->get_name(),map));


}
