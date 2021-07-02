#include "automata.h"
#include "automata_manager.h"

using namespace std;

AutomataManager* AutomataManager::instance = nullptr;

AutomataManager::AutomataManager() {
    automatas = new Automata*[nbMaxAutomatas];
    for(int i = 0; i < nbMaxAutomatas; i++) automatas[i] = nullptr;
    nbAutomatas = 0;
}

AutomataManager::~AutomataManager() {
    if(automatas != nullptr) {
        for(int i = 0; i < nbMaxAutomatas; i++) {
            if(automatas[i] != nullptr) {
                delete automatas[i];
                automatas[i] = nullptr;
            }
        }
        delete[] automatas;
        automatas = nullptr;
    }
    nbAutomatas = 0;
}

AutomataManager* AutomataManager::getAutomataManager() {
    if(!instance) instance = new AutomataManager();
    return instance;
}

void AutomataManager::destroyAutomataManager() {
    delete instance;
    instance = nullptr;
}
Automata* AutomataManager::getAutomata(int id) const {
    if(id > nbMaxAutomatas) throw "Error: Automaton incorrect index";
    if(automatas[id] == nullptr) throw "Error: Undefined automaton";
    return automatas[id];
}

//Modification d'un automate à un indice donné
void AutomataManager::changeAutomata(int id, CellState** availableStates, TransitionStrategy* transition, NeighborhoodStrategy* neighborhood, int nbStates, string name, string desc, string author, int year)
{
    if(id >= nbAutomatas) throw "Error: Automaton incorrect index";
    delete automatas[id];
    automatas[id] = new Automata(availableStates, transition, neighborhood, nbStates, name, desc, author, year);
}

//Ajout d'un automate à la fin du tableau d'automates
void AutomataManager::addAutomata(CellState** availableStates, TransitionStrategy* transition, NeighborhoodStrategy* neighborhood, int nbStates, string name, string desc, string author, int year) {
    if(nbAutomatas >= nbMaxAutomatas) throw "Error : can't be added because the automaton table is full";
    automatas[nbAutomatas] = new Automata(availableStates, transition, neighborhood, nbStates, name, desc, author, year);
    nbAutomatas++;
}

//Supression d'un automate à un indice donné, réajustement tableau pour éviter les trous
void AutomataManager::removeAutomata(int id) {
    if(id >= nbAutomatas) throw "Error: Automaton incorrect index";
    if (automatas[id]) {
        delete automatas[id];
        automatas[id] = nullptr;
    }
    //On décale les automates pour combler la supression
    while(id < nbAutomatas - 1) {
        automatas[id] = automatas[id + 1];
        id++;
    }
    if (automatas[id]) {
        delete automatas[id];
        automatas[id] = nullptr;
    }
    nbAutomatas--;
}

void AutomataManager::clear() {
    for (int i = nbAutomatas - 1; i >= 0; i --) {
        removeAutomata(i);
    }
    nbAutomatas = 0;
}
