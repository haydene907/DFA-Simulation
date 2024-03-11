#include <vector>
#include <string>
using namespace std;

#pragma once
//Essentially a spanning tree. Intention is to transition to new state only when
//condition is met.
class State
{
private:
	string name;
public:
	bool acceptingState;
	bool startingState;
	State(int num);
	void createLink(State* newState, char condition);
	string returnName();
	vector<State*> transitions;
	vector<char> conditions;
};

