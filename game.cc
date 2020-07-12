#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <sstream>

#include "game.h"

#include "Player.h" 
#include "Deck.h"
#include "Card.h"
#include "Table.h"

using namespace std;

//constructor
Game::Game() {
	Deck d;
	hard = false;
}

////////////////************HELPER FUNCTIONS*************/////////////////////

//this function will create a new human or computer player and insert it to the vector of players
vector<Player*> playerInsert(vector<Player*> p, string type, int pnum) {
	if (type == "Human") {
		p.push_back(new HumanPlayer("human", pnum, 0)); //create a new human player
	} else {
		p.push_back(new CompPlayer("comp", pnum, 0)); //create a new computer player
	}
	return p;
}

//initializes the players with either human or computer players
vector<bool> Game::setPlayer(string player_types[], int s) {
	vector<bool> rage;//this vector determines if the rage button will be disabled or enabled
	for (int i = 1; i <= 4; i++) {	//put all 4 players in the players vector
		players = playerInsert(players, player_types[i - 1], i);
	}
	seed = s;
	srand48((long) seed);				//uses the seed 
	for (int i = 0; i < 4; i++) {//determines if the rage button will be enabled (only for humans)
		if (player_types[i] == "Human") {
			rage.push_back(true);
		} else {
			rage.push_back(false);
		}
	}
	return rage;
}

////this function will figure out which player has the card 7S
const int sevenSpade(vector<Player*> p) {
	Card temp(SPADE, SEVEN);
	for (int j = 0; j < p.size(); j++) {
		vector<Card> tempHand = p[j]->getHand();
		for (int i = 0; i < tempHand.size(); i++) { //return the index in p where the player has 7S
			if (temp == tempHand[i]) {
				return j;
			}
		}
	}
}

//this will put each player's score from the previous round to the score vector
vector<int> setScore(vector<int> p, int pnum, vector<Player*> players) {
	p.push_back(players[pnum]->getScore());
	return p;
}

//this will print the winners
string straightWinner(vector<Player*> players) {
	vector<Player*> winners;
	winners.push_back(players[0]); //put the first player's score in the vector

	for (int i = 0; i < 3; i++) { //go through each player to find the lowest score
		if (players[i + 1]->getScore() < winners[0]->getScore()) { //if the next player has a lower score, delete the vector and push that player in the winning vector
			winners.clear();
			winners.push_back(players[i + 1]);
		} else if (players[i + 1]->getScore() == winners[0]->getScore()) { //if the next player has an equal score, store that player in the vector along with the other player in the vector
			winners.push_back(players[i + 1]);
		}
	}
	stringstream ss_winner;
	string msg = "";
	//print the winners in the game (if the scores are equal, print multiple winners)
	for (int i = 0; i < winners.size(); i++) {
		cout << "Player " << winners[i]->getPlayerNum() << " wins!" << endl;
		ss_winner << winners[i]->getPlayerNum();
		msg += "Player " + ss_winner.str() + " wins! \n";
	}
	return msg;
}

//prints the score and discarded cards after each end of the round
string printEachRound(int m, vector<Player*> players, vector<int> tempScore,
		Table t) {

	vector<Card> discards = t.discards(m + 1); //this vector has all the discarded cards for each player
	cout << "Player " << (m + 1) << "'s discards: ";
	for (int i = 0; i < discards.size(); i++) { //print the cards discarded by each player
		cout << discards[i] << " ";
	}
	cout << endl;

	string msg;	//this msg will be passed back to the subject for the view to print the msg via a popup
	stringstream ss;//these stringstream are needed to convert ints to strings (used to display the popup)
	stringstream ss_temp;
	stringstream ss_round;
	stringstream ss_overall;

	ss << m + 1;
	ss_temp << tempScore[m];
	ss_round << (players[m]->getScore() - tempScore[m]);
	ss_overall << (players[m]->getScore());

	msg = "Player " + ss.str() + "'s score: " + ss_temp.str() + " + "//print each player's score
			+ ss_round.str() + " = " + ss_overall.str() + "\n"; //print the score of each player
	return msg;
}

////////////////************CLASS DEFINTIONS*************/////////////////////

//creates a new deck for each new game
void Game::reSeedDeck() {
	Deck deck;
	d = deck;
}

//distributes teh player's hand and begins the new round
string Game::setPlayerHands() {
	Table t;

	d.shuffle();
	//distribute the hands to each player
	for (int i = 0; i < 4; i++) {
		players[i]->setHand(d.distributeDeck(i + 1));
	}

	//nextPlayer will store the current player who is next to play
	nextPlayer = sevenSpade(players);

	if (nextPlayer == 0) {
		temp = 3; //if the first player to play is player 1, then player 4 is the last player to place the card
	} else {
		temp = nextPlayer - 1; //otherwise the previous player to the first player (ex if player 3 starts first, then player 2 will end the round)
	}

	//this vector will store the player's score from the previous round
	tempScore.clear();
	for (int r = 0; r < 4; r++) {
		tempScore = setScore(tempScore, r, players);
	}

	//used to return the msg back to the subject (model will do this) and the view will popup this message
	stringstream ss;
	ss << nextPlayer + 1;
	string num = ss.str();

	string msg = "A new round begins. It's player " + (num)
			+ "'s turn to play.";

	return msg;

}

