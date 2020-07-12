/*
 * Model.  Is responsible keeping track of the deck of cards.  
 * It knows nothing about views or controllers.
 * Gets all knowledge about the game from game.h 
 */

#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include <gtkmm.h>
#include "subject.h"
#include "game.h"

class Model: public Subject {
public:
	Model();

	std::string playerButton(Glib::ustring);//changes label between computer to human (before game starts)
	std::vector<bool> setPlayerTypes(std::string player_types[], int);//will determine if rage button will be enabled or disabled (checks player type)
	void reSeedDeck();			//creates new deck at the beginning of each game
	void setPlayerHand();								//sets the player's hand
	void gamePlay();											//plays the game
	bool getMaxScore();		//returns true if no players have exceed 80 points
	std::string getWinner();				//returns the winners of the game
	void clearGame();						//clears all the content of the game
	bool validCardPlay(int, int);//determines if the human has entered a valid card (via button)
	void addNextPlayer();							//moves to the next button
	int getCurrentPlayerNum() const;		//gets the player's current number
	void rageQuit();		//converts the human player into a computer player
	void setHard();								//set the flag in game to hard
private:
	Game g;	//uses the game class for all the knowledge and organization of the game's data
};
// Model

#endif
