#include "State.h"
#include <string>

State::State(int num) {
	name = 'q' + (std::to_string(num));
}
void State::createLink(State* newstate, int condition) {
	transitions.emplace_back(newstate);
	conditions.emplace_back(condition);
}

string State::returnName() {
	return name;
}