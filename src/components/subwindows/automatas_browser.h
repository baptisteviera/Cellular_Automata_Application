#ifndef AUTOMATASBROWSER_H
#define AUTOMATASBROWSER_H

#include <QString>
#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QListWidget>
#include <QMessageBox>
#include "../../utils/automata_manager.h"
#include "../../utils/database.h"
#include "transitions_browser.h"
#include "neighbors_browser.h"
#include "states_browser.h"

class AutomatonCreationException{
    std::string info;

public:
    AutomatonCreationException(std::string s) : info(s){}
        std::string getInfo() const{return info;}
};

/**
 * @brief Classe AutomatasCreator permet de créer une pop-up pour configurer un automate
 */
class AutomatasCreator : public QDialog{
    /**
     * @brief transitionsBrowser pointeur contenant l'ensemble des transitions
     */

    Q_OBJECT

    TransitionsBrowser* transitionsBrowser;
    /**
     * @brief neighborsBrowser pointeur contenant l'ensemble des voisinages
     */
    NeighborsBrowser* neighborsBrowser;
    /**
     * @brief statesBrowser pointeur contenant l'ensemble des états
     */
    StatesBrowser* statesBrowser;
    /**
     * @brief chosenName nom de l'automate
     */
    QString chosenName;
    /**
     * @brief nbStates nombre d'états
     */
    int nbStates;
    /**
     * @brief chosenStates états choisis pour l'automate
     */
    CellState** chosenStates;
    /**
     * @brief chosenTransition  transition choisis pour l'automate
     */
    /**
     * @brief chosenAuthor nom de l'auteur de l'automate
     */
    QString chosenAuthor;
    /**
     * @brief chosenYear année de création de l'automate
     */
    int chosenYear;
    /**
     * @brief chosenDescription description de l'automate
     */
    QString chosenDescription;
    /**
     * @brief chosenTransition transition choisie
     */
    TransitionStrategy* chosenTransition;
    /**
     * @brief chosenNeighborhood voisinage choisis pour l'automate
     */
    NeighborhoodStrategy* chosenNeighborhood;
    /**
     * @brief mainLayout disposition principale
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief fieldsLayout disposotion pour les différents champs
     */
    QFormLayout* fieldsLayout;
    /**
     * @brief nameField disposition pour l'affichage des noms
     */
    QLineEdit* nameField;
    /**
     * @brief nbStatesSpb champ de valeurs numériques du nombre d'états choisis
     */
    QSpinBox* nbStatesSpb;
    /**
     * @brief statesList tables des états
     */
    QListWidget* statesList;
    /**
     * @brief statesItems ligne de la table des états
     */
    QListWidgetItem** statesItems;
    /**
     * @brief editStateButton bouton pour modifier un état
     */
    QPushButton* editStateButton;



    /**
     * @brief authorField champ de l'auteur
     */
    QLineEdit* authorField;
    /**
     * @brief yearSpb champ pour renseigner une année
     */
    QSpinBox* yearSpb;
    /**
     * @brief descriptionTextBox champ pour une description
     */
    QLineEdit* descriptionTextBox;
    /**
     * @brief neighborhoodChooseButton boutton afin de choisir le voisinage
     */
    QPushButton* neighborhoodChooseButton;
    /**
     * @brief transitionChooseButton boutton afin de choisir les transitions
     */
    QPushButton* transitionChooseButton;
    /**
     * @brief validateButton boutton afin de valider nos choix
     */
    QPushButton* validateButton;

