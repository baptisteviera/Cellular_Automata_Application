#ifndef CREATE_STATE_H
#define CREATE_STATE_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include "utils/database.h"
#include <QMessageBox>

class Create_State: public QDialog{
    Q_OBJECT
    /**
     * @brief mainLayout (vertical) création de la fenêtre principale qui contient tous les layouts
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief colorLayout  pour accueillir la zone de sélection de la couleur
     */
    QFormLayout* colorLayout;
    /**
     * @brief labelLayout  pour accueillir la zone de sélection du label
     */
    QFormLayout* labelLayout;
    /**
     * @brief idLayout pour accueillir la zone de sélection de l'id
     */
    QFormLayout* idLayout;
    /**
     * @brief label  pour accueillir la zone de sélection de la couleur
     */

    QLineEdit* label;
    /**
     * @brief id  la zone de sélection du label
     */
    QLineEdit* id;
    /**
     * @brief colorCbb  la zone de sélection de l'id
     */
    QComboBox* colorCbb;
    /**
     * @brief btnConfirm   la zone de sélection de la couleur
     */

    QPushButton* btnConfirm;
    /**
     * @brief initButtons permet de creer les boutons et établir les différentes conéxions avec les signaux
     */

    void initButtons();

public:
    /**
     * @brief Create_State permet de creer les boutons et établir les différentes conéxions avec les signaux
     * @param parent
     */
     Create_State(QWidget* parent);

signals:
     /**
      * @brief stateadded signal envoyé apres la création d'un état afin de recharger la liste des etats disponibles
      */
     void stateadded();

public slots:
     /**
      * @brief newState slot utilisé pour inserer l'état créé dans la base de donée
      */
   void newState();



};


#endif // CREATE_STATE_H
