#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

Player::Player(string type, int playerNum, int score) :
		score_(score), playernum_(playerNum) { //intializes a players type, number and score
	if (type == "human") //set type bit according to whehther they are human
		type_ = true;
	else
		type_ = false;
}

void Player::setHand(vector<Card> c) { //set's the players hand given a vector of cards
	playerHand_ = c;
}

bool Player::isEmpty() const { //checks if there are no cards in the player's hand
	return (playerHand_.size() == 0);
}

vector<Card> Player::getHand() const { //returns the players hand
	return playerHand_;
}

bool Player::getType() const { //returns the type of the player (human or computer)
	return type_;
}

int Player::getPlayerNum() const { //returns the players number (player 2 = 2)
	return playernum_;
}

int Player::getScore() const { //returns the players score
	return score_;
}

void Player::eraseCard(Card c) { //removes a card from their hand
	for (int i = 0; i < playerHand_.size(); i++) { //iterate until we find the card
		if (c == playerHand_[i]) {
			playerHand_.erase(playerHand_.begin() + i); //remove the card
			return;
		}
	}
}

void Player::setScore(int inc) { //set the score of a player
	score_ += (inc + 1);
}

CompPlayer::CompPlayer(string type, int playerNum, int score) :
		Player(type, playerNum, score) {
}

HumanPlayer::HumanPlayer(string type, int playerNum, int score) :
		Player(type, playerNum, score) {
}

void HumanPlayer::printHand() const { //prints the hand
	vector<Card> temp = this->getHand();
	cout << "Your hand: ";
	for (int i = 0; i < temp.size(); i++) { //outputs each card
		cout << temp[i] << " ";
	}
	cout << endl;
}

void HumanPlayer::determinePlay(Deck d, Table& t, bool hard) {
	//loop until a break statement exits the loop
	vector<Card> legal = t.legalPlays(this->getHand()); //retrieves a vector of all cards that are legal
	t.printTable(); //prints the cards on the table
	this->printHand(); //prints the hands for the player
	cout << "Legal Plays: ";
	for (int x = 0; x < legal.size(); x++) { //prints each legal card associated to the human player
		cout << legal[x] << " ";
	}
	cout << endl;
}

void HumanPlayer::discardCard(Card c, Table& t) {
	t.acceptDiscard(c, this->getHand(), this->getPlayerNum()); //acceptDiscard will determine if the user can play any legal cards (it will catch a message if user can play a legal card)
	cout << "Player " << (this->getPlayerNum()) << " discards " << c << "."
			<< endl; //output what the user discard
	this->setScore(c.getRank()); //keep the current score for the user of that round
	this->eraseCard(c); //erase that card from the player's hand
}

void CompPlayer::determinePlay(Deck d, Table &t, bool hard) {
	vector<Card> legal = t.legalPlays(this->getHand()); //legal will store any legal cards that the computer has

	if (legal.size() > 0) { //if the computer has any legal cards, play the first legal card in the vector
		t.acceptCard(legal[0], this->getHand()); //if the user has a valid card, make the computer play the first legal card
		cout << "Player " << (this->getPlayerNum()) << " plays " << legal[0]
				<< "." << endl; //output what legal card the computer played
		this->eraseCard(legal[0]); //erase that card from the computer's hand
	} else {
		vector<Card> temp = this->getHand(); //otherwise, the computer doesn't have a legal card and discard the first card in the computer's hand
		int min = temp[0].getRank();
		Card tempCard = temp[0];

		//if its hard mode, select the card with the lowest rank to minimize score
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].getRank() < min) {

				tempCard = temp[i];
				min = temp[i].getRank();
			}
		}

		if (hard) {
			t.acceptDiscard(tempCard, this->getHand(), this->getPlayerNum()); //discard the first card in the hand
		} else {
			t.acceptDiscard(temp[0], this->getHand(), this->getPlayerNum()); //discard the first card in the hand
		}

		if (!hard) {
			cout << "Player " << this->getPlayerNum() << " discards " << temp[0]
					<< "." << endl; //output the card that has been discarded
			this->setScore(temp[0].getRank()); //keep the current score for the user of that round
			this->eraseCard(temp[0]); //erase that card from the computer's hand
		} else {
			cout << "Player " << this->getPlayerNum() << " discards "
					<< tempCard << "." << endl; //output the card that has been discarded
			this->setScore(tempCard.getRank()); //keep the current score for the user of that round
			this->eraseCard(tempCard); //erase that card from the computer's hand
		}
	}
}

