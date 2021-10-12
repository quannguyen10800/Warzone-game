#include <string>
#include <vector>
#include "Card.h"

using namespace std;

class Card{
	public:
		string type;
		Card(string t){
			type = t;
		}
		void play();
};
class Deck{
	public:
		vector<Card> deck;
		Deck(vector<Card> d){
			deck = d;
		}
		void draw(Hand hand);
};
class Hand{
	public:
		vector<Card> hand;
		Hand(vector<Card> h){
			hand = h;
		}
		void putBack(Card card, Deck deck);
};
void Card::play(Deck deck){
	if (Card.type == "bomb"){
		Card.putBack(deck);
	}
	else if(Card.type == "reinforcement"){
		Card.putBack(deck);
	}
	else if(Card.type == "blockade"){
		Card.putBack(deck);
	}
	else if(Card.type == "airlift"){
		Card.putBack(deck);
	}
	else if(Card.type == "diplomacy"){
		Card.putBack(deck);
	}
}
void Deck::draw(Hand hand){
	
}
void Hand::putBack(Card card, Deck deck){
	
}
