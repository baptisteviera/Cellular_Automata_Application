#ifndef NEIGHBORHOOD_FACTORY_H
#define NEIGHBORHOOD_FACTORY_H
#include "neighborhood_strategy.h"
#include <string>

using namespace std;

/**
 * @brief Fabrique de voisinnage
 */
class NeighborhoodFactory {

public:
    /**
     * @brief production Méthode de fabrication d'un voisinage
     * @param name nom du voisinage à fabriquer
     * @return NeighborhoodStrategy* un pointeur sur une classe de voisinage
     */
    NeighborhoodStrategy* production(const string name) const;
    /**
     * @brief production Méthode de fabrication d'un voisinage
     * @param name nom du voisinage à fabriquer
     * @param radius rayon du voisinage
     * @return NeighborhoodStrategy* un pointeur sur une classe de voisinage
     */
    NeighborhoodStrategy* production(const string name, const int radius) const;
    /**
     * @brief production Méthode de fabrication d'un voisinage
     * @param name nom du voisinage à fabriquer
     * @param nbVoisins nombre de voisins
     * @param dx tableau des coordonnées relatives (x) des voisins à partir de la cellule
     * @param dy tableau des coordonnées relatives (y) des voisins à partir de la cellule
     * @return NeighborhoodStrategy* un pointeur sur une classe de voisinage
     */
    NeighborhoodStrategy* production(const string name, const int nbVoisins, int* dx, int* dy) const;

};

#endif // NEIGHBORHOOD_FACTORY_H
