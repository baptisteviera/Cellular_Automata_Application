
#ifndef LO21_GRID_H
#define LO21_GRID_H
#include "cell_state.h"
#include "cell.h"
#include <cstdlib>
#include <ctime>

/**
 * @brief Classe représentant une grille de cellule, une configuration à un instant T
 */
class Grid {
  private:
    /**
     * @brief width la largeur de la grille
     */
    int width;
    /**
     * @brief height la hauteur de la grille
     */
    int height;
    /**
     * @brief cells tableau à deux dimensions de pointeur de cellule (initialement null)
     */
    Cell*** cells = nullptr;
    /**
     * @brief name nom de la grille, pour stocker dans la base de donnees
     */
    std::string name = "";

  public:
    /**
     * @brief Grid Constructeur d'une grille
     * @param s état intial de toutes les cellules de la grille
     * @param w largeur de la grille
     * @param h hauteur de la  grille
     */
    Grid(CellState* s, int w, int h);
    /**
     * @brief Grid Constructeur complet d'une grille avec les différents états possibles
     * @param nbStates nombre d'états possibles
     * @param availableStates tableau des différents états possibles
     * @param w largeur de la grille
     * @param h hauteur de la grille
     */
    Grid(int nbStates, CellState** availableStates, int w, int h);
    /**
     * @brief Grid constructeur de recopie d'une grille
     * @param g grille à recopier
     */
    Grid(const Grid& g);
    /**
     * @brief Destructeur d'une grille
     */
    ~Grid();
    /**
     * @brief operator = redéfinition de l'opérateur d'affectation d'une grille
     * @param g grille à affecter à la grille courante
     * @return Grid& la grille affectée
     */
    Grid& operator= (const Grid& g);
    /**
     * @brief setCell accesseur en écriture d'une cellule de la grille
     * @param c nouvelle cellule
     * @param x coordonnée x de la cellule à modifier sur la grille
     * @param y coordonée y de la cellule à modifier sur la grille
     */
    void setCell(Cell* c, int x, int y);
    /**
     * @brief getCell accesseur en lecture d'une cellule de la grille
     * @param x coordonnée x de la cellule de la grille à retourner
     * @param y coordonnée y de la cellule de la grille à retourner
     * @return Cell* pointeur de la cellule retournée
     */
    Cell* getCell(int x, int y) const;
    /**
     * @brief getWidth accesseur en lecture de la largeur de la grille
     * @return int la largeur de la grille
     */
    int getWidth() const;
    /**
     * @brief getHeight accesseur en lecture de la hauteur de la grille
     * @return int la hauteur de la grille
     */
    int getHeight() const;
    /**
     * @brief getName accesseur en lecture du nom de la grille
     * @return std::string le nom de la grille
     */
    std::string getName() const;
    /**
     * @brief setName accesseur en écriture du nom de la grille
     * @param name
     */
    void setName(std::string name);
};

#endif //LO21_GRID_H
