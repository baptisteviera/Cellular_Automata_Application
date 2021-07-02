#ifndef CELL_WIDGET_H
#define CELL_WIDGET_H

#include <QWidget>
#include <QPalette>
#include <QMouseEvent>
#include <QToolTip>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include "utils/cell.h"

/**
 * @brief Classe CellWidget hérite de QWidget
 */
class CellWidget : public QWidget {
    Q_OBJECT
  public:
    explicit CellWidget() = default;
    /**
     * @brief CellWidget modifie les paramètre d'une cellule
     * @param parent widget à partir duquel est crée CellWidget
     * @param cellSize taille de la cellule
     * @param cell cellule à modifier
     */
    explicit CellWidget(QWidget* parent, int cellSize, Cell* cell);
    /**
     * @brief setColor modifie la couleur de la cellule
     * @param color couleur à modifier dans la cellule
     */
    void setColor(const QColor& color);
    /**
     * @brief setSize modifie taille de la cellule
     * @param size taille en question
     */
    void setSize(int size);
    /**
     * @brief setCell modifie la cellule
     * @param cell cellule à modifier
     */
    void setCell(Cell* cell);
    /**
     * @brief getCell renvoie une cellule
     */
    Cell* getCell() const;
    /**
     * @brief updateDisplay modifie l'affichage avec les nouveaux paramètre de la cellule
     */
    void updateDisplay();
    /**
     * @brief paintEvent modifie le sens de la flèche pour Langton's ant
     */
    virtual void paintEvent(QPaintEvent*);

  private:
    /**
     * @brief cell cellule de la grille
     */
    Cell* cell;
    /**
     * @brief leftMouseClicked état du clic gauche
     */
    bool leftMouseClicked = false;
    /**
     * @brief rightMouseClicked état du clic droit
     */
    bool rightMouseClicked = false;

  protected:
    /**
     * @brief mousePressEvent changement de l'état du clic gauche
     * @param event évènement du clic gauche
     */
    void mousePressEvent(QMouseEvent* event);
    /**
     * @brief mouseReleaseEvent changement de l'état du clic gauche
     * @param event évènement du clic droit
     */
    void mouseReleaseEvent(QMouseEvent* event);

  signals:
    /**
     * @brief leftClicked modifie l'état du clic gauche
     * @param x position x de la cellule
     * @param y position y de la cellule
     */
    void leftClicked(int x, int y);
    /**
     * @brief rightClicked modifie l'état du clic droit
     * @param x position x de la cellule
     * @param y position y de la cellule
     */
    void rightClicked(int x, int y);
};

#endif // CELL_WIDGET_H
