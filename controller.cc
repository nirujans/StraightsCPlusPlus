/*
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 */

#include <gtkmm.h>
#include "controller.h"
#include "model.h"

using namespace std;

Controller::Controller(Model *m) : model_(m) {}	//constructor (create the model that the controller will be linked to)

//calls model to prepare to start the game (create deck, create table, distribute hand, find out which player ends last etc)
vector <bool> Controller::startButtonClicked(string player_types[], int s) {
     vector <bool> rage = model_->setPlayerTypes(player_types, s);
     return rage;
} 

//calls model to allow the button to toggle between human and computer players (before starting the game)
string Controller::playerButtonClicked(Glib::ustring playerLabel) {
	return (model_->playerButton(playerLabel));
} 

//calls model to distribute the hand to the 4 players
void Controller::setPlayerHand(){
	model_->setPlayerHand();
}

//calls model to start the new deck for starting a brand new game
void Controller::reSeedDeck(){
	model_->reSeedDeck();
}

//calls model function to play the current game
void Controller::gamePlay(){
	model_->gamePlay();
}

//calls model to determine if any player has not reached more than 80 points
bool Controller::getMaxScore(){
	return (model_->getMaxScore());
}

//calls model to get the winner of the game
string Controller::getWinner(){
	return (model_->getWinner());
}

//asks model to clear all content in the current game 
void Controller::clearGame(){
	model_->clearGame();
}

//calls model to determine if the player's request for playing a card is a valid move
bool Controller::validCardPlay(int cardNum,int cardButton){
	return model_->validCardPlay(cardNum,cardButton);
}

//calls model to move to the next player
void Controller::addNextPlayer(){
	model_->addNextPlayer();
}

//calls model to get the current players number
int Controller::getCurrentPlayerNum() const {
	return model_->getCurrentPlayerNum();
}

//calls model function to request a ragequit from player
void Controller::rageQuit(){		
	model_->rageQuit();
}
