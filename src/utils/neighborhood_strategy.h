//
// Created by Téva Ducoté on 23/04/2021.
//

#ifndef LO21_NEIGHBORHOODSTRATEGY_H
#define LO21_NEIGHBORHOODSTRATEGY_H

#include <iostream>
#include<utility>
#include "cell.h"
#include "grid.h"
#include "cell_state.h"
/**
 * @brief NeighborhoodStrategy classe abstraite permettant de déléguer les différents types de voisinages
 */
class NeighborhoodStrategy {
    /**
     * @brief name nom du voisinage
     */
    std::string name;
  public:
    /**
     * @brief NeighborhoodStrategy Constructeur de la classe NeighborhoodStrategy
     * @param na nom donné au voisinage
     */
    NeighborhoodStrategy(std::string na): name(na) {}
    /**
     * @brief getNeighbors  méthode virtuelle pure dont le comportement est définies dans les classes filles
     * @param c cellule dont on souhaite connaître les voisins
     * @param g grille sur laquelle étudier les voisins
     * @return Cell** tableau de pointeurs des cellules voisines
     */
    virtual Cell** getNeighbors(Cell* c, Grid* g) = 0;
    /**
     * @brief getNbNeighbors méthode virtuelle pure renvoyant le nombre de voisins
     * @return int le nombre de voisins
     */
    virtual int getNbNeighbors() const = 0 ;
    /**
     * @brief getName méthode renvoyant le nom du voisinage
     * @return string nom du voisinage
     */
    std::string getName() const  {
        return name;
    }
};
/**
 * @brief Voisinage de VonNeumann héritant de la stratégie de voisinage
 */
class VonNeumannNeighborhood: public NeighborhoodStrategy {
    /**
     * @brief neighbors Tableau des voisins
     */
    Cell** neighbors;
    /**
     * @brief nbNeighbors Nombre de voisins
     */
    int nbNeighbors = 4;

  public:
    /**
     * @brief VonNeumannNeighborhood Constructeur du voisinage de VonNeumann
     */
    VonNeumannNeighborhood();
    /**
     * @brief ~VonNeumannNeighborhood Destructeur du voisinage de VonNeumann
     */
    ~VonNeumannNeighborhood() {
        delete[] neighbors;
    }
    /**
     * @brief getNbNeighbors Méthode renvoyant le nombre de voisins
     * @return int Nombre de voisins
     */
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    /**
     * @brief getNeighbors Méthode renvoyant les cellules voisines d'une cellule
     * @param c Cellule dont on veut connaître les voisins
     * @param g Grille sur laquelle étudier le voisinage
     * @return Cell* Tableau de pointeur des cellules voisines
     */
    virtual Cell** getNeighbors(Cell* c, Grid* g);
};

/**
 * @brief Voisinage de VonNeumann généralisé héritant de la stratégie de voisinage
 */
class VonNeumannNeighborhoodGeneralized: public NeighborhoodStrategy {
    /**
     * @brief neighbors Tableau de pointeur sur les cellules voisines
     */
    Cell** neighbors;
    /**
     * @brief radius Rayon du voisinage
     */
    int radius;
    /**
     * @brief nbNeighbors Nombre de voisins
     */
    int nbNeighbors;
    /**
     * @brief name Nom du voisinage
     */
    std::string name = "Von Neumann Neighborhood Generalized";
  public:
    /**
     * @brief VonNeumannNeighborhoodGeneralized Constructeur de voisinage de VonNeumann généralisé
     * @param name nom du voisinage
     * @param radius raton du voisinage (1 par défaut)
     */
    VonNeumannNeighborhoodGeneralized(std::string name = "Von Neumann Neighborhood Generalized", int radius = 1);
    /**
     * @brief Destructeur du voisinage de VonNeumann généralisé
     */
    ~VonNeumannNeighborhoodGeneralized() {
        delete[] neighbors;
    }
    /**
     * @brief getNbNeighbors Méthode renvoyant le nombre de voisins
     * @return int Nombre de voisins
     */
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    /**
     * @brief getRadius Accesseur en lecture du rayon
     * @return  int Rayon
     */
    int getRadius() const {return radius;}
    /**
     * @brief getNeighbors Méthode renvoyant les voisins d'une cellule
     * @param c Cellule dont on souhaite connaître ses voisins
     * @param g Grille sur laquelle étudier le voisinage
     * @return Cell** Tableau de pointeur sur les cellules voisines
     */
    virtual Cell** getNeighbors(Cell* c, Grid* g);
};
/**
 * @brief Voisinage de Moore héritant de la stratégie de voisinage
 */
