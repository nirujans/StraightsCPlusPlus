#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include <gtkmm.h>

class Model;

class Controller {
public:
	Controller(Model*);											//construtor
	std::vector<bool> startButtonClicked(std::string player_types[], int);//asks model to distribute the hand, incorportate seed, set the table, deck and hand of players (prepare for start of game)
	std::string playerButtonClicked(Glib::ustring);	//asks model to allow toggling the button to switch between computer and human player (before game starts)
	void setPlayerHand();		//asks model to distribute the deck to players
	void reSeedDeck();		//asks model to reset Deck for each new game played
	void gamePlay();							//asks model to play the game
	bool getMaxScore();	//asks model if any player has not gone over 80 points
	std::string getWinner();	//asks model to return the winner of the game
	void clearGame();					//asks model to clear the game content
	bool validCardPlay(int, int);//ask model if the given card is a valid card to play
	void addNextPlayer();		//will ask the model to move to the next player
	int getCurrentPlayerNum() const;//ask model for the current player's number
	void rageQuit();			//controls a ragequit request from human player
private:
	Model *model_;												//Model
};
// Controller

#endif

