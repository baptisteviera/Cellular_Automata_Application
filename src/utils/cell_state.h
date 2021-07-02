#ifndef LO21_CELLSTATE_H
#define LO21_CELLSTATE_H

#include <QColor>
#include <string>
/**
 * @brief Classe représentant un état de cellule
 */
class CellState {
  public:
    /**
     * @brief setId accesseur en écriture de l'identificateur
     * @param i nouvel identificateur
     */
    void setId(int i);
    /**
     * @brief setLabel accesseur en écriture du label de l'état
     * @param s nouveau label
     */
    void setLabel(std::string s);
    /**
     * @brief setColor accesseur en écriture de la couleur de l'état
     * @param c nouvelle couleur
     */
    void setColor(QColor c);
    /**
     * @brief getId accesseur en lecture de l'identificateur de l'état
     * @return int l'identificateur de l'état
     */
    int getId() const;
    /**
     * @brief getColor accesseur en lecture de la couleur de l'état
     * @return QColor la couleur de l'état
     */
    QColor getColor() const;
    /**
     * @brief getLabel accesseur en lecture du label de l'état
     * @return string le label de l'état
     */
    std::string getLabel() const;
    CellState(int x, std::string l, QColor c): id(x), label(l), col(c) {}

  private:
    /**
     * @brief id l'identificateur de l'état
     */
    int id;
    /**
     * @brief label le label de l'état
     */
    std::string label;
    /**
     * @brief col la couleur de l'état
     */
    QColor col;
};

/*
class CellStateDirection: public CellState {
private:
 direction dir;
public:
 CellStateDirection(int x, std::string l, QColor c,direction direction=none): CellState(x,l,c),dir(direction){}
 direction getDirection() const;
 void setDirection(direction d);

};
*/


#endif //LO21_CELLSTATE_H
