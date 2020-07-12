/*
 * Observer class.  Abstract class for Observer Pattern
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
public:
	virtual void update(std::string msg) = 0;
	virtual void endRound(std::string msg, std::vector<int>,
			std::vector<int>) = 0;
	virtual void updateInterface(std::vector<int>, std::vector<int>,
			std::vector<int>, std::vector<int>) = 0;
	virtual void notifyTableClear() = 0;
	virtual void endGame(std::string) = 0;
};

#endif
