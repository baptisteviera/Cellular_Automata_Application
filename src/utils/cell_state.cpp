#include "cell_state.h"

void CellState::setId(int i) {
    this->id = i;
}
void CellState::setLabel(std::string s) {
    this->label = s;
}

void CellState::setColor(QColor c) {
    this->col = c;
}
int CellState::getId() const {
    return this->id;
}

QColor CellState::getColor() const {
    return this->col;
}
std::string CellState::getLabel() const {
    return this->label;
}


/*
direction CellStateDirection::getDirection() const {
    return this->dir;
}

void CellStateDirection::setDirection(direction d) {
    this->dir = d;
}
*/