//plays the game 
string Game::gamePlay() {

	//play the game while the last player has cards remaining
	while (!(players[temp]->isEmpty())) {
		if (players[nextPlayer]->getType()) {			//if the player is human
			handInt.clear();
			discards.clear();

			discards = t.numOfDiscards();//find the number of discards by all players
			vector<Card> hand = players[nextPlayer]->getHand();	//get the current player's hand
			for (int i = 0; i < hand.size(); i++) {
				handInt.push_back(hand[i].getSuit() * 13 + hand[i].getRank());
			}
			tableInt = t.tableInt();//determine the cards placed on the table
			players[nextPlayer]->determinePlay(d, t, true);	//find out if this is a legal play
			return "Human";	//return and the model should call the subject and update the view for the player's (human) turn
		} else if (!players[nextPlayer]->getType()) { //if the computer is playing

			players[nextPlayer]->determinePlay(d, t, hard);	//determine the computer's move
		}
		nextPlayer++;								//move to the next player
		if (nextPlayer == 4) { //move back to the nextPlayer player if the fourth player played last
			nextPlayer = 0;
		}
	}

	if (players[temp]->isEmpty()) {		//if everyone has played all their hands
		string msg;
		for (int m = 0; m < 4; m++) {
			msg += printEachRound(m, players, tempScore, t);//print the round's score
		}
		cout << msg;
		discards = t.numOfDiscards();
		setPlayerScore();
		t.clearTable();	//clear table and popup(via subject that calls the view)  the round's score
		return msg;
	}
}

//returns true if no player has a score > 80
bool Game::getMaxScore() {

	for (int i = 0; i < 4; i++) {
		if (players[i]->getScore() >= 80) {
			return false;
		}
	}
	return true;
}

//prints the winner of the game (popup message will occur)
string Game::getWinner() {
	string msg = straightWinner(players);
	return msg;
}

//clears ALL contents of the game (game has ended completely)
void Game::clearGame() {
	t.clearTable();
	tempScore.clear();
	players.clear();
}

//returns the vector discards
vector<int> Game::getDiscards() const {
	return discards;
}

//returns the vector handInt
vector<int> Game::getHandInt() const {
	return handInt;
}

//returns the vector tableInt
vector<int> Game::getTableInt() const {
	return tableInt;
}

//returns the vector playerScore
vector<int> Game::getPlayerScore() const {
	return playerScore;
}

//places the player's score into the vector playerScore
void Game::setPlayerScore() {
	playerScore.clear();
	for (int i = 0; i < 4; i++) {
		playerScore.push_back(players[i]->getScore());
	}
}

//determines if the card placed by the player is valid
bool Game::validCardPlay(int cardNum, int cardButton) {

	int rank = cardNum % 13;
	int suit = cardNum / 13;

	vector<Card> legal = t.legalPlays(players[nextPlayer]->getHand());

	//if there are no legal plays, the card clicked by the human is discarded
	if (legal.size() == 0) {
		players[nextPlayer]->discardCard(
				(players[nextPlayer]->getHand())[cardButton], t);
		return true;
	}

	//checks if the card pressed is part of the legal set. 
	//if so, print what card the player played and move on to the next player
	for (int i = 0; i < legal.size(); i++) {
		if ((legal[i].getRank() == rank) && (legal[i].getSuit() == suit)) {
			cout << "Player " << nextPlayer + 1 << " plays " << legal[i] << "."
					<< endl;
			t.acceptCard(legal[i], players[nextPlayer]->getHand());
			players[nextPlayer]->eraseCard(legal[i]);
			return true;
		}
	}
	//otherwise, the human plays an illegal play and print this message
	cout << "This is not a legal play." << endl; //need to check if the card placed is a valid card
	return false;
}

//moves to the next player
void Game::addNextPlayer() {
	nextPlayer++;
	if (nextPlayer == 4) {
		nextPlayer = 0;
	}
}

//clears the table (end of round)
void Game::clearTable() {
	t.clearTable();
}

//gets the current player's number
int Game::getCurrentPlayerNum() const {
	return nextPlayer;
}

//handles ragequit from player. Converts the player to a human while keeping all properties from the human.
//print the message and let the computer play the card for the former human player
void Game::rageQuit() {
	cout << "Player " << (players[nextPlayer]->getPlayerNum())
			<< " ragequits. A computer will now take over." << endl; //output that the player has quited the game (computer will take over)
	vector<Card> tempHand = players[nextPlayer]->getHand();	//keep a temp storing the player's current hand
	players[nextPlayer] = new CompPlayer("Comp", (nextPlayer + 1),
			players[nextPlayer]->getScore());
	players[nextPlayer]->setHand(tempHand);
}

void Game::setHard() {
	hard = true; //set the hard flag to true
}
vector<int> Game::getValidIndex() const { //returns the indexes of the valid cards in the hand
	vector<Card> playerHand = players[nextPlayer]->getHand();
	vector<Card> legal = t.legalPlays(playerHand);
	vector<int> legalindex;

	for (int i = 0; i < legal.size(); i++) {
		for (int j = 0; j < playerHand.size(); j++)
			if (legal[i] == playerHand[j]) {
				legalindex.push_back(j);
			}
	}

	return legalindex;
}
