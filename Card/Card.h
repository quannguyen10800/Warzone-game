#include <string>
#include <vector>

using namespace std;

class Card{
  
	public:
  
		string type;
  
    Card();
		Card(string t){
			type = t;
		}
  
		void play();
  
};

class Deck{
  
	public:
  
		vector<Card> deck;
  
    Deck();
 		Deck(vector<Card> d){
			deck = d;
		}
  
		void draw(Hand hand);
  
};

class Hand{
  
	public:
  
		vector<Card> hand;
  
    Hand();
		Hand(vector<Card> h){
			hand = h;
		}
  
		void putBack(Card card, Deck deck);
  
};
