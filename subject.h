/*
 * MVC example of GTKmm program
 *
 * Subject class.  Abstract class for Observer Pattern
 *
 * Description of class found in subject.cc
 *
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#ifndef MVC_SUBJECT_H
#define MVC_SUBJECT_H

#include <set>

class Observer;

class Subject {
public:
	void subscribe(Observer*);
	void unsubscribe(Observer*);

protected:
	void playerturn(std::string msg);
	void endRound(std::string msg, std::vector<int>, std::vector<int>);
	void updateInterface(std::vector<int>, std::vector<int>, std::vector<int>,
			std::vector<int>);
	void notifyTableClear();
	void endGame(std::string);
private:
	typedef std::set<Observer*> Observers;
	Observers observers_;
};
// Subject

#endif