    /**
     * @brief initButtons fonction qui permet de connecter les boutons
     */
    void initButtons();
    /**
     * @brief initEvents permet de connecter les boutons
     */
    void initEvents();
    /**
     * @brief createAutomaton permet d'appeler la méthode d'insertion d'automate
     */
    void createAutomaton();
    /**
     * @brief initStatesBrowser permet d'appeler la méthode de chargement d'automate
     */
    void initStatesBrowser();
    /**
     * @brief updateStatesList permet de mettre à jour la liste des états d'un automate
     */
    void updateStatesList();

public:
    /**
     * @brief AutomatasCreator constructeur de la pop-up de création d'automates
     * @param parent widget à part duquel est crée AutomatasCreator
     */
    AutomatasCreator(QWidget* parent);

public slots:
    /**
     * @brief receiveTransition permet de modifier la valeur des paramètre de la transition
     * @param t pointeur vers la transition
     */
    void receiveTransition(TransitionStrategy* t);
    /**
     * @brief receiveNeighborhood permet de modifier la valeur des paramètre du voisinage
     * @param n pointeur vers la voisinage
     */
    void receiveNeighborhood(NeighborhoodStrategy* n);
    /**
     * @brief startCreation permet de lancer la méthode createAutomaton
     */
    void startCreation();
    /**
     * @brief setChosenName permet de définir le nom de l'automate
     * @param s nom de l'automate
     */
    void setChosenName(const QString& s);
    /**
     * @brief setChosenState permet de choisir l'état
     * @param id numéro de l'état
     * @param c état de cellule
     */
    void setChosenState(int id,CellState* c);
    /**
     * @brief setChosenAuthor permet de choisir un auteur
     * @param s nom de l'auteur
     */
    void setChosenAuthor(const QString& s);
    /**
     * @brief setChosenYear permet de choisir une année
     * @param y année
     */
    void setChosenYear(int y);
    /**
     * @brief setChosenDescription permet de choisir une description
     * @param d
     */
    void setChosenDescription(const QString& d);
    /**
     * @brief changeNbStates permet de changer le nombre d'état
     * @param nb nombre d'état
     */
    void changeNbStates(int nb);
    /**
     * @brief allowEditing permet l'édition d'un champ
     * @param id
     */
    void allowEditing(int id);
};
/**
 * @brief Classe AutomatasBrowser permet de créer une pop-up pour charger les automates
 */
class AutomatasBrowser : public QDialog {
    Q_OBJECT
    /**
     * @brief mainLayout disposition principale
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief buttonsLayout disposition des boutons
     */
    QHBoxLayout* buttonsLayout;
    /**
     * @brief automatasTable tableau des automates
     */
    QTableWidget* automatasTable;
    /**
     * @brief automatasItems ligne du tableau des automates
     */
    QTableWidgetItem*** automatasItems;
    /**
     * @brief btnChoose, btnCreate boutons pour choisir et créer des automates
     */
    QPushButton *btnChoose, *btnCreate, *btnDelete, *btnSave;
    /**
     * @brief automataCreator pointeur pour l'affichage de la pop-up de création de d'automate
     */
    AutomatasCreator* automataCreator;

    const int TBL_NB_COLS = 4;
    /**
     * @brief initAutomatasTable fonction pour initialiser le tableau des automates
     */
    void initAutomatasTable();
    /**
     * @brief initButtons fonction pour connecter les boutons avec le back-end
     */
    void initButtons();

  public:
    /**
     * @brief AutomatasBrowser constructeur de la pop-up de chargement d'automates
     * @param parent widget à partir duquel est crée AutomatasBrowser
     */
    AutomatasBrowser(QWidget* parent);
    ~AutomatasBrowser();
    void openAutomatasBrowser();

  signals:
    /**
     * @brief automataChanged permet de renseigner l'id automate
     * @param id numéro de l'automate
     */
    void automataChanged(int id);
    /**
     * @brief btnCreateClicked permet d'ouvrir la pop-up de création d'automate
     */
    void btnCreateClicked();

  private slots:
    /**
     * @brief chooseAutomata permet de choisir un automate
     */
    void chooseAutomata();
    /**
     * @brief openAutomataCreator permet d'ouvrir la pop-up de cxréation d'automate
     */
    void openAutomataCreator();

    void deleteAutomata();
};

#endif // AUTOMATASBROWSER_H