class MooreNeighborhood: public NeighborhoodStrategy {
    /**
     * @brief neighbors Tableau de pointeur sur les cellules voisines
     */
    Cell** neighbors;
    /**
     * @brief nbNeighbors Nombre de voisins (8 pour cette classe)
     */
    int nbNeighbors = 8;
  public:
    /**
     * @brief MooreNeighborhood Constructeur du voisinage de Moore
     */
    MooreNeighborhood();
    /**
     * @brief ~MooreNeighborhood Destructeur du voisinage de Moore
     */
    ~MooreNeighborhood() {
        delete[] neighbors;
    }
    /**
     * @brief getNbNeighbors Méthode renvoyant le nombre de voisins
     * @return
     */
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    /**
     * @brief getNeighbors Méthode renvoyant les voisins d'une cellule
     * @param c Cellule dont on souhaite connaître ses voisins
     * @param g Grille sur laquelle étudier le voisinage
     * @return Cell** Tableau de pointeur sur les cellules voisines
     */
    virtual Cell** getNeighbors(Cell* c, Grid* g);
};

/**
 * @brief Voisinage de Moore généralisé héritant de la stratégie de voisinage
 */
class MooreNeighborhoodGeneralized: public NeighborhoodStrategy {
    /**
     * @brief neighbors Tableau de pointeur sur les cellules voisines
     */
    Cell** neighbors;
    /**
     * @brief radius Rayon du voisinage
     */
    int radius;
    /**
     * @brief nbNeighbors Nombre de voisins
     */
    int nbNeighbors;
  public:
    /**
     * @brief MooreNeighborhoodGeneralized Constructeur du voisinage de Moore généralisé
     * @param name Nom du voisinage
     * @param radius Rayon (par défaut 1)
     */
    MooreNeighborhoodGeneralized(std::string name="Moore Neighborhood Generalized", int radius = 1);
    /**
     * @brief ~MooreNeighborhoodGeneralized Destructeur du voisinage de Moore généralisé
     */
    ~MooreNeighborhoodGeneralized() {
        delete[] neighbors;
    }
    /**
     * @brief getNbNeighbors Méthode renvoyant le nombre de voisins
     * @return int Nombre de voisins
     */
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    /**
     * @brief getRadius Accesseur en lecture du rayon
     * @return int Rayon
     */
    int getRadius() const {return radius;}
    /**
     * @brief getNeighbors Méthode renvoyant les voisins d'une cellule
     * @param c Cellule dont on souhaite connaître ses voisins
     * @param g Grille sur laquelle étudier le voisinage
     * @return Cell** Tableau de pointeur sur les cellules voisines
     */
    virtual Cell** getNeighbors(Cell* c, Grid* g);
};

class ArbitraryNeighborhood: public NeighborhoodStrategy {
    /**
     * @brief neighbors Tableau de pointeur des cellules voisines
     */
    Cell** neighbors;
    /**
     * @brief nbNeighbors Nombre de voisins
     */
    int nbNeighbors;
    /**
     * @brief dx Tableau des coordonnées relatives (x) des voisins à partir de la cellule
     */
    int* dx;
    /**
     * @brief dy Tableau des coordonnées relatives (y) des voisins à partir de la cellule
     */
    int* dy;
  public:
    /**
     * @brief ArbitraryNeighborhood Constructeur du voisinage arbitraire
     * @param nbNeighbors Nombre de voisins
     * @param dx Tableau des coordonnées relatives (x) des voisins à partir de la cellule
     * @param dy Tableau des coordonnées relatives (y) des voisins à partir de la cellule
     * @param na Nom du voisinage arbitraire
     */
    ArbitraryNeighborhood(int nbNeighbors, int* dx, int* dy, std::string na);
    /**
     * @brief ~Arbitraryneighborhood Destructeur de voisinage arbitraire
     */
    ~ArbitraryNeighborhood() {
        delete[] neighbors;
    }
    /**
     * @brief getNbNeighbors Méthode renvoyant le nombre de voisins
     * @return  int Nombre de voisins
     */
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    /**
     * @brief getDx Accesseur en lecture du tableau des coordonnées relative x
     * @return int* Tableau des coordonnées relatives (x) des voisins à partir de la cellule
     */
    int* getDx()const{return dx;}
    /**
     * @brief getDx Accesseur en lecture du tableau des coordonnées relative y
     * @return int* Tableau des coordonnées relatives (y) des voisins à partir de la cellule
     */
    int* getDy()const{return dy;}
    /**
     * @brief getNeighbors Méthode renvoyant les voisins d'une cellule
     * @param c Cellule dont on souhaite connaître ses voisins
     * @param g Grille sur laquelle étudier le voisinage
     * @return Cell** Tableau de pointeur sur les cellules voisines
     */
    virtual Cell** getNeighbors(Cell* c, Grid* g);
};

#endif //LO21_NEIGHBORHOODSTRATEGY_H
