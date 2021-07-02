#ifndef AUTOMATA_SETTINGS_WINDOWS_H
#define AUTOMATA_SETTINGS_WINDOWS_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVariant>
#include "utils/neighborhood_strategy.h"

/**
 * @brief classe StateBrowseWindow permet de créer la pop-up de parcours des états
 */
class StateBrowseWindow : public QDialog{
    Q_OBJECT
    /**
     * @brief mainLayout disposition principale
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief stateLayout disposition des états
     */
    QFormLayout* stateLayout;
    /**
     * @brief stateCbb menu déroulant pour afficher les états
     */
    QComboBox* stateCbb;
    /**
     * @brief nameStateLabel champ de texte correspondant au nom des états
     */
    QLabel* nameStateLabel;
public:
    /**
     * @brief StateBrowseWindow constructeur par défaut de la pop-up des états
     */
    StateBrowseWindow();
    ~StateBrowseWindow(){};

};

/**
 * @brief Classe NeighborsBrowseWindow permet de créer la pop-up de parcours des voisinages
 */
class NeighborsBrowseWindow : public QDialog{
    Q_OBJECT
    /**
     * @brief mainLayout disposition principale
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief neighborhoodLayout disposition des voisinages
     */
    QFormLayout* neighborhoodLayout;
    /**
     * @brief neighborhoodCbb menu déroulant pour afficher les voisinages
     */
    QComboBox* neighborhoodCbb;
    /**
     * @brief radiusSetting cadre du champ des rayons
     */
    QGroupBox* radiusSetting;
    /**
     * @brief radius champ de valeurs numériques des rayons
     */
    QSpinBox* radius;


public:
    /**
     * @brief NeighborsBrowseWindow constructeur par défaut de la pop-up des voisinages
     */
    NeighborsBrowseWindow();
    ~NeighborsBrowseWindow(){};
private slots:
    void clickedactions(int indexItem);

};

/**
 * @brief Classe TransitionBrowseWindow permet de créer la pop-up de parcours des transitions
 */
class TransitionBrowseWindow : public QDialog{
    Q_OBJECT
    //transition Spinbox
    /**
     * @brief mainLayout disposition principale
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief transitionLayout disposition des transitions
     */
    QFormLayout* transitionLayout;
    /**
     * @brief transitionCbb menu déroulant pour afficher les transitions
     */
    QComboBox* transitionCbb;
    /**
     * @brief directionLayout disposition des transitions
     */
    QFormLayout* directionLayout;
    /**
     * @brief directionCbb menu déroulant pour afficher les directions
     */
    QComboBox* directionCbb;
    /**
     * @brief Confirm boutton de confirmation des choix
     */
    QPushButton *Confirm;


public:
    /**
     * @brief TransitionBrowseWindow constructeur par défaut de la pop-up des transitions
     */
    TransitionBrowseWindow();
    ~TransitionBrowseWindow(){};
private slots:
    /**
     * @brief clickedaction permet d'afficher la direction selon le type de transition
     * @param indexItem indice de la transition
     */
    void clickedaction(int indexItem);

};



#endif // AUTOMATA_SETTINGS_WINDOWS_H
