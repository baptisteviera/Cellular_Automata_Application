#include <string>
#include "automata.h"
using namespace std;

Automata::Automata(CellState** availableStates, TransitionStrategy* transition, NeighborhoodStrategy* neighborhood, int nbStates, string name, string desc, string author, int year) {
    this->name = name;
    this->description = desc;
    this->author = author;
    this->creationYear = year;
    this->nbStates = nbStates;
    this->availableStates = new CellState*[nbStates];
    for(int i = 0; i < nbStates; i++) {
        this->availableStates[i] = availableStates[i];
    }
    this->transitionStrategy = transition;
    this->neighborStrategy = neighborhood;
}

Automata::~Automata() {
    if(availableStates != nullptr) {
        for(int i = 0; i < nbStates; i++) {
            if(availableStates[i] != nullptr) {
                delete availableStates[i];
                availableStates[i] = nullptr;
            }
        }
        delete[] availableStates;
        availableStates = nullptr;
    }
}

Grid* Automata::applyTransition(Grid* src) const {
    Grid* dst = new Grid(availableStates[0], src->getWidth(), src->getHeight());
    for(int i = 0; i < src->getHeight(); i++) {
        for(int j = 0; j < src->getWidth(); j++) {
            //Pour chaque cellule on appele la méthode calcNextCell pour la modifier en fonction de son voisinage et de la fonction de transition
            dst->setCell(transitionStrategy->calcNextCell(src->getCell(i, j),
                                                          neighborStrategy->getNeighbors(src->getCell(i, j), src),
                                                          neighborStrategy->getNbNeighbors(),
                                                          availableStates,
                                                          nbStates), i, j);
        }
    }
    return dst;
}

void Automata::setAvailableStates(CellState** availableStates, int nbStates) {
    if(this->nbStates != nbStates) {
        this->nbStates = nbStates;
        CellState** newTab = new CellState*[nbStates];
        for(int i = 0; i < nbStates; i++) newTab[i] = availableStates[i];
        CellState** old = this->availableStates;
        this->availableStates = newTab;
        delete[] old;
    }
    for(int i = 0; i < nbStates; i++) this->availableStates[i] = availableStates[i];
}

void Automata::setAvailableState(CellState* state, const int id) {
    if(id >= nbStates) throw "Error: availableStates incorrect index";
    availableStates[id] = state;

}

CellState* Automata::getAvailableState(const int id) const {
    if(id >= nbStates) throw "Error: availableStates incorrect index";
    return availableStates[id];
}
