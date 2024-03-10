#pragma once
#include <string>
#include <vector>
#include "State.h"
using namespace std;

class DFA
{
private:
	vector<State*> stateList;
	State* head;
public:
	void addState(int num); //creates new state
	void addTransition(int startNum, int endNum, int condition); //creates transition
	State* retState(int num); //returns requested state, head is index 0
};

