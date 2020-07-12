/*
 * MVC example of GTKmm program
 *
 * Subject class.  Abstract class for Observer Pattern
 *
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */

#include <set>
#include "subject.h"
#include "observer.h"

using namespace std;

//subject and observer relationship
void Subject::subscribe(Observer *newView) {
	observers_.insert(newView);
}

void Subject::unsubscribe(Observer *formerView) {
	observers_.erase(formerView);
}

//asks view to create a popup to tell what player goes first in the current round
void Subject::playerturn(string msg) {
	Observers::iterator i;
	for (i = observers_.begin(); i != observers_.end(); ++i)
		(*i)->update(msg);

}

//asks view to create a popup to output the end of round scores
void Subject::endRound(string msg, vector<int> d, vector<int> s) {
	Observers::iterator i;
	for (i = observers_.begin(); i != observers_.end(); ++i)
		(*i)->endRound(msg, d, s);

}

//update the table, discards, and player's hand for the human player's turn
void Subject::updateInterface(vector<int> discard, vector<int> hand,
		vector<int> table, vector<int> legalIndex) {
	Observers::iterator i;
	for (i = observers_.begin(); i != observers_.end(); ++i)
		(*i)->updateInterface(discard, hand, table, legalIndex);

}

//notifies the view to clear the table and hand to null cards (back side of cards)
void Subject::notifyTableClear() {
	Observers::iterator i;
	for (i = observers_.begin(); i != observers_.end(); ++i)
		(*i)->notifyTableClear();
}

//tells view to end the game (clear all cards to null, and reset all labels, buttons)
void Subject::endGame(string msg) {
	Observers::iterator i;
	for (i = observers_.begin(); i != observers_.end(); ++i)
		(*i)->endGame(msg);
}
