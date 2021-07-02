#include "cell.h"
#include "cell_state.h"

void Cell::setState(CellState* s) {
    this->state = s;
}
CellState* Cell::getState() const {
    return this->state;
}

Cell::Cell(CellState* s, int x, int y, Direction d): state(s), x(x), y(y), dir(d) {}

Cell::Cell(const Cell& c): state(c.getState()), x(c.getX()), y(c.getY()), dir(c.getDirection()){}


int Cell::getX() const {
    return this->x;
}

int Cell::getY() const {
    return this->y;
}

Direction Cell::getDirection() const {
    return this->dir;
}

void Cell::setDirection(Direction d) {
    this->dir = d;
}

void Cell::turnRight() {
    if (this->dir != NONE) {
        this->dir = static_cast<Direction>(this->dir - 1);
        this->dir = static_cast<Direction>(1 + ((this->dir + 1) % (LEFT)));
    }
}

void Cell::turnLeft() {
    if (this->dir != NONE) {
        this->dir = static_cast<Direction>(this->dir - 1);
        this->dir = static_cast<Direction>(1 + ((this->dir - 1 + LEFT) % (LEFT)));
    }
}
