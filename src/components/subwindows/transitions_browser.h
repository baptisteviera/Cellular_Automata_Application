#ifndef TRANSITIONSBROWSER_H
#define TRANSITIONSBROWSER_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "utils/transition_strategy.h"
#include "utils/database.h"

class TransitionsBrowser : public QDialog{

    Q_OBJECT
    /**
     * @brief mainLayout layout vertical qui contient l'ensemble des layout
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief transitionLayout
     */
    QFormLayout* transitionLayout;
    /**
     * @brief transitionsCbb permet d'avoir le menu déroulant qui contiendra les transitions implémentées
     */
    QComboBox* transitionsCbb;
    /**
     * @brief btnConfirm bouton de confirmation
     */
    QPushButton* btnConfirm;
    /**
     * @brief nbTransitions le nb de transitions est mis par défaut à 0.
     */
    int nbTransitions = 0;
    /**
     * @brief transitions tableau contenant l'ensemble des transitions implémentées
     */
    TransitionStrategy** transitions = nullptr;
    /**
     * @brief selectedTransition fait référence à la transition sélectionnée
     */
    TransitionStrategy* selectedTransition = nullptr;
    /**
     * @brief updateCombobox permet de mettre à jour le menu déroulant contenant les transitions afin de prendre en compte éventuellement de nouvelles fonctionnalités
     */
    void updateCombobox();

public:
    /**
     * @brief TransitionsBrowser constructeur
     * @param parent
     */
    TransitionsBrowser(QWidget* parent);
    ~TransitionsBrowser();
    /**
     * @brief setTransitions setteur qui permet de fixer le tableau de transition
     * @param nbTransitions le nombre de transitions
     * @param transitions tableau de transition
     */
    void setTransitions(int nbTransitions, TransitionStrategy** transitions);
    /**
     * @brief openTransitionBrowser permet de charger les transitions de la BDD.
     */
    void openTransitionBrowser();

signals:
    /**
     * @brief transitionChanged fonction qui est appelé dans chooseTransition
     * @param transition la transition sélectionnée
     */
    void transitionChanged(TransitionStrategy* transition);

public slots:
    /**
     * @brief chooseTransition fonction qui appelle transitionChanged pour appliquer le changement
     */
    void chooseTransition();
    /**
     * @brief transitionsCbbChanged permet de fixer l'attribut selectedTransition à partir d'un élément de la classe transitions
     * @param id identifiant de d'un élément du tableau transition
     */
    void transitionsCbbChanged(int id);

};

#endif // TRANSITIONSBROWSER_H
