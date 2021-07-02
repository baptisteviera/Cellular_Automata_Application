#include "grid_factory.h"

GridFactory::GridFactory() {}

Grid* GridFactory::generateGrid(GridType type, int width, int height, Automata* automata) const {
    Grid* grid;
    switch (type) {
        case RANDOM:
            grid = new Grid(automata->getNbStates(), automata->getAvailableStates(), width, height);
            break;
        case EMPTY:
            grid = new Grid(automata->getAvailableStates()[0], width, height);
            break;
    }
    if (instanceof<LATransition>(automata->getTransitionStrategy())) {
        grid->getCell(0, 0)->setDirection(Direction::UP);
    }
    return grid;
}
