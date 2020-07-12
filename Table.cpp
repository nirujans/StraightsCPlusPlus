#include "Table.h"
#include <string>
#include <iostream>

using namespace std;

Table::Table() {
	playersdiscards_.resize(4); //initialize the vector that contains each players discards to 4 (4 players)
	suitsplaced_.resize(4); //initialize the vector that contains the number of cards placed for each suit
}

void pushandSort(vector<int> &cards, int rank) { //helper function to insert and sort the array which contains the cards placed on the table
	cards.push_back(rank);
	//insertion sort since size is relatively small, and will be mostly sorted each time
	int j = 0, key = 0;
	for (int i = 1; i < cards.size(); ++i) {
		key = cards[i];
		j = i - 1;
		while ((j >= 0) && (cards[j] > key)) {
			cards[j + 1] = cards[j];
			j -= 1;
		}
		cards[j + 1] = key;
	}

}
void Table::acceptCard(Card card, vector<Card> hand) {
	string message = "This is not a legal play."; //need to check if the card placed is a valid card
	const char *p;
	p = message.c_str();

	vector<Card> legal = legalPlays(hand); //find all valid cards based of their hand
	bool found = false;
	for (int i = 0; i < legal.size(); i++) {
		if (card == legal[i]) {
			found = true; //if the card is valid
			break;
		}
	}
	if (!found) //if the card placed is not valid throw message
		cout << message << endl;

	int suit = card.getSuit();
	int rank = card.getRank();

	pushandSort(suitsplaced_[suit], rank);
}

//checks if the discarded card is legal or not. It will appropriately perform a set of actions based on this result
void Table::acceptDiscard(Card card, vector<Card> hand, int playernumber) {
	string message = "You have a legal play. You may not discard."; //need to check if the card placed is a valid card
	const char *p;
	p = message.c_str();

	vector<Card> legal = legalPlays(hand); //find all valid cards based of their hand
	if (legal.size() > 0)
		cout << message << endl;
	else {
		playersdiscards_[playernumber - 1].push_back(card);
	}

}

//returns the discards of each player
vector<Card> Table::discards(int playernumber) const {
	return playersdiscards_[playernumber - 1];
}

void Table::pushLegal(vector<Card>& hand, int& i,
		vector<Card>& legalplays) const { //helper function to push legal cards into legal vector
	for (int suit = 0; suit < 4; suit++) { //starting at clubs through spades
		if (suitsplaced_[suit].size() > 0) { //check if there is atleast one card of that suit placed on the table
			int lower = suitsplaced_[suit][0]; //they can play one lower than the lowest card
			int upper = suitsplaced_[suit][suitsplaced_[suit].size() - 1]; //they can play one higher than the highest card
			if (!(lower == 0) && (hand[i].getSuit() == suit)
					&& (hand[i].getRank() == (lower - 1))) //check if  the card is same suit, and one lower than the lowest
				legalplays.push_back(hand[i]);
			if (!(upper == 12) && (hand[i].getSuit() == suit)
					&& (hand[i].getRank() == (upper + 1))) //check if the card is same suit, and one higher than the card
				legalplays.push_back(hand[i]);
		}
	}
}

vector<Card> Table::legalPlays(vector<Card> hand) const { //returns a vector of cards which contains the legal plays a player can make
	vector<Card> legalplays;

	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].getRank() == 6) { //they can play any seven
			if (hand[i].getSuit() == 3) { //if you have 7S you must play the seven of spades
				legalplays.clear(); //no other cards can be played
				legalplays.push_back(hand[i]);
				break;
			} else {
				legalplays.push_back(hand[i]);
			}

		}
		pushLegal(hand, i, legalplays); //use the helper function to find rest of legal cards
	}

	return legalplays;
}

void Table::printTable() const { //method to print cards on a table

	string numtoRank[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10",
			"J", "Q", "K" };

	cout << "Cards on the table:" << endl;
	cout << "Clubs: ";
	for (int i = 0; i < suitsplaced_[0].size(); i++)
		cout << numtoRank[suitsplaced_[0][i]] << " ";
	cout << "\nDiamonds: ";
	for (int i = 0; i < suitsplaced_[1].size(); i++)
		cout << numtoRank[suitsplaced_[1][i]] << " ";
	cout << "\nHearts: ";
	for (int i = 0; i < suitsplaced_[2].size(); i++)
		cout << numtoRank[suitsplaced_[2][i]] << " ";
	cout << "\nSpades: ";
	for (int i = 0; i < suitsplaced_[3].size(); i++)
		cout << numtoRank[suitsplaced_[3][i]] << " ";
	cout << "" << endl;
}

void Table::clearTable() { //clear the table when the roung changes
	for (int i = 0; i < 4; i++) {
		playersdiscards_[i].clear();
		suitsplaced_[i].clear();
	}
	clubsplaced_.clear();
	diamondsplaced_.clear();
	heartsplaced_.clear();
	spadesplaced_.clear();
}

//calculates the number of discarded cards for each players and returns that vector
vector<int> Table::numOfDiscards() const {
	vector<int> discards;
	for (int i = 0; i < 4; i++) {
		discards.push_back(playersdiscards_[i].size());
	}
	return discards;
}

//finds which cards have been placed on the table and places it into a vector of ints (returns that vector)
vector<int> Table::tableInt() {
	vector<int> tableInt;
	for (int i = 0; i < suitsplaced_[0].size(); i++) {
		tableInt.push_back(suitsplaced_[0][i]);
	}
	for (int i = 0; i < suitsplaced_[1].size(); i++) {
		tableInt.push_back(13 + suitsplaced_[1][i]);
	}
	for (int i = 0; i < suitsplaced_[2].size(); i++) {
		tableInt.push_back(26 + suitsplaced_[2][i]);
	}
	for (int i = 0; i < suitsplaced_[3].size(); i++) {
		tableInt.push_back(39 + suitsplaced_[3][i]);
	}
	return tableInt;
}
