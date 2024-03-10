#include <iostream>
#include <string>
#include "State.h"
#include "DFA.h"
using namespace std;

//recursive function that iterates through every state once and counts it
//used in allStatesConnected() because having a vector with visited states outside function
//scope is essential for correct operation of function
//If implemented anywhere else, create pointer to vector of pointers to State objects
int dfs(vector<State*>* visited, State* state) {
    int count = 1;
    //iterates through current nodes transitions recursively counts the number of nodes
    for (int i = 0; i < state->transitions.size(); i++) {
        bool inVisited = false;
        State* stateLookahead = state->transitions[i];
        //iterates through visited vector and ensures next node to be counted hasnt been visited
        for (int j = 0; j < visited->size(); j++) {
            if (visited->at(j)->returnName() == stateLookahead->returnName())
                inVisited = true;
        }
        if (!inVisited)
            count += dfs(visited, stateLookahead);
    }
    return count;
}

//visit each node traversing only from transitions, increment value for each visited
//upon each visit add state to visited list, so they arent visited again
//this will verify every state has a transition to it.
bool allStatesConnected(State* state, int numStates) {
    vector<State*>* visited = new vector<State*>;
    int count = dfs(visited, state);
    visited->clear();
    delete visited;
    if (count == numStates)
        return true;
    else
        return false;
}

//create pointer to vector of state pointers before call, delete after

//TODO: print all the transitions for state examined
void printTree(State* state, vector<State*>* visited) {
    for (int i = 0; i < state->transitions.size(); i++) {
        bool inVisited = false;
        State* stateLookahead = state->transitions[i];
        cout << state->returnName() << "->" << stateLookahead->returnName() << " ";
        //iterates through visited vector and ensures next node to be counted hasnt been visited
        for (int j = 0; j < visited->size(); j++) {
            if (visited->at(j)->returnName() == stateLookahead->returnName())
                inVisited = true;
        }
        if (!inVisited)
            printTree(stateLookahead, visited);
    }
}

//TODO: Verify DFA is DFA, test DFA with input

int main()
{
    string alphabet;
    int numStates = 0;
    DFA dfa;
    vector<int> numTransitions;
    while ((alphabet.size() < 1) || (alphabet.size() > 2)) {
        cout << "Enter a set of characters to use for your DFA alphabet (limit to 2, do not seperate): ";
        cin >> alphabet;
    }

    while ((numStates < 1) || (numStates > 5)) {
        cout << "Enter the number of states for the DFA(1-5): ";
        cin >> numStates;
    }

    for (int i = 0; i < numStates; i++) {
        int transitions;
        dfa.addState(i);
        cout << "Enter number of transitions for " << dfa.retState(i)->returnName() << ": ";
        cin >> transitions;
        numTransitions.emplace_back(transitions);
    }

    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numTransitions[i]; j++) {
            int toState;
            int condition;
            cout << "Enter transition destination " << j + 1 << " for " << dfa.retState(i)->returnName() << "(state number): ";
            cin >> toState;
            cout << "Enter condition for transition: ";
            cin >> condition;
            dfa.addTransition(i, toState, condition);
        }
    }
    
    if (allStatesConnected(dfa.retState(0), numStates)) {
        cout << "DFA Successfully Created!!!" << endl;
    }

    cout << "Current Transitions:" << endl;
    vector<State*>* visited = new vector<State*>;
    printTree(dfa.retState(0), visited);
    visited->clear();
    delete visited;

}

