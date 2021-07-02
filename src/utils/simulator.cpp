#include "simulator.h"


void Simulator::allocateBuffer() {
    if (grids != nullptr) {
        for(int i = 0; i < bufferSize; i++) {
            if (grids[i] != nullptr) {
                delete grids[i];
                grids[i] = nullptr;
            }
        }
        delete[] grids;
        grids = nullptr;
    }
    grids = new Grid*[bufferSize];
    for(int i = 0; i < bufferSize; i++) grids[i] = nullptr;
}

void Simulator::setAutomata(Automata *automata) {
    this->automata = automata;
}

Automata* Simulator::getAutomata() const {
    return this->automata;
}

Simulator::Simulator(Automata* a, int buf): automata(a), bufferSize(buf), maxID(0) {
    allocateBuffer();
}

Simulator::Simulator(Automata* a, Grid& startG, int buf): automata(a),  bufferSize(buf), startGrid(&startG), maxID(0){
    allocateBuffer();
    grids[0] = new Grid(startG);
}

void Simulator::setStartGrid(Grid *g) {
    if (startGrid != nullptr) {
        delete startGrid;
        startGrid = nullptr;
    }

    startGrid = g;
    reset();
}
void Simulator::run(int nbSteps) {
    for(int i = 0; i < nbSteps; i++) next();
}

void Simulator::next() {
    if(startGrid == nullptr)
        return;
    try {
        currentGridID++;
        if(currentGridID > maxID) maxID = currentGridID;

        if (grids[currentGridID % bufferSize]) {
            delete grids[currentGridID % bufferSize];
            grids[currentGridID % bufferSize] = nullptr;
        }
        grids[currentGridID % bufferSize] = automata->applyTransition(grids[(currentGridID - 1) % bufferSize]);
    }  catch (TransitionException e) {
        currentGridID --;
        throw;
    }
}

void Simulator::reset() {
    if (startGrid == nullptr) throw "start grid is not defined";
    currentGridID = 0;
    maxID = 0;
    if (grids[0]) {
        delete grids[0];
        grids[0] = nullptr;
    }
    grids[0] = new Grid(*startGrid);
}


Simulator::~Simulator() {
    for(int i = 0; i < bufferSize; i++) {
        delete grids[i];
        grids[i] = nullptr;
    }
    delete[] grids;
    grids = nullptr;
}


Simulator::Iterator Simulator::getIterator() {
    return Iterator(this);
}

int Simulator::getBufferSize() const{
    return bufferSize;
}

void Simulator::setBufferSize(int size){
    bufferSize = size;
}

int Simulator::getCurrentGridID() const {
    return this->currentGridID;
}


///-------------------------------------------------------------------
/// Classe Simulator::Iterator
///-------------------------------------------------------------------

Simulator::Iterator::Iterator() {

}

Simulator::Iterator::Iterator(Simulator* s): sim(s), gridID(s->currentGridID % s->getBufferSize()) {

}

bool Simulator::Iterator::isDone() const {
    return sim == nullptr || gridID == -1 || (sim->currentGridID <= sim->maxID-sim->bufferSize);
}

void Simulator::Iterator::nextGrid() {
    //if(isDone()) throw "Issue : next on a finite iterator!";
    gridID = (gridID+1) % sim->getBufferSize();
}

void Simulator::Iterator::previousGrid() {
    if(isDone()) throw "Issue : previous on a finite iteraror !";
    sim->currentGridID--;
    gridID = (gridID-1 + sim->getBufferSize()) % (sim->getBufferSize());
}

Grid* Simulator::Iterator::current() const {
    //if(isDone()) throw "Issue : current on finite iteraror !";
    return sim->grids[gridID];
}
