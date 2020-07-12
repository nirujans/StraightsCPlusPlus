#include "Card.h"
#include <string>
#include <cassert>
using namespace std;

Card::Card() {

}
Card::Card(Suit s, Rank r) {		//creates a card with a suit and rank
	suit_ = s;
	rank_ = r;
}

Suit Card::getSuit() const {		//returns the suit of the card 
	return suit_;
}

Rank Card::getRank() const {		//returns the rank of the card
	return rank_;
}

bool operator==(const Card &a, const Card &b) {		//compares two cards
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

ostream &operator<<(ostream &out, const Card &c) {//output stream for printing cards
	string suits[SUIT_COUNT] = { "C", "D", "H", "S" };
	string ranks[RANK_COUNT] = { "A", "2", "3", "4", "5", "6", "7", "8", "9",
			"10", "J", "Q", "K" };

	out << ranks[c.getRank()] << suits[c.getSuit()];

	return out;
}

istream &operator>>(istream &in, Card &c) {	//input stream for inputing card values (not used in this program)
	string suits = "CDHS", ranks = "A234567891JQK";

	string str;
	in >> str;
	assert( !in.fail());

	//Read in the rank, make sure it's valid
	c.rank_ = (Rank) ranks.find(str.at(0));
	assert( c.rank_ != string::npos);

	//If it's a 10, make sure the 2nd character is a 0
	if (c.rank_ == TEN) {
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}

	//Read in the suit, make sure it's valid
	c.suit_ = (Suit) suits.find(str.at(1));
	assert( c.suit_ != string::npos);

	return in;
}
