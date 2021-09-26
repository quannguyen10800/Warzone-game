//
// Created by Quan Nguyen on 2021-09-26.
//

#ifndef COMP345_ASS1_PART3_ORDERLIST_H
#define COMP345_ASS1_PART3_ORDERLIST_H

#endif //COMP345_ASS1_PART3_ORDERLIST_H

#pragma once
#include <iostream>
#include <string>
#include <vector>

//#include "Map.h"
//#include "Cards.h"

using namespace std;

class OrderList {

private:
    string explanation;

public:
    OrderList();
    virtual void execute() = 0;  //Abstract
    string getDescription();
    void setDescription(string orderName);

    //Copy Constructor
    OrderList(const OrderList& order);

    //Assign operator
    void operator=(const OrderList& order);

    //Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const OrderList& order);
    friend istrean& operator<<(istream& in, OrderList& order);

};

//Derived classes for orders
//----------------DEPLOY------------//
class Deploy : public OrderList {

private:
    bool checkIfValid{false};
    int armyNum;
    string territory; //put it as node of territory
public:
    //constructor
    Deploy();
    Deploy(Player* player, int army, Territory* territory1)
};