#pragma once
#include <string>
#include <vector>
#include "State.h"
using namespace std;

class DFA
{
private:
	vector<State*> stateList;
public:
	State* head;
	void addState(int num); //creates new state
	void addTransition(int startNum, int endNum, char condition); //creates transition
	State* retState(int num); //returns requested state, head is index 0
	void makeAccepting(int n);
	void printTree();
};

