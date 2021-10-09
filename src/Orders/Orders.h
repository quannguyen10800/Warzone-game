//
// Created by Quan Nguyen on 2021-09-26.
//

#ifndef COMP345_ASS1_PART3_ORDERLIST_H
#define COMP345_ASS1_PART3_ORDERLIST_H

#endif //COMP345_ASS1_PART3_ORDERLIST_H

#pragma once

//#include "../Map/Map.h"
//#include "../Players/Players.h"
#include <iostream>
#include <vector>

class Players;
class Territory;

enum OrderType : short
{
    DEPLOY,
    ADVANCE,
    BOMB,
    BLOCKADE,
    AIRLIFT,
    NEGOTIATE,
};


class Orders
{
public:
    virtual ~Orders();
    friend std::ostream &operator<<(std::ostream &output, const Orders &order);
    void execute();
    int getPriority() const;
    virtual Orders* clone() const = 0;
    virtual bool validate() const = 0;
    virtual OrderType getType() const = 0;

protected:
    Players* issuer_;
    Orders();
    Orders(Players* issuer, int priority);
    Orders(const Orders &order);
    const Orders &operator=(const Orders &order);
    virtual std::ostream &print_(std::ostream &output) const = 0;
    virtual void execute_() = 0;
    virtual void undo1();

private:
    int priority_;
};


class OrdersList
{
public:
    OrdersList();
    OrdersList(const OrdersList &orders);
    ~OrdersList();
    const OrdersList &operator=(const OrdersList &orders);
    friend std::ostream &operator<<(std::ostream &output, const OrdersList &orders);
    std::vector<Orders*> getOrders() const;
    void setOrders(std::vector<Orders*> orders);
    Orders* displayTopOrder();
    Orders* displayTopOrderWithoutRemoving();
    int size() const;
    void add(Orders* order);
    void move(int source, int destination);
    void remove(int target);

private:
    std::vector<Orders*> orders_;
};


class DeployOrder : public Orders
{
public:
    DeployOrder();
    DeployOrder(Players* issuer, int numberOfArmies, Territory* destination);
    DeployOrder(const DeployOrder &order);
    const DeployOrder &operator=(const DeployOrder &order);
    Orders* clone() const;
    void gatherArmy(int additional);
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    void undo1();
    std::ostream &print_(std::ostream &output) const;

private:
    int numberOfArmies_;
    Territory* destination_;
};


class AdvanceOrder : public Orders
{
public:
    AdvanceOrder();
    AdvanceOrder(Players* issuer, int numberOfArmies, Territory* source, Territory* destination);
    AdvanceOrder(const AdvanceOrder &order);
    const AdvanceOrder &operator=(const AdvanceOrder &order);
    Orders* clone() const;
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    void undo_();
    std::ostream &print_(std::ostream &output) const;

private:
    int numberOfArmies_;
    Territory* source_;
    Territory* destination_;
};


class BombOrder : public Orders
{
public:
    BombOrder();
    BombOrder(Players* issuer, Territory* target);
    BombOrder(const BombOrder &order);
    const BombOrder &operator=(const BombOrder &order);
    Orders* clone() const;
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Territory* target_;
};


class BlockadeOrder : public Orders
{
public:
    BlockadeOrder();
    BlockadeOrder(Players* issuer, Territory* territory);
    BlockadeOrder(const BlockadeOrder &order);
    const BlockadeOrder &operator=(const BlockadeOrder &order);
    Orders* clone() const;
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Territory* territory_;
};


class AirliftOrder : public Orders
{
public:
    AirliftOrder();
    AirliftOrder(Players* issuer, int numberOfArmies, Territory* source, Territory* destination);
    AirliftOrder(const AirliftOrder &order);
    const AirliftOrder &operator=(const AirliftOrder &order);
    Orders* clone() const;
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    void undo_();
    std::ostream &print_(std::ostream &output) const;

private:
    int numberOfArmies_;
    Territory* source_;
    Territory* destination_;
};


class NegotiateOrder : public Orders
{
public:
    NegotiateOrder();
    NegotiateOrder(Players* issuer, Players* target);
    NegotiateOrder(const NegotiateOrder &order);
    const NegotiateOrder &operator=(const NegotiateOrder &order);
    Orders* clone() const;
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Players* target_;
};