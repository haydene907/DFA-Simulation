#include "State.h"
#include <string>

State::State(int num) {
	name = 'q' + (std::to_string(num));
	acceptingState = false;
	startingState = false;
}
void State::createLink(State* newstate, char condition) {
	transitions.emplace_back(newstate);
	conditions.emplace_back(condition);
}



string State::returnName() {
	return name;
}