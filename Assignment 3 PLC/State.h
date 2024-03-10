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
	State(int num);
	void createLink(State* newState, int condition);
	string returnName();
	vector<State*> transitions;
	vector<int> conditions;
};

