#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Table.h"
#include "Deck.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Player{
public:
	Player(){}						//constructor
	Player(std::string, int, int);			//overriding constructor
	virtual ~Player(){}					//destructor
	void setHand(std::vector<Card>);		//mutator - sets the player's hand
	std::vector<Card> getHand() const;	//accessor - gets the player's hand
	bool getType() const;				//accessor - gets the player's type
	bool isEmpty() const;				//returns true if the last player to play has an empty hand
	int getScore() const; 				//accessor - get the players score accessor
	void setScore(int);					//mutator - sets the players score
	int getPlayerNum() const;			//accessor - returns the player's number
	virtual void printHand() const{}		//prints the player's hand
	virtual void determinePlay(Deck d, Table& t, bool hard) {};	//determines if the play is valid or not
	virtual void discardCard(Card c, Table& t){};		//discards the card if there are no legal cards to play
	void eraseCard (Card);				//erases the card from the player's hand
protected:
	bool type_;  						//type of player: human or computer
	int score_;						//player's score
	int playernum_;					//player's number 
	std::vector<Card> playerHand_;		//vector storing the player's hand
};

class CompPlayer: public Player{			//computer class for computer players
public:	
	CompPlayer (std::string, int, int);		//constructor
	void determinePlay(Deck d, Table& t,bool hard);	//automatically plays for the computer
	void discardCard(Card c, Table&t) {};	//discards cards for computer automatically
	~CompPlayer(){}					//destructor
};


class HumanPlayer: public Player{			//human class for human players
public:		
	HumanPlayer (std::string, int, int);		//constructor
	~HumanPlayer(){}					//destructor
	void printHand() const;				//prints the human player's hand
	void determinePlay(Deck d, Table& t,bool hard);	//determines if the human has played a valid hand (if valid, plays the card)
	void discardCard(Card c, Table& t);		//discards the card if there are no other legal plays (checks for this since this is a human player)
};

#endif
