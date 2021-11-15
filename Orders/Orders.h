//
// Created by Quan Nguyen on 2021-10-11.
//




//#pragma once

#include "../Player/Player.h"
#include <iostream>
#include <vector>
//#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"
enum OrderType : short
{
    DEPLOY,
    ADVANCE,
    BOMB,
    BLOCKADE,
    AIRLIFT,
    NEGOTIATE,
};

class Player;

class Order
{
public:
    virtual ~Order();
    friend std::ostream &operator<<(std::ostream &output, const Order &order);
    void execute();
    int getPriority() const;
    virtual Order* clone() const = 0;
    virtual bool validate() const = 0;
    virtual OrderType getType() const = 0;

protected:
    Player* issuer_;
    Order();
    Order(Player* issuer, int priority);
    Order(const Order &order);
    const Order &operator=(const Order &order);
    virtual std::ostream &print_(std::ostream &output) const = 0;
    virtual void execute_() = 0;
    virtual void undo_();

private:
    int priority_;
};

/***
 * The OrderList class contains...
 */
class OrdersList
{
public:
    OrdersList();
    OrdersList(const OrdersList &orders);
    ~OrdersList();
    int size() const;
    void add(Order* order);
    void move(int origin, int targetDestination);
    void remove(int target);
    const OrdersList &operator=(const OrdersList &orders);
    friend std::ostream &operator<<(std::ostream &output, const OrdersList &orders);
    std::vector<Order*> getOrders() const;
    void setOrders(std::vector<Order*> orders);
    Order* popTopOrder();
    Order* peek();


private:
    std::vector<Order*> orders_;
};
/**
 * DeployOrder class contains
 */
class DeployOrder : public Order
{
public:
    DeployOrder();
    DeployOrder(Player* issuer, int numberOfArmies, Territory* destination);
    DeployOrder(const DeployOrder &order);
    const DeployOrder &operator=(const DeployOrder &order);
    void addArmies(int additional);
    bool validate() const;
    OrderType getType() const;
    Order* clone() const;

protected:
    void execute_();
    void undo_();
    std::ostream &print_(std::ostream &output) const;

private:
    int numberOfArmies_;
    Territory* destination_;
};

/**
 * AdvanceOrder class contains
 */
class AdvanceOrder : public Order
{
public:
    AdvanceOrder();
    AdvanceOrder(Player* issuer, int numberOfArmies, Territory* source, Territory* destination);
    AdvanceOrder(const AdvanceOrder &order);
    const AdvanceOrder &operator=(const AdvanceOrder &order);
    Order* clone() const;
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

/**
 * BomOrder class contains
 */
class BombOrder : public Order
{
public:
    BombOrder();
    BombOrder(Player* issuer, Territory* target);
    BombOrder(const BombOrder &order);
    const BombOrder &operator=(const BombOrder &order);
    Order* clone() const;
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Territory* target_;
};

/**
 * BlockadeOrder class contains
 */
class BlockadeOrder : public Order
{
public:
    BlockadeOrder();
    BlockadeOrder(Player* issuer, Territory* territory);
    BlockadeOrder(const BlockadeOrder &order);
    const BlockadeOrder &operator=(const BlockadeOrder &order);
    Order* clone() const;
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Territory* territory_;
};

/**
 * AirLiftOrder contains
 */
class AirliftOrder : public Order
{
public:
    AirliftOrder();
    AirliftOrder(Player* issuer, int numberOfArmies, Territory* source, Territory* destination);
    AirliftOrder(const AirliftOrder &order);
    const AirliftOrder &operator=(const AirliftOrder &order);
    bool validate() const;
    OrderType getType() const;
    Order* clone() const;
protected:
    void execute_();
    void undo_();
    std::ostream &print_(std::ostream &output) const;

private:
    int numberOfArmies_;
    Territory* source_;
    Territory* destination_;
};


class NegotiateOrder : public Order
{
public:
    NegotiateOrder();
    NegotiateOrder(Player* issuer, Player* target);
    NegotiateOrder(const NegotiateOrder &order);
    const NegotiateOrder &operator=(const NegotiateOrder &order);
    Order* clone() const;
    bool validate() const;
    OrderType getType() const;

protected:
    void execute_();
    std::ostream &print_(std::ostream &output) const;

private:
    Player* target_;
};

