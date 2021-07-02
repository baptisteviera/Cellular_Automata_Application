#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QGroupBox>
#include <QLineEdit>
#include <QListWidget>
#include "simulator_widget.h"
#include "bslider.h"
#include "utils/automata_manager.h"
#include "subwindows/automatas_browser.h"
#include "subwindows/neighbors_browser.h"
#include "subwindows/transitions_browser.h"
#include "subwindows/configs_browser.h"
#include "utils/database.h"
#include "subwindows/states_browser.h"

/**
 * @brief The ControlPanel class classe centrale qui réunit tous les objets permettant de paramétrer la simulation et de gérer toutes les données persistantes (automates, voisinages, transitions, configurations)
 */
class ControlPanel : public QWidget {
    Q_OBJECT

    /**
     * @brief mainLayout disposition générale de la console de commandes
     */
    QVBoxLayout* mainLayout;

    //Grid settings box
    /**
     * @brief gridSettingsBox boîte réunissant les paramètres du réseau pour la simulation
     */
    QGroupBox* gridSettingsBox;

    /**
     * @brief gridSettingsLayout disposition générale de la boîte des paramètres du réseau
     */
    QFormLayout* gridSettingsLayout;

    /**
     * @brief nbRowsSpb champ à nombre enier présentant le nombre de lignes du réseau
     */

    /**
     * @brief nbColsSpb champ à nombre entier présentant le nombre de colonnes du réseau
     */

    /**
     * @brief cellSizeSpb champ à nombre entier présentant la taille des cellules du réseau
     */
    QSpinBox* nbRowsSpb, *nbColsSpb, *cellSizeSpb;

    /**
     * @brief configButtonsLayout disposition des boutons poussoirs gérant la sauvegarde et le chargement d'une configuration
     */
    QHBoxLayout* configButtonsLayout;

    /**
     * @brief txtConfigName champ de texte pour le nom de la configuration courante
     */
    QLineEdit* txtConfigName;

    /**
     * @brief btnLoadConfig bouton poussoir permettant de charger une configuration
     */

    /**
     * @brief btnSaveConfig bouton poussoir permettant de sauvegarder une configuration
     */
    QPushButton *btnLoadConfig, *btnSaveConfig;

    //Automata settings box
    /**
     * @brief automataSettingsBox boîte réunissant les paramètres de l'automate pour la simulation
     */
    QGroupBox* automataSettingsBox;

    /**
     * @brief automataSettingsLayout disposition générale de la boîte des paramètres de l'automate
     */
    QVBoxLayout* automataSettingsLayout;

    //Choose automata
    /**
     * @brief automatasLabel identifie le champ texte pour le nom de l'automate
     */
    QLabel* automatasLabel;

    /**
     * @brief btnBrowseAutomatas bouton poussoir pour parcourir les automates disponibles
     */
    QPushButton* btnBrowseAutomatas;

    /**
     * @brief textAutomataName champ texte affichant le nom de l'automate
     */
    QLineEdit* textAutomataName;

    /**
     * @brief automataFieldLayout disposition pour l'affichage et le choix de l'automate
     */
    QHBoxLayout* automataFieldLayout;

    //Chose states
    /**
     * @brief statesLabel identifie la liste des états dans l'interface
     */
    QLabel* statesLabel;

    /**
     * @brief btnEditState bouton poussoir permettant d'éditer un état choisi dans la liste
     */
    QPushButton* btnEditState;

    /**
     * @brief statesListWidget liste des états utilisés par l'automate courant
     */
    QListWidget* statesListWidget;

    /**
     * @brief statesListItem tableau des états de l'automate courant à afficher dans la liste
     */
    QListWidgetItem** statesListItem;

    /**
     * @brief statesFieldLayout disposition pour l'affichage du choix des états
     */
    QHBoxLayout* statesFieldLayout;

    //Chose neighborhood
    /**
     * @brief neighborhoodLabel identifie le champ du voisinage dans l'interface
     */
    QLabel* neighborhoodLabel;

    /**
     * @brief textNeighborhoodName champ texte affichant le voisinage en cours d'utilisation
     */
    QLineEdit* textNeighborhoodName;

    /**
     * @brief btnBrowseNeighborhoods bouton poussoir permettant de lancer la pop-up qui affiche les voisinages disponibles
     */
    QPushButton* btnBrowseNeighborhoods;

    /**
     * @brief neighborhoodFieldLayout disposition pour l'affichage du choix du voisinage
     */
    QHBoxLayout* neighborhoodFieldLayout;

    //Chose transition rule
    /**
     * @brief transitionsLabel identifie le champ de la règle de transition dans l'interface
     */
    QLabel* transitionsLabel;

    /**
     * @brief textTransitionName champ de texte affichant la règle de transition en cours d'utilisation
     */
    QLineEdit* textTransitionName;

    /**
     * @brief btnBrowseTransitions bouton poussoir permettant de lancer une pop-up pour afficher les règes de transition disponibles
     */
    QPushButton* btnBrowseTransitions;

    /**
     * @brief transitionsFieldLayout disposition pour l'affichage du choix de la règle de voisinage
     */
    QHBoxLayout* transitionsFieldLayout;

    //Run settings box
    /**
     * @brief runSettingsBox boîte réunissant les paramètres de l'exécution de la simulation
     */
    QGroupBox* runSettingsBox;

    /**
     * @brief sliderSpeed curseur permettant de régler la fréquence d'exéxcution
     */
    BSlider* sliderSpeed;

    /**
     * @brief speedLabel identifie le curseur pour régler la fréquence d'exécution
     */
    QLabel* speedLabel;

