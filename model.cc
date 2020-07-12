/*
 * Model class.  Is responsible keeping track of the deck of cards.  
 * It knows nothing about views or controllers.
 * Gets all knowledge about the game from game.h 
 */

#include <gtkmm.h>
#include "model.h"
#include "game.h"
#include <iostream>

using namespace std;

Model::Model() {
}	//constructor

//determines if rage button is enabled or disabled
vector<bool> Model::setPlayerTypes(string player_types[], int s) {
	vector<bool> rage = g.setPlayer(player_types, s);
	return rage;
}

//toggles button's label from human to computer and vice versa
string Model::playerButton(Glib::ustring playerLabel) {
	if (playerLabel != "Rage") {
		if (playerLabel == "Computer") {
			playerLabel = "Human";
		} else {
			playerLabel = "Computer";
		}
		return playerLabel;
	}
}

//creates a new deck at the beggining of each new game
void Model::reSeedDeck() {
	g.reSeedDeck();
}

//distribute the deck to each player's hand
void Model::setPlayerHand() {
	string msg = g.setPlayerHands();
	playerturn(msg);
}

//plays the game
void Model::gamePlay() {
	string outcome = g.gamePlay();

	//if outcome is a player, then let player make their move
	//otherwise the round has ended, and get the player's highest score from that round and if its less than 80, call setPlayerHand()
	if (outcome != "Human") {
		while (outcome != "Human") {
			endRound(outcome, g.getDiscards(), g.getPlayerScore());	//update the player's score and discards at the end of round
			if (g.getMaxScore()) {//if no one has reached a score of more than 80, continue to play and go to the next round
				g.clearTable();
				notifyTableClear();	//clear table and its content
				setPlayerHand(); 	//call's model setPlayerHand
				outcome = g.gamePlay();
			} else {
				string winner = g.getWinner();//if someone has reached a score of more than 80, then print the winners (and create a popup)
				endGame(winner);
				return;
			}
		}
	}

	if (outcome == "Human") {//if the player is human, then update the interface and make the human player see the updated table, their hand, all all of the player's score and num of discarded cards
		updateInterface(g.getDiscards(), g.getHandInt(), g.getTableInt(),
				g.getValidIndex());
	}
}

//returns true if no one has more than 80 points
bool Model::getMaxScore() {
	return (g.getMaxScore());
}

//returns the winners of the game
string Model::getWinner() {
	return (g.getWinner());
}

//clears all the contents in the game
void Model::clearGame() {
	g.clearGame();
}

//returns true if the card played is valid and processes the card
//otherwise, returns false, and print that the card is an invalid card to play 
bool Model::validCardPlay(int cardNum, int cardButton) {
	return g.validCardPlay(cardNum, cardButton);
}

//move to the next player
void Model::addNextPlayer() {
	g.addNextPlayer();
}

//returns the current player's number
int Model::getCurrentPlayerNum() const {
	return (g.getCurrentPlayerNum());
}

void Model::setHard() {
	g.setHard(); //set the flag in game to hard
}
//handles a ragequit from the user. converts the human player to a computer player (keeps its property)
void Model::rageQuit() {
	g.rageQuit();
}
