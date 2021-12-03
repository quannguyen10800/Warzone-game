#pragma once

#include <string>
#include <vector>
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include <iostream>
#include "../Player/Player.h"
class Deck;
class Hand;
using namespace std;

class Card {
private:
    //type of card to know what this card will do
    int type;
    string name;
public:
    //empty constructor
    Card();
    //constructor with card type
    Card(string s);

    //void method to play a card
    void play(Deck deck, Hand hand);

    //getters
    int getType();
    string getName();

    //setter
    void setType(int type);
    virtual Order* play() const = 0;
    Card* removeCard(int position);

    void setOwner(Player *owner);

protected:
    Player* owner_;

};

class Deck {
private:
    //a deck is a vector of cards
    vector<Card> deck;
public:
    //empty constructor
    Deck();
    //constructor that takes a vector of cards
    Deck(vector<Card> d);

    //void method to add a card from the deck vector to the hand
    void draw(Player* player);
    //getters
    vector<Card> getVector();
    Card getCard();

    int size() const;
    std::vector<Card*> getCards() const;

    void addCard(Card *pCard);
};

class Hand {
private:
    //a hand is a vector of cards
    vector<Card*> hand;
    std::vector<Card*> cards_;
public:
    //empty constructor
    Hand();
    //constructor that draws from the deck
    Hand(Deck deck);
    //constructor that takes a vector of cards
    Hand(vector<Card> h);
    //getters
    vector<Card> getVector();
    Card getCard();
    Hand(const vector<Card*> &cards);
    int size() const;
    std::vector<Card*> getCards() const;

    Card *removeCard(int position);
};