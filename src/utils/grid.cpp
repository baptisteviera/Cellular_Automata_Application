#include "grid.h"

Grid::~Grid() {
    if (cells == nullptr) {
        return;
    }
    for(int i = 0; i < height; i++) {
        if (cells[i]) {
            for(int j = 0; j < width; j++) {
                if (cells[i][j]) {
                    delete cells[i][j];
                }
            }
            delete[] cells[i];
        }
    }
    delete[] cells;
    cells = nullptr;
}

Grid::Grid(CellState* c, int w, int h) {
    this->width = w;
    this->height = h;
    cells = new Cell** [h];
    for(int i = 0; i < h; i++) cells[i] = new Cell*[w];
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            cells[i][j] = new Cell(c, i, j);
        }
    }
}

Grid::Grid(int nbStates, CellState** availableStates, int w, int h) {
    srand(time(nullptr));
    this->width = w;
    this->height = h;
    cells = new Cell** [h];
    for(int i = 0; i < h; i++) cells[i] = new Cell*[w];
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            cells[i][j] = new Cell(availableStates[rand() % nbStates], i, j);
        }
    }
}

Grid::Grid(const Grid& g): width(g.width), height(g.height), cells(new Cell * * [g.height]) {
    for(int i = 0; i < g.height; i++) {
        this->cells[i] = new Cell*[g.width];
        for(int j = 0; j < g.width; j++) {
            this->cells[i][j] = new Cell(*g.cells[i][j]);
        }
    }

}


Grid& Grid::operator= (const Grid& g) {
    if(this != &g) {
        if (this->width != g.width) {
            this->width = g.width;
        }
        if( this->height != g.height) {
            this->height = g.height;
        }
        Cell*** newcells = new Cell** [g.height];
        for(int i = 0; i < g.height; i++) newcells[i] = new Cell*[g.width];
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                newcells[i][j] = g.cells[i][j];
            }
        }
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                delete cells[i][j];
        delete[] cells;
        this->cells = newcells;
    }
    return *this;
}

int Grid::getWidth() const {
    return this->width;
}
int Grid::getHeight() const {
    return this->height;
}

void Grid::setCell(Cell* c, int x, int y) {
    if (cells[x][y]) {
        delete this->cells[x][y];
    }
    this->cells[x][y] = c;
}

Cell* Grid::getCell(int x, int y) const {
    return this->cells[x][y];
}

void Grid::setName(std::string name) {
    this->name = name;
}

std::string Grid::getName() const{
    return this->name;
}
