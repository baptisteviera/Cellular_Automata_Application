#include "transition_factory.h"

using namespace std;

TransitionStrategy* TransitionFactory::production(const string ruleName) const {
    if(ruleName == "Game of Life Transition Rule") return new GOLTransition;
    if(ruleName == "Brian Brain Transition Rule") return new BBTransition;
    if(ruleName == "David Grieffath Transition") return new DGTransition;
    if(ruleName == "Langton Loop Transition") return new LLTransition;
    if(ruleName == "Langton Ant Transition") return new LATransition;

    throw "Unknown Transition";
}
