
#ifndef UNTITLED19_PLAYER_H
#define UNTITLED19_PLAYER_H
using  namespace std;
#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "list"




using  namespace std;
#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include  <vector>




class Player{
private:
    //a player own a collection of territories
    vector<Territory*> territories;
    //i dont have the class now so im gonna comment it
    HandsOfCard *handofcard;
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
    vector <Territory*> toDefend;
    vector <Territory*> toAttact;

    vector<Player*> diplomaticRelations_;
    bool neutral = false;

    vector<PLayer*> diplomaticRelations_ ;
    bool neutral = false;



public:


    //defualt contructor
    Player();
    Player(string s ,vector<Territory*> territories,HandsofCards *handofcard,Orders *orders);
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

    void addOrder(Orders *order);

    vector<Territory*> conqures();

    void addTerritory(Territory* territory);

    void removeTerritory(Territory* territory);

    //Hand* getHand();
    void issueOrder(string s ,vector<Territory*> territories,HandsofCards *handofcard,int priority);

    Territory * random_territory(string continent_name,Map* map);

    void AssignFirstTerritory(Map* map);


    vector<Territory*> to_Defend();

    vector<Territory*> to_Attact();


    void addDiplomaticRelation(Player *pPlayer);
    vector<Player*> getRelations()const;
};