    /**
     * @brief bufferSizeSpb champ à valeur entière permettant de régler la taille du buffer
     */
    QSpinBox* bufferSizeSpb;

    /**
     * @brief runSettingsLayout disposition générale pour les paramètres de l'exécution de la simulation
     */
    QFormLayout* runSettingsLayout;

    /**
     * @brief simulatorWidget widget portant la partie simulateur de l'interface
     */
    SimulatorWidget* simulatorWidget;

    /**
     * @brief automataManager singleton gérant les automates disponibles dnas l'application
     */
    AutomataManager* automataManager;



    // Popups
    /**
     * @brief automatasBrowser pop-up donnant accès aux différents automates disponibles dans l'application
     */
    AutomatasBrowser* automatasBrowser;

    /**
     * @brief neighborsBrowser pop-up donnant accès aux différents voisinages disponibles dans l'application
     */
    NeighborsBrowser* neighborsBrowser;

    /**
     * @brief transitionsBrowser pop-up donnant accès aux différentes règles de transition présentes dans l'application
     */
    TransitionsBrowser* transitionsBrowser;

    /**
     * @brief statebrowser pop-up donnant accès aux différents états présents dans l'application
     */
    StatesBrowser* statebrowser;

    /**
     * @brief configsBrowser pop-up donnant accès à la bibliothèque des configurations disponibles dans l'application
     */
    ConfigsBrowser* configsBrowser;

    /**
     * @brief loadAutomatas charge dans l'application l'ensemble des automates pris en charge
     */
    void loadAutomatas();

    /**
     * @brief loadNeighborhoods charge dans l'application l'ensemble des voisinages pris en charge
     */
    void loadNeighborhoods();

    /**
     * @brief loadTransitions charge dans l'application l'ensemble des règles de transition prises en charge
     */
    void loadTransitions();

    /**
     * @brief loadStates charge dans l'application l'ensemble des états pris en charge
     */
    void loadStates();

  public:
    /**
     * @brief ControlPanel constructeur de la classe ControlPanel
     * @param parent widget parent du panneau de contrôle
     * @param simulatorWidget widget portant la partie simulateur de l'interface
     */
    explicit ControlPanel(QWidget* parent, SimulatorWidget* simulatorWidget);

    /**
      * @brief Destructeur de la classe ControlPanel
      */
    ~ControlPanel();

    /**
     * @brief initGridSettings délégation utilisée par le constructeur, initialise tous les objets ayant trait aux paramètres du réseau
     */
    void initGridSettings();

    /**
     * @brief initAutomataSettings délégation utilisée par le constructeur, initialise tous les objets ayant trait aux paramètres de l'automate
     */
    void initAutomataSettings();

    /**
     * @brief initRunSettings délégation utilisée par le constructeur, initialise tous les objets ayant trait aux paramètres de l'exécution
     */
    void initRunSettings();

    /**
     * @brief setNbRows paramètre le nombre de lignes du réseau
     * @param nbRows nombre de lignes
     */
    void setNbRows(int nbRows);

    /**
     * @brief setNbCols paramètre le nombre de colonnes du réseau
     * @param nbCols nombre de colonnes
     */
    void setNbCols(int nbCols);

    /**
     * @brief setCellSize paramètre la taille des cellules du réseau
     * @param cellSize taille des cellules
     */
    void setCellSize(int cellSize);

    /**
     * @brief initEventHandler délégation utilisée par le constructeur, initialise la prise en charge de tous les événements qui lient les objets de la classe entre eux
     */
    void initEventHandler();

  signals:
    /**
     * @brief automataChanged signal indiquant que l'automate courant à utiliser par le simulateur a changé
     * @param id identifiant du nouvel automate à utiliser
     */
    void automataChanged(int id);
    void stateadded();
  private slots:
    /**
     * @brief openNeighborsBrowser slot engrangeant l'ouverture de l'explorateur des voisinages
     */
    void openNeighborsBrowser();

    /**
     * @brief setAutomata slot permettant de changer l'automate à utiliser
     * @param id identifiant du nouvel automate à utiliser
     */
    void setAutomata(int id);

    /**
     * @brief setNeighbor slot permettant de changer le voisinage à utiliser
     * @param neighbor nouveau voisinage à utiliser
     */
    void setNeighbor(NeighborhoodStrategy* neighbor);

    /**
     * @brief setTransition slot permettant de changer la règle de transition à utiliser
     * @param transition nouvelle règle de transition à utiliser
     */
    void setTransition(TransitionStrategy* transition);

    /**
     * @brief setConfig slot permettant de charger une configuration dans le simulateur
     * @param config configuration à charger dans le simulateur
     */
    void setConfig(Grid* config);

    /**
     * @brief openTransitionsBrowser slot engrengeant l'ouverture de l'explorateur des règles de transition
     */
    void openTransitionsBrowser();

    /**
     * @brief openAutomatasBrowser slot engrangeant l'ouverture de l'explorateur des automates
     */
    void openAutomatasBrowser();

    /**
     * @brief openStateBrowser slot engrangeant l'ouverture de l'explorateur des états
     */
    void openStateBrowser();

    /**
     * @brief openConfigsBrowser slot engrangeant l'ouverture de l'explorateur des configurations qui peuvent être chargées
     */
    void openConfigsBrowser();

    /**
     * @brief updateStates slot engendrant la mise à jour des états de l'automate courant
     */
    void updateStates();

    /**
     * @brief btnSaveConfigClicked slot lançant les actions liées à un click sur le bouton de sauvegarde d'une configuration
     */
    void btnSaveConfigClicked();
};

#endif // CONTROL_PANEL_H
