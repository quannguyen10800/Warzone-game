#include "Card.h"
#include "../Orders/Orders.h"
#include "iostream"

Card::Card()
{
    //if no card type is specified in the constructor, a random int will be generated to determine the cards type
    type = rand() % 6 + 1;
}

Card::Card(string n)
{
    //if the constructor contains the type, it will be passed through
    name = n;
    if (name.string::compare("bomb")) {
        type = 1;
    }
    else if (name.string::compare("reinforcement")) {
        type = 2;
    }
    else if (name.string::compare("blockade")) {
        type = 3;
    }
    else if (name=="airlift") {
        type = 4;
    }
    else if (name.string::compare("diplomacy")) {
        type = 5;
    }
    else {
        cout << "not a valid card type";
    }
}

int Card::getType() {
    return this->type;
}

string Card::getName() {
    return this->name;
}

void Card::setType(int t) {
    this->type = t;
}
void Card::play(Deck deck, Hand hand)
{
    vector<Card> h = hand.getVector();
    vector<Card> d = deck.getVector();
    //switch statement will check the type of the card being played and run the corresponding code to that card type
    switch (this->type) {
        case 1:
            //code for if card is a bomb
            d.insert(d.end(), std::make_move_iterator(h.begin()), std::make_move_iterator(h.end()));
            break;
        case 2:
            d.insert(d.end(), std::make_move_iterator(h.begin()), std::make_move_iterator(h.end()));
            //code for if card is a reinforcement
            break;
        case 3:
            d.insert(d.end(), std::make_move_iterator(h.begin()), std::make_move_iterator(h.end()));
            //code for if card is a blockade
            break;
        case 4:
            d.insert(d.end(), std::make_move_iterator(h.begin()), std::make_move_iterator(h.end()));
            //code for if card is a airlift
            break;
        case 5:
            d.insert(d.end(), std::make_move_iterator(h.begin()), std::make_move_iterator(h.end()));
            //code for if card is a diplomacy
            break;
        default:
            //code for incompatible int type
            break;
    }
}

Deck::Deck()
{
    std::vector<Card> d;
    //if no deck is provided in the constructor we generate 50 random cards and insert them into a vector 'd'
    for (int i = 0; i < 50; i++) {
        Card card = Card();
        d.push_back(card);
    }
    deck = d;
}

Deck::Deck(vector<Card> d)
{
    //if the constructor contains the deck, it will be passed through
    deck = d;
}

void Deck::draw(Player* player)
{
    vector<Card> h = player->getHand().getVector();
    vector<Card> d = player->getHand().getVector();
    h.insert(h.end(), std::make_move_iterator(d.begin()),std::make_move_iterator(d.end()));
}

Hand::Hand() {
    std::vector<Card> h;
    hand = h;
}

Hand::Hand(Deck deck)
{
    std::vector<Card> h;
    //if the deck is provided in the consructor, we draw 7 cards from the deck
    for (int i = 0; i < 7; i++) {
        deck.draw(h);
    }
    hand = h;
}

Hand::Hand(vector<Card> h)
{
    //if the constructor contains the hand, it will be passed through
    hand = h;
}

vector<Card> Hand::getVector() {
    return this->hand;
}

Card Hand::getCard()
{
    return Card();
}

vector<Card> Deck::getVector() {
    return this->deck;
}

Card Deck::getCard()
{
    return Card();
}
