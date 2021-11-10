#include "Card.h"
int main() {
    Deck deck = Deck();
    Hand hand = Hand(deck);

    vector<Card> h = hand.getVector();
    for (int i = 0; i < h.size();i++) {
        h[i].play(deck,hand);
    }
}
