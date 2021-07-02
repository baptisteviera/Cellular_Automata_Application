#ifndef LO21_CELL_H
#define LO21_CELL_H
#include "cell_state.h"
/**
 * @brief Direction enumération des différentes orientations pour Langston's Ant
 */
enum Direction {NONE, UP, RIGHT, DOWN, LEFT};

/**
 * @brief Classe représentant une cellule identifiée par son état, ses coordonnées et éventuellement sa direction
 */
class Cell {
  private:
    /**
     * @brief state état de la cellule
     */
    CellState* state;
    /**
     * @brief x coordonnée représentant le numéro de la colonne de la cellule dans la grille
     */
    int x;
    /**
     * @brief y coordonnée représentant le numéro de la ligne de la cellule dans la grille
     */
    int y;
    /**
     * @brief dir direction de la cellule utilisée pour l'automate Langston's Ant
     */
    Direction dir;

  public:
    /**
     * @brief setState accesseur en écriture de l'état de la cellule
     * @param s nouvel état de la cellule
     */
    void setState(CellState* s);
    /**
     * @brief getState accesseur en lecture de l'état de la cellule
     * @return  CellState* un pointeur sur l'état de la cellule
     */
    CellState* getState() const;
    /**
     * @brief Cell Constructeur d'une cellule
     * @param s pointeur sur l'état de la cellule
     * @param i coordonnée x
     * @param j coordonnée y
     * @param d direction  de la cellule (NONE par défaut)
     */
    Cell(CellState* s, int i, int j, Direction d = NONE);
    /**
     * @brief Cell Construteur de recopie d'une cellule
     */
    Cell(const Cell&);
    /**
     * @brief getX accesseur en lecture de la coordonnée x d'une cellule
     * @return int la coordonnée x de la cellule
     */
    int getX() const;
    /**
     * @brief getY accesseur en lecture de la coordonnée y d'une cellule
     * @return int la coordonnée y de la cellule
     */
    int getY() const;
    /**
     * @brief getDirection accesseur en lecture de la direction de la cellule
     * @return Direction la direction de la cellule
     */
    Direction getDirection() const;
    /**
     * @brief setDirection accesseur en écriture de la direction de la cellule
     * @param d la nouvelle direction de la cellule
     */
    void setDirection(Direction d);
    /**
     * @brief turnRight permet de modifier la direction de la cellule (rotation de 90° à droite)
     */
    void turnRight();
    /**
     * @brief turnLeft turnRight permet de modifier la direction de la cellule (rotation de 90° à gauche)
     */
    void turnLeft();
};

#endif //LO21_CELL_H
