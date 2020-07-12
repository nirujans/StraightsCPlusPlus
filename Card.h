#ifndef _CARD_
#define _CARD_

#include <ostream>
#include <istream>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };		//enum of suit and rank values
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card{
	friend std::istream &operator>>(std::istream &, Card &);

public:
	Card();				//constructor
	Card(Suit, Rank);		//overriding constructor (passes suit and rank of card)
	Suit getSuit() const;	//accessor - returns suit of card
	Rank getRank() const;	//accessor - returns suit of card
private:
	Suit suit_;				//suit of card
	Rank rank_;			//rank of card
};

bool operator==(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
