//
// Created by mehrsa yazdani on 2021-11-07.
//

#ifndef UNTITLED1_PLATER_H
#define UNTITLED1_PLATER_H

using  namespace std;
#include <iostream>
#include "Map.h"
#include "list"

class Order;
class OrdersList;


using  namespace std;
#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "card.h"
#include  <vector>




class Player{
private:
    //a player own a collection of territories
    vector<Territory*> territories;
    //i dont have the class now so im gonna comment it
    Hand *handofcard;
    //A player has their own list of orders to be created and executed in the current turn (see Part 3).
    OrdersList *orders;
    //each player has a name
    string Pname;

    int numberofarmies;


    //each player has a number assigned to them
    //this number will be static and will belong to the class each time a player is created , the number will increament
    //and th enumber will be assigned to them
    static  int *number;
    //there  is a territory randlonly assigned to the player at the begining of the game
    Territory *initial = new Territory();
    vector <Territory*> toDefend;
    vector <Territory*> toAttact;

    vector<Player*> diplomaticRelations_;
    bool neutral = false;



public:


    //defualt contructor
    Player();
    Player(string s ,vector<Territory*> territories,Hand *handofcard,OrdersList *orders);
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

    //Hand* getHand();
    void issueOrder(Order* ord);

    Territory * random_territory(string continent_name,Map* map);

    void AssignFirstTerritory(Map* map);


    vector<Territory*> to_Defend();

    vector<Territory*> to_Attact();

    int getTheNumberOFArmies();
    void setTheNumberOFArmies(int numb);









};
#endif //UNTITLED1_PLATER_H
