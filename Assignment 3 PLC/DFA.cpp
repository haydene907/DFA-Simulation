#include "DFA.h"
#include <vector>
#include <string>
#include "State.h"
#include <iostream>
using namespace std;

// Creates a new state, manages it in the stateList
void DFA::addState(int num) {
	State* newState = new State(num);
	if (stateList.size() == 0) {
		head = newState;
		newState->startingState = true;
	}
	stateList.emplace_back(newState);
}

//Searches list of states for the names of the start and end states
//If matches found, transition and condition is added to start state
void DFA::addTransition(int startNum, int endNum, char condition) {
	State* start = nullptr;
	State* end = nullptr;
	string startName = 'q' + (std::to_string(startNum));
	string endName = 'q' + (std::to_string(endNum));
	for (int i = 0; i < stateList.size(); i++) {
		if (stateList[i]->returnName() == startName)
			start = stateList[i];
		if (stateList[i]->returnName() == endName)
			end = stateList[i];
	}
	if ((start != nullptr) && (end != nullptr))
		start->createLink(end, condition);
}

//returns start state pointer
State* DFA::retState(int num) {
	return stateList[num];
}

//makes an already created state into an accepting state.
void DFA::makeAccepting(int n) {
	stateList[n]->acceptingState = true;
}

void DFA::printTree() {
	for (int i = 0; i < stateList.size(); i++) {
		if (stateList[i]->startingState)
			cout << "SS";
		if (stateList[i]->acceptingState)
			cout << "AS";
		cout << stateList[i]->returnName() << endl;
	}
}