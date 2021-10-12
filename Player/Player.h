//
// Created by Mehrsa Yazdani on 2021-10-03.
//

#ifndef UNTITLED19_PLAYER_H
#define UNTITLED19_PLAYER_H
//using namespace std;
#include <iostream>
#include "list"
#include "../Map/Map.h"
#include "../Orders/Orders.h"

//#include "HandsOfCards.h"
#include  <vector>

class Player{
private:
    //a player own a collection of territories
    vector<Territory*> territories;
    //i dont have the class now so im gonna comment it
    //HandsOfCard *handofcard;
    //A player has their own list of orders to be created and executed in the current turn (see Part 3).
    OrdersList *orders;
    //each player has a name
    string Pname;
    //each player has a number assigned to them
    //this number will be static and will belong to the class each time a player is created , the number will increament
    //and th enumber will be assigned to them
    static  int *number;
    //there  is a territory randlonly assigned to the player at the begining of the game
    Territory *initial = new Territory();
    list<Territory*> toDefend;
    list<Territory*> toAttact;  //*Attack


    //Quan Nguyen
    vector<Player*> diplomaticRelations_;
    bool neutral = false;


public:
    //defualt contructor
    Player();
  //  Player(string s ,vector<Territory*> territories,HandsofCards *handofcard,Orders *orders);
    //contructor with name
    Player(string n);

    //the copy contructor
    Player(const Player &p);

    //assignment operator
    Player& operator=(const Player &p);

    friend ostream& operator<<(ostream&, const Player&);
    //destructer

    ~Player();

    //getters and setters

    void setpName(string *n);

    string getPName();

    vector<Territory*> getTerritories();

    OrdersList* getOrdersList();

    void addOrder(Order *order);

    vector<Territory*> conqures();

    void addTerritory(Territory* territory);

    void removeTerritory(Territory* territory);


//    //Quan Nguyen
    void addDiplomaticRelation(Player* player);
    vector<Player*> getRelations() const;
    bool isNeutral();



    //Hand* getHand();
   // void issueOrder(string s ,vector<Territory*> territories,HandsofCards *handofcard,int priority);

    list<Territory*> to_Defend();
    list<Territory*> to_Attact();











};













#endif //UNTITLED19_PLAYER_H
