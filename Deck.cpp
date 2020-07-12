#include "Deck.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

Suit suits[4] = { CLUB, DIAMOND, HEART, SPADE };	//arrays of suits and ranks
Rank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING };

Deck::Deck() {
	size_ = 0;
	for (int i = 0; i < 4; i++) { //initialize the deck based from A-K C, A-K D, A-K H, A-K S
		for (int j = 0; j < 13; j++) {
			deck_.push_back(Card(suits[i], ranks[j]));
			size_++;
		}
	}
}

void Deck::shuffle() { //using the shuffle algorithm provided
	int n = size_;
	while (n > 1) {
		int k = (int) (lrand48() % n);
		--n;
		Card c = deck_[n];
		deck_[n] = deck_[k];
		deck_[k] = c;
	}
}

void Deck::printDeck() const { //print the deck based of the format asked for
	for (int i = 0; i < size_; i++) {
		cout << deck_[i] << " ";
		if ((i == 12) || (i == 25) || (i == 38) || (i == 51)) //only 13 cards per line
			cout << "" << endl;

	}
}

vector<Card> Deck::distributeDeck(int playerNumber) const { //method that returns a player their hand given their player number
	vector<Card> temp; 			//temporary vector
	playerNumber--; 				//for indexing purposes
	int start = 13 * playerNumber; 	//ex. player 2 will get cards from 26 to 39
	int end = 13 * (playerNumber + 1);
	for (int i = start; i < end; i++)
		temp.push_back(deck_[i]);

	return temp; 	//return the section of each deck to the appropriate player
}

