
//
// Created by Mehrsa Yazdani on 2021-10-07.
//
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Map.cpp"
#include "Player .cpp"
using namespace std;


int main(){

    Territory* t1=new Territory(1,"Tehran",2);
    Territory* t2=new Territory(1,"shomal",2);
    Territory* t3=new Territory(1,"jonob",2);
    Territory* t4=new Territory(1,"gharb",2);
    Territory* t5=new Territory(1,"sahrgh",2);
    Territory* t6=new Territory(1,"west cost ",2);
    vector<Territory*> practice;
    practice.push_back(t1);
    practice.push_back(t2);
    practice.push_back(t3);
    practice.push_back(t4);
    practice.push_back(t5);
    handOfCard* hand=new handOfCard();
    OrdersList* orders=new OrdersList();


    Player* p1=new Player();
    Player* p2=new Player("mehrsa");
    Player* p3=new Player("mehrsa",practice,hand,orders);
    Player* p4;
    p4=p3;
    string * s1=new string("terry");


    p1->setpName(s1);
    p2->setpName(s1);
    p3->setpName(s1);
    p4->setpName(s1);

    vector<Territory*> hi=p1->getTerritories();
    p1->addTerritory(t6);

    cout << p1->getTerritories()<<endl;
    p1->removeTerritory(t6);
    cout << p1->getTerritories()<<endl;

    
    cout<<"list of territories to be attacted"<< p1->to_Attact()<<endl;
    cout<<"list of territories to be defended"<< p1->to_Defend()<<endl;



    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;


}