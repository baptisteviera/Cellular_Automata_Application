#ifndef GRID_FACTORY_H
#define GRID_FACTORY_H

#include "grid.h"
#include "automata.h"
#include "helpers.h"

enum GridType {
    EMPTY,
    RANDOM
};

/**
 * @brief The GridFactory class implémentation du design pattern fabrique pour générer des pavages
 */
class GridFactory {
  public:
    GridFactory();
    /**
     * @brief generateGrid génère un pavage à utiliser par un simulateur
     * @param type discrimine les grilles vides et les grilles déterminées aléatoirement
     * @param width largeur de la grille
     * @param height hauteur de la grille
     * @param automata automate utilisant la grille générée
     * @return retourne un pavage
     */
    Grid* generateGrid(GridType type, int width, int height, Automata* automata) const;
};

#endif // GRID_FACTORY_H
