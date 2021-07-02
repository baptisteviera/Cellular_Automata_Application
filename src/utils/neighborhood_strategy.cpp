//
// Created by Téva Ducoté on 23/04/2021.
//

#include "neighborhood_strategy.h"
#include <cmath>

VonNeumannNeighborhood::VonNeumannNeighborhood(): NeighborhoodStrategy("Von Neumann Neighborhood") {
    neighbors = new Cell* [nbNeighbors];
}


Cell** VonNeumannNeighborhood::getNeighbors(Cell* c, Grid* g) {
    int n = 0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY() + 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if((abs(k - c->getX()) + abs(l - c->getY())) == 1) {
                neighbors[n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighbors;
}

VonNeumannNeighborhoodGeneralized::VonNeumannNeighborhoodGeneralized(std::string name, int radius): NeighborhoodStrategy(name) {
    this->radius = radius;
    this->nbNeighbors = this->radius * this->radius + (this->radius + 1) * ((this->radius + 1)) - 1 ;
    neighbors = new Cell* [nbNeighbors];
}


Cell** VonNeumannNeighborhoodGeneralized::getNeighbors(Cell* c, Grid* g) {
    int n = 0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY() + 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if( (abs(k - c->getX()) + abs(l - c->getY())) <= radius) {
                neighbors[n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighbors;
}

MooreNeighborhood::MooreNeighborhood(): NeighborhoodStrategy("Moore Neighborhood") {
    neighbors = new Cell* [nbNeighbors];
}

Cell** MooreNeighborhood::getNeighbors(Cell* c, Grid* g) {
    int n = 0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY() + 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if(x != c->getX() || y != c->getY()) {
                neighbors[n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighbors;
}

MooreNeighborhoodGeneralized::MooreNeighborhoodGeneralized(std::string name, int radius): NeighborhoodStrategy(name) {
    this->radius = radius;
    this->nbNeighbors = (2 * this->radius + 1) * (2 * this->radius + 1) - 1;
    neighbors = new Cell* [nbNeighbors];
}

Cell** MooreNeighborhoodGeneralized::getNeighbors(Cell* c, Grid* g) {
    int n = 0;
    for (int k = c->getX() - radius; k <= c->getX() + radius; k++) {
        for (int l = c->getY() - radius; l <= c->getY() + radius; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if(x != c->getX() || y != c->getY()) {
                neighbors[n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighbors;
}

//dx = [3 -3 2 2] : transmis par frontend
//dy = [2 2 -3 3] : transmis par frontend
//nbvoisin
//        getX + dx[i], getY + dy[i]


ArbitraryNeighborhood::ArbitraryNeighborhood(int nbNeighbors, int* dx,  int* dy, std::string na): NeighborhoodStrategy(na), dx(dx), dy(dy) {
    this->nbNeighbors = nbNeighbors;
    neighbors = new Cell* [nbNeighbors];
}

//dx et dy tableaux contenant le décalage par rapport à une cellule
Cell** ArbitraryNeighborhood::getNeighbors(Cell* c, Grid* g) {
    int n = 0;
    while(n < nbNeighbors) {
        //coordonnée cellule voisine
        int x = (c->getX() + dx[n] + g->getHeight()) % g->getHeight();
        int y = (c->getY() + dy[n] + g->getWidth()) % g->getWidth();
        neighbors[n] = g->getCell(x, y);
        n++;
    }
    return neighbors;
}
