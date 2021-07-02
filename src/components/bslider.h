#ifndef BSLIDER_H
#define BSLIDER_H

#include <QSlider>
#include <QStyleOptionSlider>
#include <QToolTip>
/**
 * @brief classe BSlider permettant de changer la vitesse d'exécution
 */
class BSlider : public QSlider {
    Q_OBJECT
  public:
    /**
     * @brief BSlider fonction pour changer la vitesse d'exécution de l'automate
     * @param parent widget à part duquel est crée AutomatasCreator
     */
    explicit BSlider(QWidget* parent = 0);
    /**
     * @brief BSlider fonction pour changer la vitesse d'exécution de l'automate
     * @param orientation sens du changement de la barre de vitesse
     * @param parent widget à part duquel est crée AutomatasCreator
     */
    explicit BSlider(Qt::Orientation orientation, QWidget* parent = 0);

  protected:
    /**
     * @brief sliderChange fonction pour changer la position de la barre de vitesse
     * @param change position du curseur
     */
    virtual void sliderChange(SliderChange change);
};

#endif // BSLIDER_H
