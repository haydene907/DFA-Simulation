#include <iostream>
#include <string>
#include "State.h"
#include "DFA.h"
using namespace std;

string alphabet; //global variable alphabet allows access for compatibility checks everywhere

bool inAlphabet(string test, string control) {
    for (int i = 0; i < test.size(); i++) {
        if ((test[i] != control[0]) && (test[i] != control[1]))
            return false;
    }
    return true;
}

//recursive function that iterates through every state once and counts it
//used in allStatesConnected() because having a vector with visited states outside function
//scope is essential for correct operation of function
//If implemented anywhere else, create pointer to vector of pointers to State objects
int dfs(vector<State*>* visited, State* state) {
    int count = 1;
    visited->emplace_back(state);
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

//NOTE:Make sure to create pointer to vector of state pointers before call, delete after
//Prints all transitions for every state in the DFA
void printTransitions(State* state, vector<State*>* visited) {
    visited->emplace_back(state);
    for (int i = 0; i < state->transitions.size(); i++) {
        bool inVisited = false;
        State* stateLookahead = state->transitions[i];
        cout << state->returnName() << "->" << stateLookahead->returnName() << " ";
        cout << "if " << state->conditions[i] << endl;
        //iterates through visited vector and ensures next node to be counted hasnt been visited
        for (int j = 0; j < visited->size(); j++) {
            if (visited->at(j)->returnName() == stateLookahead->returnName())
                inVisited = true;
        }
        if (!inVisited)
            printTransitions(stateLookahead, visited);
    }
}

//take string, iterate through transitioning states for each character.
//if last character transitions to an accepting state, then input is accepted
void dfaTraversal(DFA* dfa) {
    string userInp = "";

    
    while (userInp != "q") {
        bool accepted = false;
        State* state = dfa->head;
        cout << "Enter an input string and see if it is accepted(q to quit): ";
        cin >> userInp;

        if (userInp == "q")
            break;

        //iterates through user input
        for (int i = 0; i < userInp.size(); i++) {
            bool transitionFound = false;
            
            //quick check for alphabet compatibility, done here so
            //new input can be retrieved
            if (!inAlphabet(userInp, alphabet)) {
                cout << "User string not in alphabet, try again." << endl;
                break;
            }

            //iterates through conditions list for current state,
            //if match found between user input and availiable transitions
            //transition is taken, next piece of user input is examined in new state
            for (int j = 0; j < state->conditions.size(); j++) {
                if (state->conditions[j] == userInp[i]) {
                    state = state->transitions[j];
                    transitionFound = true;
                }
            }
            if (!transitionFound)
                break;

            //if end of user input has been reached and the current state is an
            //accepting state then the input string is accepted.
            if ((i == (userInp.size() - 1)) && (state->acceptingState))
                accepted = true;
        }
        if (accepted)
            cout << "Input accepted!" << endl;
        else
            cout << "Input not accepted." << endl;
    }
    userInp.clear();
}

//TODO: Verify DFA works, test DFA with input. determine initial state and accepting states
int main()
{
    int numStates = 0;
    int numAcceptingStates = 0;
    DFA dfa;
    vector<int> numTransitions;
    while ((alphabet.size() < 1) || (alphabet.size() > 2)) {
        cout << "Enter a set of characters to use for your DFA alphabet (limit to 2, do not seperate, q is reserved): ";
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
            char condition;
            cout << "Enter transition destination " << j + 1 << " for " << dfa.retState(i)->returnName() << "(state number): ";
            cin >> toState;
            cout << "Enter condition for transition: ";
            cin >> condition;
            string test(1, condition);
            if (inAlphabet(test, alphabet))
                dfa.addTransition(i, toState, condition);
            else {
                cout << "Transition not in alphabet, process aborted." << endl;
                return 1;
            }
        }
    }

    while ((numAcceptingStates < 1) || (numAcceptingStates > numStates)) {
        cout << "Enter the number of accepting states: ";
        cin >> numAcceptingStates;
    }
    
    for (int i = 0; i < numAcceptingStates; i++) {
        int acceptingState;
        cout << "Enter state number of accepting state " << (i + 1) << ": ";
        cin >> acceptingState;
        dfa.makeAccepting(acceptingState);
    }
    
    if (allStatesConnected(dfa.retState(0), numStates)) {
        cout << "DFA Successfully Created!!!" << endl;
    }

    cout << "States (SS = Starting State, AS = Accepting State):" << endl;
    dfa.printTree();

    cout << "Current Transitions:" << endl;
    vector<State*>* visited = new vector<State*>;
    printTransitions(dfa.retState(0), visited);
    visited->clear();
    delete visited;

    if (allStatesConnected(dfa.retState(0), numStates))
        dfaTraversal(&dfa);


    return 0;
}

