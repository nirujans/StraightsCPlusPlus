/*
 Game Class Design Pattern
 Controls the logic of the game (almost all the code were from our Project part 1)
 It knows all the data and information that the game currently is processing and manipulating with
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Table.h"

class Game {
public:
	Game();												//constructor
	std::vector<bool> setPlayer(std::string player_types[], int);//initializes players (human or computer)
	std::string setPlayerHands();//distributes cards to players, and begins round
	std::string gamePlay();	//plays the game (computer will automatically play itself, and players will be handed with the updated view if its their turn)
	bool getMaxScore();	//returns true if there are no players that have more than 80 points
	std::string getWinner();				//returns the winner(s) of the game
	void clearGame();//clears all the contents in the current game (called when game is completed)
	void reSeedDeck();	//creates a new deck for each new instance of the game
	std::vector<int> getDiscards() const;//vector that contains the number of discards of each player
	std::vector<int> getHandInt() const;//vector that contains numbers that would help display the player's hand
	std::vector<int> getTableInt() const;//vector that contains numbers that would help display the table
	std::vector<int> getPlayerScore() const;//vector that contains each player's score
	void clearTable();							//clears table after each round
	bool validCardPlay(int, int);//determines if the user is playing a card that is valid
	void addNextPlayer();				//moves to the next player in the game
	void setPlayerScore();							//sets the player's score
	int getCurrentPlayerNum() const;		//gets the current player's number
	void rageQuit();//converts a player to a computer (all points, scores, hand, discards will be transferred)
	std::vector<int> getValidIndex() const;	//returns the valid card indexs in the hand
	void setHard();										//sets the game to hard
private:
	std::vector<Player*> players;							//vector of players
	std::vector<int> tempScore;	//vector of the points earned by each player for the current round
	Deck d;												//creates a deck
	Table t;												//creates a table
	int seed;												//holds the seed 
	int nextPlayer;							//holds the current player's number
	int temp;			//holds the player's number that will play the last card
	std::vector<int> discards;			//vector of number of discarded cards
	std::vector<int> handInt;//vector of numbers that will be used to display the player's hand
	std::vector<int> tableInt;//vector of numbers that will be used to display the cards on the table
	std::vector<int> playerScore;					//vector of player's score
	bool hard;
};

#endif
