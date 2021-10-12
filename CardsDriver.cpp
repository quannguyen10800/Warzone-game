#include "Card.h"
int main() {
	Deck deck = Deck();
	Hand hand = Hand(deck);
	Card("bomb");
	Card("reinforcement");
	Card("blockade");
	Card("airlift");
	Card("diplomacy");
}