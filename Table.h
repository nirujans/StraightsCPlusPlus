#ifndef _TABLE_
#define _TABLE_
#include <vector>
#include "Card.h"

#include <iostream>
class Table {
public:
	Table();											//constructor
	void acceptCard(Card, std::vector<Card>);				//determines if the card can be played. Processes the card if so, otherwise error message will be displayed
	void acceptDiscard(Card, std::vector<Card>, int);			//determines if the card can be discarded. Discards card if so, otherwise error message will be displayed
	void printTable() const;								//prints table
	void clearTable();									//clears cards on the table
	std::vector<Card> legalPlays(std::vector<Card>) const; 	//given a hand, returns the legal plays depending on whats on the field
	std::vector<Card> discards(int) const;					//pushes discarded cards into a vector of discarded cards
	std::vector<int> numOfDiscards() const;				//finds the number of discarded cards from each player
	std::vector <int> tableInt();							//finds the cards currently present faceup on the table
private:
	std::vector<int> clubsplaced_;
	std::vector<int> diamondsplaced_;
	std::vector<int> heartsplaced_;
	std::vector<int> spadesplaced_;
	std::vector<std::vector<Card> > playersdiscards_;			//vector of discarded cards 
	std::vector<std::vector<int> > suitsplaced_;				//vector of cards placed on the table
	void pushLegal(std::vector<Card>& hand, int& i, std::vector<Card>& legalplays) const;	 //helper function to push legal cards into legal vector
	void pushAndSort(std::vector<Card>, int);				//helper function to insert and sort the array which contains the cards placed on the table					
};

#endif

