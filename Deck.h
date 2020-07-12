#ifndef _DECK_
#define _DECK_
#include <vector>
#include "Card.h"

#include <iostream>
class Deck {
public:
	Deck();										//constructor
	void shuffle(); 				//uses a shuffling algorithm to shuffle deck
	void printDeck() const; 							//method to print deck
	std::vector<Card> distributeDeck(int) const; //splits the deck into the appropriate section and
private:
	std::vector<Card> deck_;	//private member that contains  the deck
	int size_; 					//size of the deck
};

#endif
